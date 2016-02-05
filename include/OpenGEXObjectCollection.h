#pragma once

#include "OpenGEXCommon.h"
#include "OpenGEXObject.h"

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT GeometryObject : public ObjectStructure
	{
	public:
		GeometryObject()
		{
			visible = true;
			shadow = true;
			motionBlur = true;
		}
	public:
		bool visible;
		bool shadow;
		bool motionBlur;
	};
}