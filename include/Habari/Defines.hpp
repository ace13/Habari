#pragma once

#define HABARI_PARAMETERS_BEGIN namespace Habari { \
namespace Params {

#define HABARI_PARAMETERS_END } \
}

#define HABARI_FLAG(FlagName, FlagDescription) struct FlagName##_t : public Habari::Flag { \
const char* getName() const { return FlagName; } \
const char* getDescription() const { return Description; }

#define HABARI_MULTIFLAG(FlagName, FlagDescription) struct FlagName##_t : public Habari::MultiFlag { \
const char* getName() const { return FlagName; } \
const char* getDescription() const { return Description; }

#define HABARI_PARAMETER(FlagName, FlagType, FlagDescription) struct FlagName##_t : public Habari::Parameter<FlagType> { \
const char* getName() const { return FlagName; } \
const char* getDescription() const { return Description; } \

#define HABARI_END(FlagName) } FlagName; Habari::RegisterParameter(FlagName);

#define HABARI_CATEGORY(Category) const char* getCategory() const { return #Category; } protected: bool hasCategory() const { return true; } public:
#define HABARI_SHORTHAND(Shorthand) char getShorthand() const { return Shorthand; } protected: bool hasShorthand() const { return true; } public:
#define HABARI_ENVIRONMENT(Environment) const char* getEnvironment() const { return #Environment; } protected: bool hasEnvironment() const { return true; } public:
#define HABARI_CONFIG(ConfigName) const char* getConfigName() const { return #ConfigName; } protected: bool hasConfigName() const { return true; } public:

#define HABARI_VARIFIER(Code) protected: void setVerifier() { setVerifier(Code); } public:
#define HABARI_DEFAULT(DefaultValue) protected: void setDefault() { setValue(DefaultValue); } public:
