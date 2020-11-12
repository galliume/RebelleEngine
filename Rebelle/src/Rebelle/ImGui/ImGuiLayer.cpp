#include "rblpch.h"

#include "ImGuiLayer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

//@todo why include .cpp ? without them it does not work...
#include "backends/imgui_impl_glfw.cpp"
#include "backends/imgui_impl_vulkan.cpp"

#include "Rebelle/Macros.h"
#include "Rebelle/Application.h"
#include "Rebelle/Renderer/Vulkan.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Rebelle {

	ImGuiLayer::ImGuiLayer(): Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		unsigned char* tex_pixels = NULL;
		int tex_w, tex_h;
		io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &tex_w, &tex_h);

		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		Vulkan vulkan = Vulkan::Get();

		ImFontAtlas fontAtlas = ImFontAtlas();
		fontAtlas.AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		ImGui::CreateContext(&fontAtlas);

		ImGui_ImplGlfw_InitForVulkan(vulkan.getWindow(), true);

		// Setup Platform/Renderer bindings
		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = vulkan.getInstance();
		init_info.PhysicalDevice = vulkan.getPhysicalDevice();
		init_info.Device = vulkan.getDevice();
		init_info.QueueFamily = vulkan.getQueueFamily();
		init_info.Queue = vulkan.getQueue();
		init_info.PipelineCache = VK_NULL_HANDLE;
		init_info.DescriptorPool = vulkan.getDescriporPool();
		init_info.Allocator = VK_NULL_HANDLE;
		init_info.MinImageCount = vulkan.getMinImageCount();
		init_info.ImageCount = vulkan.getImageCount();
		ImGui_ImplVulkan_Init(&init_info, vulkan.getRenderPass());
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		RBL_CORE_TRACE("yopiu");
		ImGui_ImplVulkan_NewFrame();
		ImGui::NewFrame();
		ImGui_ImplGlfw_NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		Vulkan vulkan = Vulkan::Get();

		// Rendering
		ImGui::Render();

		std::vector<VkCommandBuffer>listCmdBuffers = vulkan.getCommandBuffers();

		for (int i = 0; i < listCmdBuffers.size(); i++)
		{
			VkCommandBuffer cmdBuffer = listCmdBuffers[i];
			ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cmdBuffer);
		}

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
}
