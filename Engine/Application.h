
#pragma once

namespace MindMeld
{
	struct ApplicationInfo
	{
		const char* appName;

		unsigned windowWidth;
		unsigned windowHeight;

		unsigned majorVersion;
		unsigned minorVersion;
		unsigned microVersion;
	};
}