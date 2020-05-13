#include "Tap.h"
#include "MainEngine.h"

namespace MyGame
{
	void Tap::Init()
	{
		_button = Engine::Get()->GetScene()->Create<Button>();
		_button->SetTexture(Engine::Get()->GetResources()->GetTexture("Button4"));
		_button->SetScale(.4f, .4f);
		_button->SetParent(this);

		_text = Engine::Get()->GetScene()->Create<Text>();
		_text->SetFont(L"Oswald");
		_text->SetFontSize(164);
		_text->SetText(L"TAP");
		_text->SetTextColor(63, 161, 227);
		_text->SetParent(_button, false);
		
	}
	
	void Tap::Update()
	{
		if (_button->Pressed())
		{
			_button->SetTexture(Engine::Get()->GetResources()->GetTexture("Button5"));
			_text->SetTextColor(40, 100, 138);
			_value++;
		}

		if (_button->Released())
		{
			_button->SetTexture(Engine::Get()->GetResources()->GetTexture("Button4"));
			_text->SetTextColor(63, 161, 227);
		}
	}
	
	int Tap::GetValue()
	{
		return _value;
	}
}