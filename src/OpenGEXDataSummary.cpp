#include "OpenGEXPCH.h"
#include "OpenGEXDataSummary.h"
#include "OpenGEXStructure.h"

namespace OGEXParser
{
	OpenGEXDataSummary::OpenGEXDataSummary()
	{
		distanceScale = 1.0f;
		angleScale = 1.0f;
		timeScale = 1.0f;
		upDirection = UAD_Z;
	}

	OpenGEXDataSummary::~OpenGEXDataSummary()
	{
		for (size_t i = 0; i < allStructures.size(); ++i)
		{
			delete allStructures[i];
		}

		allStructures.clear();
	}

}