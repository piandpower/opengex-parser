#pragma once

#include "OpenGEXCommon.h"
#include "OpenGEXTypes.h"

namespace OGEXParser
{
	class Structure;

	class DLL_OPENGEXPARSER_EXPORT OpenGEXDataSummary
	{
		friend class OpenGEXParser;
	public:
		OpenGEXDataSummary();
		~OpenGEXDataSummary();

	public:
		float distanceScale;
		float angleScale;
		float timeScale;
		int32 upDirection; // UpAxisDirection enum

	protected:
		std::vector<Structure*> allStructures;   // almost everything stored here
	};
}
