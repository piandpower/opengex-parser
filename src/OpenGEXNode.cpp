#include "OpenGEXPCH.h"
#include "OpenGEXNode.h"

namespace OGEXParser
{

	//------------------------------------------------------------------------------------------------
	static void setMatrix(NodeStructe *nodeStructure, DataArrayList *transformData) 
	{
		float* m = nodeStructure->transform.data;

		Value *next(transformData->m_dataList->m_next);
		m[0] = transformData->m_dataList->getFloat();
		size_t i(1);
		while (next != NULL) 
		{
			m[i] = next->getFloat();
			next = next->m_next;
			i++;
		}
	}

	void NodeStructe::processSubNode(ODDLParser::DDLNode* node)
	{
		if (!node)
			return;

		std::string tokenType = node->getType();
		if (tokenType == "Transform")
		{
			DataArrayList *transformData(node->getDataArrayList());
			if (NULL != transformData) 
			{
				if (transformData->m_numItems != 16) 
				{
					return;
				}
				setMatrix(this, transformData);
			}
		}
		else if (tokenType == "ObjectRef")
		{
			Reference* refValue = node->getReferences();
			if (refValue)
			{
				Text* refId = refValue->m_referencedName[0]->m_id;
				objectRefName.assign(refId->m_buffer, refId->m_len);
			}
		}
		else
		{
			Structure::processSubNode(node);
		}
	}

}