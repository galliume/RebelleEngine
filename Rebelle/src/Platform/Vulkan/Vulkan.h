#pragma once
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include "rblpch.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <optional>
#include <array>
#include <cstddef>
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
	struct Vertex 
	{
		glm::vec2 pos;
		glm::vec3 color;

		static VkVertexInputBindingDescription getBindingDescription() 
		{
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}
		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() 
		{
			std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			return attributeDescriptions;
		}
	};
	struct UniformBufferObject {
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};
	const std::vector<Vertex> vertices = {
	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
	{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};
	const std::vector<uint16_t> indices =
	{
		0, 1, 2, 2, 3, 0
	};
	class Vulkan
	{
	public:
		Vulkan();
		inline static Vulkan& Get() { return *s_Instance; }

		void createInstance();
		inline VkInstance getInstance() { return instance; };
		void createSurface();
		inline VkSurfaceKHR* getSurface() { return &surface; };
		
		void pickPhysicalDevice();
		void createLogicalDevice();
		inline VkPhysicalDevice getPhysicalDevice() { return physicalDevice; };

		void createDescriptorPool();
		void createDescriptorSets();

		void createSwapChain();		

		void createDescriptorSetLayout();

		void createUniformBuffers();
		
		void recreateSwapChain();

		void createGraphicsPipeline();
		void createImageViews();		

		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void createIndexBuffer();
		void createGraphicsPipline();
		void createRenderPass();
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffers();
		void createSyncObjects();
		void cleanupSwapChain();
		void createVertexBuffer();

		inline void setWindow(GLFWwindow* glfwWindow) { window = glfwWindow; };
		inline GLFWwindow* getWindow() { return window; };
		inline VkRenderPass getRenderPass() { return renderPass; };
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
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
		inline size_t getCurrentFrame() { return currentFrame; };
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
		std::vector<VkFence> inFlightFences;
		size_t currentFrame = 0;
		bool framebufferResized = false;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		VkDescriptorSetLayout descriptorSetLayout;
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;
		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptorSets;
	private:
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);		
		bool isDeviceSuitable(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void setupDebugMessenger();
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		VkShaderModule createShaderModule(const std::vector<char>& code);
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		void updateUniformBuffer(uint32_t currentImage);
	};
}
