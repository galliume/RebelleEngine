#pragma once

#include "rblpch.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>

namespace Rebelle {
	struct QueueFamilyIndices 
	{
		std::optional<uint32_t> graphicsFamily;
		bool isComplete() { return graphicsFamily.has_value(); }
	};

	class Vulkan
	{
	public:
		void init();		
		void cleanUp();
	private:
		VkInstance instance;
		VkDebugUtilsMessengerEXT callback;
		bool enableValidationLayers = true;
		const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;
		VkQueue graphicsQueue;
	private:
		void createInstance();
		void createLogicalDevice();
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void setupDebugMessenger();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
	};
}
