#pragma once

#if defined(_MSC_VER)
#   define TAG_DLL_EXPORT __declspec(dllexport)
#   define TAG_DLL_IMPORT __declspec(dllimport )
#   ifdef OPENGEXPARSER_BUILD
#       define DLL_OPENGEXPARSER_EXPORT TAG_DLL_EXPORT
#   else
#       define DLL_OPENGEXPARSER_EXPORT TAG_DLL_IMPORT
#   endif // OPENDDLPARSER_BUILD
#   pragma warning( disable : 4251 )
#else
#   define DLL_OPENGEXPARSER_EXPORT
#endif // _WIN32

#include <string>
