#pragma once

#include "Habari.hpp"

namespace Habari
{
	
class MultiFlag
{
public:
	MultiFlag() { setDefault(); mSource = Source_Default; }
	virtual ~MultiFlag() { }
	
	virtual const char* getName() const = 0;
	virtual const char* getDescription() const = 0;

	virtual const char* getCategory() const { return nullptr; }
	virtual const char* getConfigName() const { return nullptr; }
	virtual const char* getShorthand() const { return nullptr; }
	virtual const char* getEnvironment() const { return nullptr; }

	virtual bool isSet(SourceTypes source = Source_Any) const;
	virtual bool get() const;
	virtual SourceTypes getSource() const;

	virtual void setValue(unsigned int value = 1);

protected:
	virtual void setDefault() { mValue = false; }

private:
	unsigned int mValue;
	SourceTypes mSource;
};

}
