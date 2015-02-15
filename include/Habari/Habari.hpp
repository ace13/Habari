#pragma once

namespace Habari
{
	
enum SourceTypes
{
	Source_Default = 1,
	Source_Config = 2,
	Source_Environment = 4,
	Source_Commandline = 8,

	Source_Any = 14
};

void ParseConfig(const std::string& file);
void ParseConfig(std::istream& stream);
void ParseEnvironment();
void ParseCommandline(int argc, char** argv);

template<typename T>
void RegisterParameter(T&);

class IParameter
{
public:
	virtual const char* getName() const = 0;
	virtual const char* getDescription() const = 0;

	virtual const char* getCategory() const = 0;
	virtual const char* getConfigName() const = 0;
	virtual char getShorthand() const = 0;
	virtual const char* getEnvironment() const = 0;

	virtual bool isSet(SourceTypes source = Source_Any) const = 0;
	virtual SourceTypes getSource() const = 0;

protected:
	virtual bool hasCategory() const = 0;
	virtual bool hasConfigName() const = 0;
	virtual bool hasShorthand() const = 0;
	virtual bool hasEnvironment() const = 0;
};

}
