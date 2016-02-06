#pragma once

#include "OpenGEXCommon.h"
#include "OpenGEXObject.h"

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT GeometryObject : public ObjectStructure
	{
	public:
		struct Mesh
		{
			int32 lod;

			int32 primitiveType;

			std::vector<Vector3D> positions;
			std::vector<Vector3D> normals;
			std::vector<Vector4D> colors;
			std::vector<Vector3D> tangents;
			std::vector<Vector3D> bitangents;
			std::vector<std::vector<Vector2D>> texcoords;

			std::vector<std::vector<unsigned_int32>> indicesOfMaterial;

			Mesh()
			{
				lod = 0;
				primitiveType = PT_Triangles;
			}
		};
	public:
		GeometryObject()
		{
			visible = true;
			shadow = true;
			motionBlur = true;
		}

		virtual void processSubNode(ODDLParser::DDLNode* node);

	protected:
		void processMeshNode(ODDLParser::DDLNode* node);

		void processVertexArrayNode(ODDLParser::DDLNode* node, Mesh& mesh);
		
		void processIndexArrayNode(ODDLParser::DDLNode* node, Mesh& mesh);
	public:
		bool visible;
		bool shadow;
		bool motionBlur;

		std::vector<Mesh> lodMeshes;  // 0 is the highest lod
	};
}