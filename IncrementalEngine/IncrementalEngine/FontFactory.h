#ifndef _FONT_FACTORY_H
#define _FONT_FACTORY_H

#include "FW1FontWrapper.h"

namespace IncrementalEngine
{
	static class FontFactory
	{
	public:
		static IFW1Factory* Get();
		static void Release();

	private:
		static IFW1Factory* FACTORY_INSTANCE;
	};
}

#endif