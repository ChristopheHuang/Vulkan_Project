#include "context.hpp"

namespace Application {
	std::unique_ptr<Context> Context::instance_ = nullptr;

	void Context::Init() {
		if (!instance_) {
			instance_.reset(new Context());
		}
	}

	void Context::Quit() {
		instance_.reset();
	}

	Context& Context::GetInstance() {
		return *instance_; 
	}	

	Context::Context() {
		createInstance();
		pickupPhysicalDevice();
		// Ask for queue family indices before creating device
		queryQueueFamilyIndices();
		createDevice();
		getQueues();
	}

	Context::~Context() {
		device.destroy();
		instance.destroy();
	}

	void Context::createInstance() {
		vk::InstanceCreateInfo createInfo;
		std::vector<const char*> layers = { "VK_LAYER_KHRONOS_validation" };

		// Search for available layers
		//auto layers = vk::enumerateInstanceLayerProperties();
		//for (auto& layer : layers) {
		//	std::cout << layer.layerName << std::endl;
		//}

		vk::ApplicationInfo appInfo;

		appInfo.setApiVersion(VK_API_VERSION_1_3)
			.setPEngineName("GLFW").setPApplicationName("Vulkan Project");

		


		createInfo.setPApplicationInfo(&appInfo)
			.setPEnabledLayerNames(layers);
		
		instance = vk::createInstance(createInfo);
	}

	void Context::pickupPhysicalDevice() {
		auto devices = instance.enumeratePhysicalDevices();
		physicalDevice = devices[0];
		
		std::cout << physicalDevice.getProperties().deviceName << std::endl;
	}

	void Context::createDevice() {
		vk::DeviceCreateInfo createInfo;
		vk::DeviceQueueCreateInfo queueCreateInfo;
		float priorities = 1.0f;
		queueCreateInfo.setPQueuePriorities(&priorities)
			.setQueueCount(1)
			.setQueueFamilyIndex(queueFamilyIndices.graphicsQueue.value());

		createInfo.setQueueCreateInfos(queueCreateInfo);

		device = physicalDevice.createDevice(createInfo);
	}

	void Context::getQueues() {
		graphicsQueue = device.getQueue(queueFamilyIndices.graphicsQueue.value(), 0);
	}

	void Context::queryQueueFamilyIndices() {
		auto properties = physicalDevice.getQueueFamilyProperties();
		for (int i = 0; i < properties.size(); i++) {
			const auto& property = properties[i];
			if (property.queueFlags | vk::QueueFlagBits::eGraphics) {
				queueFamilyIndices.graphicsQueue = i;
				break;
			}
		}
	}
}