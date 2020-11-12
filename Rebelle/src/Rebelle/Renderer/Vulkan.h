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
		Vulkan();
		inline static Vulkan& Get() { return *s_Instance; }
		inline void setWindow(GLFWwindow* glfwWindow) { window = glfwWindow; };
		inline GLFWwindow* getWindow() { return window; };
		inline VkInstance getInstance() { return instance; };
		inline VkSurfaceKHR* getSurface() { return &surface; };
		inline VkRenderPass getRenderPass() { return renderPass; };
		inline VkPhysicalDevice getPhysicalDevice() { return physicalDevice; };
		inline VkDevice getDevice() { return device; };
		inline uint32_t getQueueFamily() { return queueFamily; };
		inline VkQueue getQueue() { return graphicsQueue; };
		inline uint32_t getImageCount() { return imageCount; };
		inline uint32_t getMinImageCount() { return minImageCount; };
		std::vector<VkCommandBuffer> getCommandBuffers() { return commandBuffers; };
		inline VkDescriptorPool getDescriporPool() { return descriptorPool; };
		void init(GLFWwindow* glfWwindow);
		void cleanUp();
		void drawFrame();
		void run();
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	private:
		static Vulkan* s_Instance;
		uint32_t imageCount = 2;
		uint32_t minImageCount = 2;
		uint32_t queueFamily;
		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;
		const int MAX_FRAMES_IN_FLIGHT = 2;
		VkInstance instance = VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT callback = VK_NULL_HANDLE;
		bool enableValidationLayers = true;
		const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
		const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device = VK_NULL_HANDLE;
		VkQueue graphicsQueue = VK_NULL_HANDLE;
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		VkQueue presentQueue = VK_NULL_HANDLE;
		GLFWwindow* window = VK_NULL_HANDLE;
		VkSwapchainKHR swapChain = VK_NULL_HANDLE;
		std::vector<VkImage> swapChainImages = { };
		VkFormat swapChainImageFormat = { };
		VkExtent2D swapChainExtent = { };
		std::vector<VkImageView> swapChainImageViews = { };
		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;
		std::vector<VkFramebuffer> swapChainFramebuffers;
		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffers;
		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;		
		std::vector<VkFence> imagesInFlight;
		VkDescriptorPool descriptorPool;
		std::vector<VkFence> inFlightFences;
		size_t currentFrame = 0;
		bool framebufferResized = false;
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
		VkShaderModule createShaderModule(const std::vector<char>& code);
		void createGraphicsPipline();
		void createRenderPass();
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffers();
		void createSyncObjects();
		void createDescriptorPool();
		void recreateSwapChain();
		void cleanupSwapChain();
	};
}
