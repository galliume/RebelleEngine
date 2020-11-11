#pragma once

#include "rblpch.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>

namespace Rebelle {
	struct QueueFamilyIndices 
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); };
	};
	struct SwapChainSupportDetails 
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class Vulkan
	{
	public:
		Vulkan(GLFWwindow *window);
		inline static Vulkan& Get() { return *s_Instance; }
		void init();		
		void cleanUp();
	private:
		VkInstance instance;
		VkDebugUtilsMessengerEXT callback;
		bool enableValidationLayers = true;
		const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
		const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;
		VkQueue graphicsQueue;
		VkSurfaceKHR surface;
		VkQueue presentQueue;
		static Vulkan* s_Instance;
		GLFWwindow* window;
		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkImageView> swapChainImageViews;
	private:
		void createInstance();
		void createGraphicsPipeline();
		void createImageViews();
		void createSwapChain();
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		void createSurface();
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		void createLogicalDevice();
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void setupDebugMessenger();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
	};
}
