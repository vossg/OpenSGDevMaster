// Includes
#ifdef OSG_BUILD_ACTIVE
#include <OSGTextFaceFactory.h>
#else
#include <OpenSG/OSGTextFaceFactory.h>
#endif
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    // Create a vector of strings.
    std::vector<std::string> families;

    // Fill the vector with the names of all font families installed
    // on the system
    OSG::TextFaceFactory::the()->getFontFamilies(families);

    // Iterate over the names
    std::vector<std::string>::const_iterator it;
    for (it = families.begin(); it != families.end(); ++it)
        std::cout << *it << std::endl;

    return EXIT_SUCCESS;
}
