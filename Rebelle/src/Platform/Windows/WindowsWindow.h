#pragma once

#include "rblpch.h"
#include "Rebelle/Window.h"
#include "Rebelle/Renderer/Vulkan.h"

#include <GLFW/glfw3.h>

namespace Rebelle {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		static void GFLWErrorCallback(int error, const char* description)
		{
			RBL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
		}

		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; };
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		Vulkan m_vulkan;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}