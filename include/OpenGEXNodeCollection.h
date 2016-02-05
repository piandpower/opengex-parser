#pragma once

#include "OpenGEXCommon.h"
#include "OpenGEXNode.h"

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT GeometryNode : public NodeStructe
	{
	public:
		std::vector<std::string> MaterialRefNames;
	};
}