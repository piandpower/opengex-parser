#pragma once

#include "OpenGEXCommon.h"
#include "OpenGEXNode.h"

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT GeometryNode : public NodeStructe
	{
	public:
		GeometryNode();

		virtual void processSubNode(ODDLParser::DDLNode* node) override;

		virtual void updateReference(class OpenGEXDataSummary* dataSummary) override;
	public:
		std::vector<std::string> materialRefNames;

	public:
		class GeometryObject* geometryObject;
	};
}