#pragma once

#include "Habari.hpp"

#include <functional>

namespace Habari
{
	
class MultiFlag : public IParameter
{
public:
	typedef unsigned int value_type;
	typedef std::function<bool(value_type)const> verifier_t;

	MultiFlag() { setDefault(); mSources = Source_Default; }
	virtual ~MultiFlag() { }
	
	virtual const char* getName() const = 0;
	virtual const char* getDescription() const = 0;

	virtual unsigned int numAliases() const { return 0; }
	virtual const char* getAlias(unsigned int = 0) { return nullptr; }
	virtual const char* getCategory() const = 0;
	virtual unsigned int numShorthands() const { return 0; }
	virtual char getShorthand(unsigned int = 0) const { return '\0'; }
	virtual const char* getEnvironment() const { return nullptr; }

	virtual bool isSet(SourceTypes source = Source_Any) const { return (mSources & source) == source; }
	virtual SourceTypes getSources() const { return mSources; }

	virtual value_type get() const;
	virtual void set(value_type value, SourceTypes source);
	virtual void inc(SourceTypes source);
	virtual void setValue(const char* inp, SourceTypes source);

	virtual value_type getDefault() const { return 0; }
	virtual verifier_t getVerifier() const { return verifier_t(); }

private:
	value_type mValue;
	SourceTypes mSources;
};

MultiFlag& GetMultiflag(const char* name);

}
