#pragma once

#include "OpenGEXCommon.h"
#include "OpenGEXNode.h"

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT GeometryNode : public NodeStructe
	{
	public:
		virtual void processSubNode(ODDLParser::DDLNode* node) override;
	public:
		std::vector<std::string> materialRefNames;
	};
}