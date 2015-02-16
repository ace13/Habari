#pragma once

#include "Habari.hpp"

#include <functional>

namespace Habari
{
	
class Flag : public IParameter
{
public:
	typedef bool value_type;
	typedef std::function<bool()> verifier_type;

	Flag() : mSources(Source_Default) { mValue = getDefault(); }
	virtual ~Flag() { }
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
	virtual void setValue(const char* inp, SourceTypes source);

	virtual value_type getDefault() const { return false; }
	virtual verifier_type getVerifier() const { return verifier_type(); }

private:
	value_type mValue;
	int mSources;
};

extern Flag& GetFlag(const char* name);

}
