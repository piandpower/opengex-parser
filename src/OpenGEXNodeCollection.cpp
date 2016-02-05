#include "OpenGEXPCH.h"
#include "OpenGEXNodeCollection.h"

namespace OGEXParser
{

	void GeometryNode::processSubNode(ODDLParser::DDLNode* node)
	{
		if (!node)
			return;

		std::string tokenType = node->getType();
		if (tokenType == "MaterialRef")
		{
			Property* prop = node->getProperties();
			if (prop && *prop->m_key == "index")
			{
				Value* propVal = prop->m_value;
				int32 index = propVal->getInt32();
				if (index + 1 > materialRefNames.size())
				{
					materialRefNames.resize(index + 1);
				}

				Reference* refValue = node->getReferences();
				if (refValue)
				{
					Text* refId = refValue->m_referencedName[0]->m_id;
					materialRefNames[index].assign(refId->m_buffer, refId->m_len);
				}
			}
		}
		else
		{
			NodeStructe::processSubNode(node);
		}
	}

}