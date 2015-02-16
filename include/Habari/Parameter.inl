#pragma once

#include <sstream>

template<typename T>
T Habari::Parse(const char* inp)
{
	T ret;
	std::ostringstream sstr(inp);
	sstr >> ret;

	return ret;
}

template<typename T>
Habari::Parameter<T>& Habari::GetParameter(const char* name)
{
	return *dynamic_cast<Habari::Parameter<T>*>(FindParameter(name));
}
