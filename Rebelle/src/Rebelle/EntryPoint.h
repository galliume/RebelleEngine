#pragma once

#ifdef RBL_PLATFORM_WINDOWS

extern Rebelle::Application* Rebelle::CreateApplication();

int main(int argc, char** argv)
{

	Rebelle::Log::Init();

	auto app = Rebelle::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Rebelle only support Windows.
#endif