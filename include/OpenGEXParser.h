#pragma once

#include "OpenGEXCommon.h"
#include "OpenGEXStructureCollection.h"
#include "OpenGEXNodeCollection.h"
#include "OpenGEXObjectCollection.h"
#include "OpenGEXDataSummary.h"

namespace ODDLParser {
	class DDLNode;
	struct Context;
}

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT OpenGEXParser
	{
	public:
		OpenGEXParser();

		virtual ~OpenGEXParser();

		bool parse(const char* buffer, int32 len);

		OpenGEXDataSummary* getDataSummary() { return dataSummary; }

	protected:
		void processNodes(ODDLParser::DDLNode* node);

		void processMetricNode(ODDLParser::DDLNode* node);

	protected:
		OpenGEXDataSummary* dataSummary;

	private:
		struct DImplementStruct;
		DImplementStruct* dImpl;
	};
}
