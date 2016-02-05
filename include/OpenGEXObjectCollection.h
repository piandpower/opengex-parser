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

		};
	public:
		GeometryObject()
		{
			visible = true;
			shadow = true;
			motionBlur = true;
		}

		virtual void processSubNode(ODDLParser::DDLNode* node);
	public:
		bool visible;
		bool shadow;
		bool motionBlur;
	};
}