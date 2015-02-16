#pragma once

#include "Habari.hpp"

#include <functional>

namespace Habari
{
	
class MultiFlag : public IParameter
{
public:
	typedef unsigned int value_type;
	typedef std::function<bool(value_type)> verifier_type;

	MultiFlag() : mSources(Source_Default) { mValue = getDefault(); }
	virtual ~MultiFlag() { }
	
	virtual unsigned int numAliases() const { return 0; }
	virtual const char* getAlias(unsigned int = 0) const { return nullptr; }
    virtual const char* getCategory() const { return nullptr; }
	virtual unsigned int numShorthands() const { return 0; }
	virtual char getShorthand(unsigned int = 0) const { return '\0'; }
	virtual const char* getEnvironment() const { return nullptr; }

	virtual bool isSet(SourceTypes source = Source_Any) const { return (mSources & source) == source; }
	virtual int getSources() const { return mSources; }

	virtual value_type get() const { return mValue; }
	virtual void set(value_type value, SourceTypes source = Source_User) { mValue = value; mSources |= source; }
	virtual void inc(SourceTypes source = Source_User) { ++mValue; mSources |= source; }
	virtual void setValue(const char* inp, SourceTypes source);

	virtual value_type getDefault() const { return 0; }
    virtual verifier_type getVerifier() const { return verifier_type(); }

private:
	value_type mValue;
	int mSources;
};

extern MultiFlag& GetMultiflag(const char* name);

}
