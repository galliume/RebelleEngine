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

int main()
{
	SandBox* sandBox = new SandBox();
	sandBox->Run();
	delete sandBox;
}