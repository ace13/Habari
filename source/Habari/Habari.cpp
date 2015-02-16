#include <Habari/Habari.hpp>

#include <Habari/Flag.hpp>
#include <Habari/MultiFlag.hpp>
#include <Habari/Parameter.hpp>

#include <vector>
#include <cstdlib>

#ifndef WIN32
#include <libgen.h>
#endif

namespace 
{
	std::vector<IParameter*> Parameters;
	std::string ProgramName;

	void ParseEnvVar(const char* input, IParameter* p)
	{
		auto sources = p->getSources();
		if (sources & (Source_User | Source_Commandline) > 0)
			return;

		if ((Habari::Flag* flag = dynamic_cast<Habari::Flag*>(p)))
			flag->set(Habari::Source_Environment);
		else if ((Habari::MultiFlag* mf = dynamic_cast<Habari::MultiFlag*>(p)))
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
	ProgramName = argv[0];
#ifdef WIN32
	int pos = ProgramName.find_last_of('\\');
	if (pos != std::string::npos)
	ProgramName = ProgramName.erase(0, pos + 1);
#else
	ProgramName = basename(ProgramName.data());
#endif

	IParameter* waiting = nullptr;
	for (int i = 1; i < argc; ++i)
	{
		char* arg = argv[i];

		if (*arg == '-' && !waiting)
		{
			if (arg[1] == '-')
			{
				char* nameS = arg + 2, nameE = nameS;
				while (*++nameE != '=' && *nameE != '\0');

				for (auto& p : Parameters)
				{
					if (strncmp(p->getName(), nameS, nameE-nameS) == 0)
					{
						waiting = p;
						break;
					}
					else if ((unsigned int as = p->numAliases()) > 0)
					{
						for (unsigned int j = 0; j < as; ++j)
						{
							if (strncmp(p->getAlias(j), nameS, nameE-nameS) == 0)
							{
								waiting = p;
								break;
							}
						}
					}

					if (waiting)
						break;
				}

				if (!waiting)
					printf("Unknown parameter '%s' given.\n", nameS);
				else if ((Habari::Flag* flag = dynamic_cast<Habari::Flag*>(waiting)))
				{
					flag->set(Habari::Source_Commandline);
					waiting = nullptr;
				}
			}
			else
			{
				int sh = 1;
				do
				{
					char shorthand = arg[sh];

					for (auto& p : Parameters)
					{
						unsigned int shs = p->numShorthands();
						for (unsigned int j = 0; j < shs; ++j)
							if (p->getShorthand(j) == shorthand)
							{
								if (waiting)
									waiting->setValue(nullptr, Source_Commandline);

								waiting = p;
								break;
							}
					}
				} while (arg[++sh] != '\0');
			}
		}
		else if (waiting)
		{
			waiting->setValue(arg, Source_Commandline);
			waiting = nullptr;
		}
	}
}

bool Habari::HasErrors()
{
	return false;
}
void Habari::PrintErrors()
{

}
void Habari::PrintUsage(const char* extraOptions)
{
	std::cout << "Usage: " << ProgramName << " [options] " << (extraOptions ? std::string(extraOptions) : "") << std::endl
		<< std::endl
		<< "General Options:" << std::endl;
	std::set<std::string> categories;
	for (auto& i: Parameters)
	{
		if (i->getCategory())
		{
			categories.insert(i->getCategory());
			continue;
		}

		bool first = true;
		std::strinstream sstr;
		sstr << "  ";
		for (unsigned int j = 0; j < i->numShorthands(); ++j)
		{
			sstr << (!first ? ", " : "") << "-" << i->getShorthand(j);

			if (first)
				first = false;
		}
		sstr << (!first ? ", " : "") << "--" << std::string(i->getName());
		for (unsigned int j = 0; j < i->numAliases(); ++j)
		{
			sstr << ", --" << std::string(i->getAlias(j));
		}

		if (sstr.tellp() > 16)
			sstr << std::endl << sstr << "                ";
		std::cout << sstr.str() << " " << std::string(i->getDescription()) << std::endl;
	}
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
	auto ver = getVerifier();
	if (ver && !ver())
		return;

	set(source);
}

void Habari::MultiFlag::setValue(const char* inp, Habari::SourceTypes source)
{
	auto ver = getVerifier();

	if (inp)
	{
		unsigned int val;
		int ret = sscanf(input, "%u", &val);
		if (ret == 1)
		{
			if (!ver || ver(val))
				set(val, source);
		}
		else if (ret == EOF)
		{
			if (!ver || ver(mValue + 1))
				inc(source);
		}
		else
			printf("Unknown value '%s' provided to %s\n", input, p->getName());
	}
	else if (!ver || ver(mValue + 1))
		inc(source);
}
