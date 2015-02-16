#pragma once

#include <sstream>

template<typename T>
T Habari::Parse(const char* inp)
{
	if (!inp)
	{
		printf("No argument provided to %s.\n", getName());
		return T();
	}

	auto ver = getVerifier();

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
