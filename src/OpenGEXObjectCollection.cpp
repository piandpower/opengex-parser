#include "OpenGEXPCH.h"
#include "OpenGEXObjectCollection.h"

namespace OGEXParser
{
	void GeometryObject::processSubNode(ODDLParser::DDLNode* node)
	{
		if (!node)
			return;

		std::string tokenType = node->getType();
		if (tokenType == "Mesh")
		{
			processSubNode(node);
		}
		else
		{
			ObjectStructure::processSubNode(node);
		}
	}

	static int32 getPrimitiveTypeFromString(const std::string& primitiveStr)
	{
		if (primitiveStr == "points")
		{
			return PT_Points;
		}
		else if (primitiveStr == "lines")
		{
			return PT_Lines;
		}
		else if (primitiveStr == "line_strip")
		{
			return PT_LineStrip;
		}
		else if (primitiveStr == "triangles")
		{
			return PT_Triangles;
		}
		else if (primitiveStr == "triangle_strip")
		{
			return PT_TriangleStrip;
		}
		else if (primitiveStr == "quads")
		{
			return PT_Quads;
		}

		return PT_Triangles;
	}

	static void fillVector2D(Vector2D& vector2D, Value* val)
	{
		Value* iterVal = val;
		for (int32 i = 0; i < 2; ++i)
		{
			if (!iterVal)
				break;

			vector2D.data[i] = iterVal->getFloat();
		}
	}

	static void fillVector3D(Vector3D& vector3D, Value* val)
	{
		Value* iterVal = val;
		for (int32 i = 0; i < 3; ++i)
		{
			if (!iterVal)
				break;

			vector3D.data[i] = iterVal->getFloat();
		}
	}

	static void fillVector4D(Vector4D& vector4D, Value* val)
	{
		Value* iterVal = val;
		int32 i = 0;
		for (i = 0; i < 4; ++i)
		{
			if (!iterVal)
			{
				break;
			}

			vector4D.data[i] = iterVal->getFloat();
		}

		for (; i < 4; ++i)
		{
			vector4D.data[i] = 1.0f;
		}
	}

	static void copyVector2DArray(std::vector<Vector2D>& vector2DArray, DataArrayList* dataArray)
	{
		for (size_t i = 0; i < dataArray->size(); ++i)
		{
			Value* val = dataArray->m_dataList;
			Vector2D vec2D;
			fillVector2D(vec2D, val);
			vector2DArray.push_back(vec2D);
			dataArray = dataArray->m_next;
		}
	}

	static void copyVector3DArray(std::vector<Vector3D>& vector3DArray, DataArrayList* dataArray)
	{
		for (size_t i = 0; i < dataArray->size(); ++i)
		{
			Value* val = dataArray->m_dataList;
			Vector3D vec3D;
			fillVector3D(vec3D, val);
			vector3DArray.push_back(vec3D);
			dataArray = dataArray->m_next;
		}
	}

	static void copyVector4DArray(std::vector<Vector4D>& vector4DArray, DataArrayList* dataArray)
	{
		for (size_t i = 0; i < dataArray->size(); ++i)
		{
			Value* val = dataArray->m_dataList;
			Vector4D vec4D;
			fillVector4D(vec4D, val);
			vector4DArray.push_back(vec4D);
			dataArray = dataArray->m_next;
		}
	}

	static void copyIndexArray(std::vector<unsigned_int32>& indices, DataArrayList* dataArray)
	{
		for (size_t i = 0; i < dataArray->size(); ++i)
		{
			Value* val = dataArray->m_dataList;
			while (val)
			{
				unsigned_int32 index = val->getUnsignedInt32();
				indices.push_back(index);
				val = val->m_next;
			}
			dataArray = dataArray->m_next;
		}
	}

	void GeometryObject::processMeshNode(ODDLParser::DDLNode* node)
	{
		Mesh mesh;
		int32 lod = 0;
		Property* prop = node->getProperties();
		while (prop)
		{
			if (*prop->m_key == "lod")
			{
				Value* propVal = prop->m_value;
				lod = propVal->getInt32();
				mesh.lod = lod;
			}
			else if (*prop->m_key == "primitive")
			{
				Value* propVal = prop->m_value;
				std::string primitiveStr = propVal->getString();
				mesh.primitiveType = getPrimitiveTypeFromString(primitiveStr);
			}
			prop = prop->m_next;
		}

		DDLNode::DllNodeList childNodes = node->getChildNodeList();
		for (DDLNode::DllNodeList::iterator iter = childNodes.begin(); iter != childNodes.end(); ++iter)
		{
			DDLNode* childNode = *iter;
			std::string tokenType = childNode->getType();
			if (tokenType == "VertexArray")
			{
				processVertexArrayNode(childNode, mesh);
			}
			else if (tokenType == "IndexArray")
			{
				processIndexArrayNode(childNode, mesh);
			}
		}

		if (lod + 1 > lodMeshes.size())
			lodMeshes.resize(lod + 1);
		lodMeshes[lod] = mesh;
	}

	void GeometryObject::processVertexArrayNode(ODDLParser::DDLNode* node, Mesh& mesh)
	{
		Property* prop = node->getProperties();
		while (prop)
		{
			if (*prop->m_key == "attrib" && prop->m_value->m_type == Value::ddl_string)
			{
				std::string attribStr = prop->m_value->getString();
				if (attribStr == "position")
				{
					DataArrayList* dataArray = node->getDataArrayList();
					copyVector3DArray(mesh.positions, dataArray);
				}
				else if (attribStr == "normal")
				{
					DataArrayList* dataArray = node->getDataArrayList();
					copyVector3DArray(mesh.normals, dataArray);
				}
				else if (attribStr == "color")
				{
					DataArrayList* dataArray = node->getDataArrayList();
					copyVector4DArray(mesh.colors, dataArray);
				}
				else if (attribStr == "tangent")
				{
					DataArrayList* dataArray = node->getDataArrayList();
					copyVector3DArray(mesh.tangents, dataArray);
				}
				else if (attribStr == "bitangent")
				{
					DataArrayList* dataArray = node->getDataArrayList();
					copyVector3DArray(mesh.bitangents, dataArray);
				}
				else if (attribStr.find_first_of("texcoord") == 0)
				{
					int32 texIndex = 0;

					size_t nextTok = strlen("texcoord");
					if (nextTok < attribStr.size())
					{
						if (attribStr[nextTok] == '[' && attribStr[nextTok + 2] == ']')
						{
							char indexStr[4];
							indexStr[0] = attribStr[nextTok + 1];
							indexStr[1] = '\0';
							texIndex = atoi(indexStr);
						}
					}
					if (texIndex + 1 > mesh.texcoords.size())
					{
						mesh.texcoords.resize(texIndex + 1);
					}

					DataArrayList* dataArray = node->getDataArrayList();
					if (!dataArray)
						return;

					copyVector2DArray(mesh.texcoords[texIndex], dataArray);
				}
			}
			prop = prop->m_next;
		}
	}

	void GeometryObject::processIndexArrayNode(ODDLParser::DDLNode* node, Mesh& mesh)
	{
		Property* prop = node->getProperties();
		int32 material = 0;
		while (prop)
		{
			if (*prop->m_key == "material")
			{
				material = prop->m_value->getInt32();
			}

			if (material + 1 > mesh.indicesOfMaterial.size())
				mesh.indicesOfMaterial.resize(material + 1);

			copyIndexArray(mesh.indicesOfMaterial[material], node->getDataArrayList());
			prop = prop->m_next;
		}
	}

}