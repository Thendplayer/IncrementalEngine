 #include "ActionButtonView.h"
#include <MainEngine.h>

namespace MagicIdle
{
	void ActionButtonView::Init()
	{
		Button::Init();

		_onTexture = Engine::Get()->Resources()->GetTexture("ActionButtonOn");
		_offTexture = Engine::Get()->Resources()->GetTexture("ActionButtonOff");

		SetScale(.66f, .66f);
		SetTexture(_offTexture);
	}
	
	void ActionButtonView::Update()
	{
		if (Pressed()) 
		{
			SetTexture(_onTexture);
		}

		if (Released())
		{
			SetTexture(_offTexture);
		}

		Button::Update();
	}
}