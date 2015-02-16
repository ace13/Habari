#pragma once

#define __HABARI_VA_NUM_ARGS(...) __HABARI_VA_NUM_ARGS_IMPL(__VA_ARGS__,5,4,3,2,1)
#define __HABARI_VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,N,...) N

#define HABARI_PARAMETERS_BEGIN namespace Habari { \
namespace ParamDefs {

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
void setValue(const char* inp, SourceTypes source) { set(Habari::Parse<FlagType>(inp), source); } \

#define HABARI_END(FlagName) }; \
} \
namespace Params { Habari::ParamDefs::FlagName##_t FlagName; } \
namespace ParamDefs { \
	bool FlagName##_reg = Habari::RegisterParameter(static_cast<Habari::IParameter*>(&Habari::Params::FlagName));

#define HABARI_ALIASES(Alias...) unsigned int numAliases() const { return __HABARI_VA_NUM_ARGS(Alias...); }\
const char* getAlias(unsigned int i = 0) const { \
	const char* sAliases[] = { Alias... };\
	if (i >= __HABARI_VA_NUM_ARGS(Alias...)) \
		return nullptr; \
	return sAliases[i];\
}
#define HABARI_CATEGORY(Category) const char* getCategory() const { return #Category; }
#define HABARI_SHORTHAND(Shorthand...) unsigned int numShorthand() const { return __HABARI_VA_NUM_ARGS(Shorthand...); }\
const char getShorthand(unsigned int i = 0) const { \
	const char sShorthands[] = { Shorthand... };\
	if (i >= __HABARI_VA_NUM_ARGS(Shorthand...)) \
		return '\0'; \
	return sShorthands[i];\
}
#define HABARI_ENVIRONMENT(Environment) const char* getEnvironment() const { return #Environment; }

#define HABARI_VARIFIER(Code) verifier_type getVerifier() const { return Code; }
#define HABARI_DEFAULT(DefaultValue) value_type getDefault() const { return DefaultValue; }

#undef __HABARI_VA_NUM_ARGS
#undef __HABARI_VA_NUM_ARGS_IMPL
