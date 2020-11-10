#include <Rebelle.h>

class ExampleLayer : public Rebelle::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		//RBL_INFO("Layer update !");
	}

	void OnEvent(Rebelle::Event& event) override
	{
		//RBL_TRACE("{0}", event);
	}
	virtual void OnImGuiRender() override
	{

	}
};
class SandBox : public Rebelle::Application
{
	public:
		SandBox()
		{
			PushLayer(new ExampleLayer());
		}

		~SandBox()
		{

		}

};

Rebelle::Application* Rebelle::CreateApplication()
{
	return new SandBox();
}