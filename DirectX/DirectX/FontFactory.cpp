#include "FontFactory.h"
#include "Utils.h"

namespace IncrementalEngine 
{
	IFW1Factory* FontFactory::FACTORY_INSTANCE = nullptr;

	IFW1Factory* FontFactory::Get()
	{
		if (FACTORY_INSTANCE == nullptr)
		{
			HRESULT result = FW1CreateFactory(FW1_VERSION, &FACTORY_INSTANCE);
			if (FAILED(result))
			{
				MessageBox(NULL, L"FW1CreateFactory", L"Error", MB_OK);
				return NULL;
			}
		}

		return FACTORY_INSTANCE;
	}
	
	void FontFactory::Release()
	{
		CHECKED_RELEASE(FACTORY_INSTANCE);
	}
}