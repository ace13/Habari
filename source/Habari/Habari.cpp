#include <Habari/Habari.hpp>

#include <Habari/Flag.hpp>
#include <Habari/MultiFlag.hpp>
#include <Habari/Parameter.hpp>

#include <vector>
#include <cstdlib>

namespace 
{
	std::vector<IParameter*> Parameters;

	void ParseEnvVar(const char* input, IParameter* p)
	{
		auto sources = p->getSources();
		if (sources & (Source_User | Source_Commandline) > 0)
			return;

		if (Habari::Flag* flag = dynamic_cast<Habari::Flag*>(p))
			flag->set(Habari::Source_Environment);
		else if (Habari::MultiFlag* mf = dynamic_cast<Habari::MultiFlag*>(p))
		{
			unsigned int val;
			int ret = sscanf(input, "%u", &val);
			if (ret == 1)
				mf->set(val, Habari::Source_Environment);
			else
				printf("Unknown value '%s' provided to %s\n", input, p->getEnvironment());
		}
		else
		{
			p->setValue(input, Habari::Source_Environment);
		}
	}
}

void Habari::ParseEnvironment()
{
	for (auto& i : Parameters)
	{
		const char* envVar = i->getEnvironment();

		if (envVar)
		{
			char* val = std::getenv(envVar);
			if (val)
			{
				ParseEnvVar(val, i);
			}
		}
	}
}
void Habari::ParseCommandline(int argc, char** argv)
{

}

bool Habari::HasErrors()
{
	return false;
}
void Habari::PrintErrors()
{

}

bool Habari::RegisterParameter(Habari::IParameter* param)
{
	Parameters.push_back(param);

	return true;
}

Habari::IParameter* Habari::FindParameter(const char* name)
{
	for (auto& i : Parameters)
	{
		if (i->getName() == name)
			return i;
	}

	return nullptr;
}

Habari::Flag& Habari::GetFlag(const char* name)
{
	return *dynamic_cast<Habari::Flag*>(FindParameter(name));
}

Habari::MultiFlag& Habari::GetMultiflag()
{
	return *dynamic_cast<Habari::MultiFlag*>(FindParameter(name));
}

void Habari::Flag::setValue(const char*, Habari::SourceTypes source)
{
	set(source);
}

void Habari::MultiFlag::setValue(const char* inp, Habari::SourceTypes source)
{
	unsigned int val;
	int ret = sscanf(input, "%u", &val);
	if (ret == 1)
		set(val, source);
	else if (ret == EOF)
		inc(source);
	else
		printf("Unknown value '%s' provided to %s\n", input, p->getName());
}
