#include "ActionButton.h"
#include <MainEngine.h>

namespace MagicIdle
{
	void ActionButton::Init()
	{
		_onTexture = Engine::Get()->Resources()->GetTexture("ActionButtonOn");
		_offTexture = Engine::Get()->Resources()->GetTexture("ActionButtonOff");

		_button = Engine::Get()->Scene()->Create<Button>();
		_button->SetTexture(_offTexture);
		_button->SetScale(.66f, .66f);
		_button->SetParent(this);
	}
	
	void ActionButton::Update()
	{
		if (_button->Pressed()) 
		{
			_button->SetTexture(_onTexture);
		}

		if (_button->Released())
		{
			_button->SetTexture(_offTexture);
		}
	}
}