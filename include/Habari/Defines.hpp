#pragma once

#if 1
#define __HABARI_VA_NARG(...) __HABARI_VA_NARG_II((__HABARI_VA_NARG_PREFIX_ ## __VA_ARGS__ ## __HABARI_VA_NARG_POSTFIX,5,4,3,2,1,0))
#define __HABARI_VA_NARG_II(__args) __HABARI_VA_NARG_I __args
#define __HABARI_VA_NARG_PREFIX___HABARI_VA_NARG_POSTFIX ,,,,,0
#define __HABARI_VA_NARG_I(_1,_2,_3,_4,_5,N,...) N
#else
#define __HABARI_VA_NARG(...) __HABARI_VA_NARG_(__VA_ARGS__,5,4,3,2,1)
#define __HABARI_VA_NARG_(...) __HABARI_VA_NARG_N(__VA_ARGS__)
#define __HABARI_VA_NARG_N(_1,_2,_3,_4,_5,N,...) N
#endif

#define HABARI_PARAMETERS_BEGIN namespace Habari { \
namespace ParamDefs {

#define HABARI_PARAMETERS_END } \
}

#define HABARI_FLAG(FlagName, FlagDescription) struct FlagName##_t : public ::Habari::Flag { \
FlagName##_t() : ::Habari::Flag() { set(getDefault(), Source_Default); } \
const char* getName() const { return #FlagName; } \
const char* getDescription() const { return FlagDescription; }

#define HABARI_MULTIFLAG(FlagName, FlagDescription) struct FlagName##_t : public ::Habari::MultiFlag { \
FlagName##_t() : ::Habari::MultiFlag() { set(getDefault(), Source_Default); } \
const char* getName() const { return #FlagName; } \
const char* getDescription() const { return FlagDescription; }

#define HABARI_PARAMETER(FlagName, FlagType, FlagDescription) struct FlagName##_t : public ::Habari::Parameter<FlagType> { \
FlagName##_t() : ::Habari::Parameter<FlagType>() { set(getDefault(), Source_Default); } \
const char* getName() const { return #FlagName; } \
const char* getDescription() const { return FlagDescription; } \
void setValue(const char* inp, SourceTypes source) { \
	FlagType val = ::Habari::Parse<FlagType>(inp); \
	auto ver = getVerifier(); \
	if (ver && !ver(val)) \
		return; \
	set(val, source); \
} \

#define HABARI_END(FlagName) }; \
} \
namespace Params { ::Habari::ParamDefs::FlagName##_t FlagName; } \
namespace ParamDefs { \
	bool FlagName##_reg = ::Habari::RegisterParameter(static_cast<::Habari::IParameter*>(&::Habari::Params::FlagName));

#define HABARI_ALIASES(...) unsigned int numAliases() const { return __HABARI_VA_NARG(__VA_ARGS__); }\
const char* getAlias(unsigned int i = 0) const { \
	const char* sAliases[] = { __VA_ARGS__ };\
	if (i >= numAliases()) \
		return nullptr; \
	return sAliases[i];\
}
#define HABARI_CATEGORY(Category) const char* getCategory() const { return #Category; }
#define HABARI_SHORTHAND(...) unsigned int numShorthands() const { return __HABARI_VA_NARG(__VA_ARGS__); }\
char getShorthand(unsigned int i = 0) const { \
	const char sShorthands[] = { __VA_ARGS__ };\
	if (i >= numShorthands()) \
		return '\0'; \
	return sShorthands[i];\
}
#define HABARI_ENVIRONMENT(Environment) const char* getEnvironment() const { return #Environment; }

#define HABARI_VERIFIER_BEGIN verifier_type getVerifier() const { return
#define HABARI_VERIFIER_END ; }
#define HABARI_DEFAULT(DefaultValue) value_type getDefault() const { return DefaultValue; }
#define HABARI_VALUENAME(Name)
