Habari
======

A C++11 commandline/config/environment parser for program options.
Licensed under the MIT license, more information in the LICENSE file.

Mockup
======

```c++
HABARI_BEGIN_PARAMETERS
 
HABARI_FLAG(Version, "Prints the version of the compiled software and exits.")
HABARI_SHORTHAND('V')
HABARI_END
 
HABARI_MULTIFLAG(Verbose, "Enable verbose output")
HABARI_SHORTHAND('v')
HABARI_ENVIRONMENT(VERBOSE)
HABARI_VERIFIER([this]() -> bool { return getValue() < 5; }) // Only allow up to -vvvvv
HABARI_END(Verbose)
 
HABARI_FLAG(Fullscreen, "Run the program fullscreened")
HABARI_SHORTHAND('f')
HABARI_CONFIG(Fullscreen)
HABARI_END(Fullscreen)
 
HABARI_PARAMETER(Size, std::string, "Specify the size of the window")
HABARI_CATEGORY(Window)
HABARI_SHORTHAND('s')
HABARI_VERIFIER([](const std::string& input) -> bool { int x, y; return (sscanf(input.c_str(), "%dx%d", &x, &y) == 2 && x > 0 && y > 0); })
HABARI_CONFIG(Size)
HABARI_DEFAULT("1024x768")
HABARI_END(Size)
 
HABARI_PARAMETER(FPS, uint32_t, "FPS limit, specify 0 for no limit")
HABARI_CATEGORY(Window)
HABARI_CONFIG(FPSLimit)
HABARI_DEFAULT(60)
HABARI_END(FPS)
 
HABARI_END_PARAMETERS
```
