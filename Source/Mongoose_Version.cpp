/* ========================================================================== */
/* === Source/Mongoose_Version.cpp ========================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library  Copyright (C) 2017-2018,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * -------------------------------------------------------------------------- */

#include "Mongoose_Version.hpp"
#include <sstream>

namespace Mongoose
{

int majorVersion()
{
    return Mongoose_VERSION_MAJOR;
}

int minorVersion()
{
    return Mongoose_VERSION_MINOR;
}

int patchVersion()
{
    return Mongoose_VERSION_PATCH;
}

std::string mongooseVersion()
{
    std::ostringstream stringStream;
    stringStream << majorVersion() << "." << minorVersion() << "." << patchVersion();
    return stringStream.str();
}

} // end namespace Mongoose