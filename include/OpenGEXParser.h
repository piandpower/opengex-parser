#pragma once

#include "OpenGEXCommon.h"
#include "OpenGEXStructureCollection.h"
#include "OpenGEXNodeCollection.h"
#include "OpenGEXObjectCollection.h"
#include "OpenGEXDataSummary.h"

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT OpenGEXParser
	{
	public:
		OpenGEXParser();

		virtual ~OpenGEXParser();

		bool parse(const char* buffer, int32 len);

		OpenGEXDataSummary* getDataSummary() { return dataSummary; }

		void clear();

	protected:
		void updateReference();

		void processNodes(ODDLParser::DDLNode* node);

		void processMetricNode(ODDLParser::DDLNode* node);

		void processGeometryNode(ODDLParser::DDLNode* node);

		Structure* createStructure(const std::string& identifier);

		void pushStrutureToDataSummary(Structure* newStruture);

		void pushNodeToDataSummary(NodeStructe* newNodeStructure);

		void pushObjectToDataSummary(ObjectStructure* newObjectStructure);

	protected:
		OpenGEXDataSummary* dataSummary;

	private:
		struct DImplementStruct;
		DImplementStruct* dImpl;
	};
}
