#pragma once
/*
* Variadic Generic Lambda
* safer and more dynamic than [this](Event & event,	auto&&...args) { return this->OnEvent(event, args...);}
* or than std::bind(&Application::x, this, std::placeholders::_1)
*/
#define BIND_EVENT_FN(event) [this](auto&&... args) { return event(std::forward<decltype(args)>(args)...); } 