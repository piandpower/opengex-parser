#pragma once

#include "OpenGEXCommon.h"

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT Structure
	{
	public:
		virtual ~Structure() {}

	public:
		std::string name;
	};
}