#include <Rebelle.h>

class SandBox : public Rebelle::Application
{
	public:
		SandBox()
		{

		}

		~SandBox()
		{

		}

};

Rebelle::Application* Rebelle::CreateApplication()
{
	return new SandBox();
}