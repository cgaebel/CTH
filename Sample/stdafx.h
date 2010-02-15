#pragma once

// YOU HAVE TO HAVE THE FOLLOWING TWO LINES OF CODE.

// In my very special case, our Test.h is in a different directory.
// Basically, include "Test.h", wherever you put it.
#include "../Test/Test.h"

// Please note the VC++ Directories configuration property. I had to tweak it
// a bit to get this to work without me constantly having to copy the library
// during develpment. Put the lib wherever you want, just make sure the damn
// thing gets linked.
#pragma comment(lib, "Test.lib")

// #pragma comment(dll, "Test.dll")
// Oh wait I can't do that. Just ensure the .dll (Release version is best)
// is in the PATH somewhere. I suggest putting it in the same directory as your
// project file, but inside the output folder works too.
