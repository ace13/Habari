#include <Habari/Defines.hpp>
#include <Habari/Flag.hpp>
#include <Habari/MultiFlag.hpp>
#include <Habari/Parameter.hpp>
#include <iostream>

HABARI_BEGIN_PARAMETERS

HABARI_FLAG(Help, "Prints the usage and exits")
	HABARI_SHORTHAND('h')
HABARI_END(Help)

HABARI_FLAG(Version, "Prints the version of the compiled software and exits.")
	HABARI_SHORTHAND('V')
HABARI_END(Version)
 
HABARI_MULTIFLAG(Verbose, "Enable verbose output")
	HABARI_SHORTHAND('v')
	HABARI_ENVIRONMENT(VERBOSE)
	// Only allow stacking up to -vvvv
	HABARI_VERIFIER([](unsigned int newVal) -> bool { return newVal < 5; })
	// 'Warning' level by default
	HABARI_DEFAULT(2)
	// Defaults to the parameter name, uppercased
	HABARI_VALUENAME(LEVEL)
HABARI_END(Verbose)
 
HABARI_FLAG(Fullscreen, "Run the program fullscreened")
	HABARI_SHORTHAND('f')
	HABARI_CATEGORY(Window)
HABARI_END(Fullscreen)
 
HABARI_PARAMETER(Size, std::string, "Specify the size of the window")
	Habari_ALIASES("Geometry", "Geom")
	HABARI_CATEGORY(Window)
	HABARI_SHORTHAND('s', 'g')
	// Verify that it's a valid resolution
	HABARI_VERIFIER([](const std::string& input) -> bool { int x, y; return (sscanf(input.c_str(), "%dx%d", &x, &y) == 2 && x > 0 && y > 0); })
	HABARI_DEFAULT("1024x768")
HABARI_END(Size)
 
HABARI_PARAMETER(FPS, uint32_t, "FPS limit, specify 0 for no limit")
	HABARI_CATEGORY(Window)
	HABARI_DEFAULT(60)
HABARI_END(FPS)

HABARI_FLAG(Quit, "Quits the program immediately")
HABARI_END(Quit)

HABARI_END_PARAMETERS

enum Verbosity {
	Fatal = 0,
	Error,
	Warning,
	Info,
	Debug
};

int main(int argc, char** argv)
{
	Habari::ParseEnvironment();
	int unparsed = Habari::ParseCommandline(argc, argv);

	if (Habari::HasErrors())
	{
		Habari::PrintErrors();
		std::cout << "Use --help for usage." << std::endl;
		return 1;
	}

	if (Habari::Params::Help.get() || unparsed == 0)
	{
		Habari::PrintUsage("<input file>");
		std::cout << "Also, this example is just a very basic mockup of the final system." << std::endl;
		return 0;
	}

	// Direct variable access
	if (Habari::Params::Version.get())
	{
		std::cout << "Version 0.0.0.1" << std::endl;
		return 0;
	}

	std::cout << "Launching application in " << Habari::Params::Size.get() << (Habari::Params::Fullscreen.get() ? " fullscreen" : " windowed") << " mode." << std::endl;

	// Parameter lookup
	if (Habari::GetMultiflag("Verbose").get() >= Info)
		std::cout << "FPS will be limited to " << Habari::GetParameter<uint32_t>("FPS").get() << " frames per second." << std::endl;

	return 0;
}