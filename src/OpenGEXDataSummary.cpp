#include "OpenGEXPCH.h"
#include "OpenGEXDataSummary.h"

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

	}

}