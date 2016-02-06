#pragma once

#include "OpenGEXCommon.h"
#include "OpenGEXTypes.h"

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT Structure
	{
	public:
		virtual ~Structure() {}

		virtual void processSubNode(ODDLParser::DDLNode* node);
	public:
		std::string name;
	};
}