#pragma once
#include <vulkan/vulkan.hpp>
#include <memory>
#include <iostream>
#include <cassert>
#include <optional>

namespace Application {

	class Context final
	{
	public:
		static void Init();
		static void Quit();

		struct QueueFamilyIndices {
			std::optional<uint32_t> graphicsQueue;
		};

		static Context& GetInstance();
		
		~Context();

		vk::Instance instance;
		vk::PhysicalDevice physicalDevice;
		vk::Device device;
		vk::Queue graphicsQueue;
		QueueFamilyIndices queueFamilyIndices;

	private:
		static std::unique_ptr<Context> instance_;

		Context();

		void createInstance();
		void pickupPhysicalDevice();
		void createDevice();
		void getQueues();
		
		void queryQueueFamilyIndices();
	};
}