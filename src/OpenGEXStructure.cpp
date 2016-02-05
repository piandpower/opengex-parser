#include "OpenGEXPCH.h"
#include "OpenGEXStructure.h"

namespace OGEXParser
{
	void Structure::processSubNode(ODDLParser::DDLNode* node)
	{
		std::string tokenType = node->getType();

		if (tokenType == "name")
		{
			name = node->getValue()->getString();
		}
	}

}