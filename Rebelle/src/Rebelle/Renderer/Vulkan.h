#pragma once

#include "rblpch.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Rebelle {
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
	private:
		void createInstance();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		bool checkValidationLayerSupport();
		void setupDebugMessenger();
		std::vector<const char*> getRequiredExtensions();
	};
}
