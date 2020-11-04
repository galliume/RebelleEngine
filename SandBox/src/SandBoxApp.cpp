#include <Rebelle.h>

class ExampleLayer : public Rebelle::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		RBL_INFO("Layer update !");
	}

	void OnEvent(Rebelle::Event& event) override
	{
		RBL_TRACE("{0}", event);
	}
};
class SandBox : public Rebelle::Application
{
	public:
		SandBox()
		{
			PushLayer(new ExampleLayer());
			PushOverlay(new Rebelle::ImGuiLayer());
		}

		~SandBox()
		{

		}

};

Rebelle::Application* Rebelle::CreateApplication()
{
	return new SandBox();
}