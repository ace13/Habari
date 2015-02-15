#pragma once

#include "Habari.hpp"

namespace Habari
{
	
class Flag : public IParameter
{
public:
	Flag() { setDefault(); mSource = Source_Default; }
	virtual ~Flag() { }
	
	virtual const char* getName() const = 0;
	virtual const char* getDescription() const = 0;

	virtual const char* getCategory() const { return nullptr; }
	virtual const char* getConfigName() const { return nullptr; }
	virtual char getShorthand() const { return '\0'; }
	virtual const char* getEnvironment() const { return nullptr; }

	virtual bool isSet(SourceTypes source = Source_Any) const;
	virtual bool get() const;
	virtual SourceTypes getSource() const;

	virtual void setValue(bool value = true);

protected:
	virtual void setDefault() { mValue = false; }
	virtual void setVerifier() { }

	void setVerifier(const std::function<bool() const>&);

	virtual bool hasCategory() const { return false; }
	virtual bool hasConfigName() const { return false; }
	virtual bool hasShorthand() const { return false; }
	virtual bool hasEnvironment() const { return false; }

private:
	bool mValue;
	SourceTypes mSource;
	std::function<bool()const> mVerifier;
};

}
