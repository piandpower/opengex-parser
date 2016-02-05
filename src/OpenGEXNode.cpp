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
		else
		{
			Structure::processSubNode(node);
		}
	}

}