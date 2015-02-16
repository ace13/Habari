#pragma once

#include "Habari.hpp"

namespace Habari
{

template<typename T>
class Parameter : public IParameter
{
public:

protected:

private:
	T mValue;
	SourceType mSource;
	std::function<bool(const T&)const> mValidator;
};

template<typename T>
Parameter<T>& GetParameter(const std::string& name);
	
}
