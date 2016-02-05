#pragma once

#include "OpenGEXCommon.h"
#include "OpenGEXStructure.h"
#include "OpenGEXTypes.h"

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT NodeStructe : public Structure
	{
	public:
		void processSubNode(ODDLParser::DDLNode* node);
	public:
		Matrix transform;
	};
}
