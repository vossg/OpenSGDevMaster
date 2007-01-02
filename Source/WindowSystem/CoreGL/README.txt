This directory contains an OpenSG window class that allows to integrate OpenSG into applications written using the native Mac OS CoreGL API.

CoreGL is the basis for two other OpenGL APIs on the Mac - AGL, the Carbon (C++) API, and NSOpenGL, the Cocoa (Objective-C) API. It is possible to convert AGL and NSOpenGL contexts into CoreGL contexts, but the Apple documentation says that this introduces a performance penalty. For this reason, there are different OpenSG windows for these APIs.

CoreGL can only be used for fullscreen rendering.

There is also a small test program called "testWindowCoreGL.cpp" that demonstrates how to use the OpenSG CoreGL window class.

- Patrick Daehne
