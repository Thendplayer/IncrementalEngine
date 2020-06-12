 #include "ActionButtonView.h"
#include <MainEngine.h>

namespace MagicIdle
{
	void ActionButtonView::Init()
	{
		Button::Init();

		SetTexture(Engine::Get()->Resources()->GetTexture("ActionButtonOff"));
		SetScale(.66f, .66f);
		
		_pressedSprite = Engine::Get()->Scene()->Create<Sprite>(this);
		_pressedSprite->SetPosition(0, 0);
		_pressedSprite->SetTexture(Engine::Get()->Resources()->GetTexture("ActionButtonOn"));
		_pressedSprite->SetActive(false);

		_buttonSound = Engine::Get()->Resources()->GetSound("Crystal");
	}
	
	void ActionButtonView::Update(float dt)
	{
		if (Pressed())
		{
			Engine::Get()->Audio()->Play(_buttonSound);
			_pressedSprite->SetActive(true);
		}

		if (Released())
		{
			_pressedSprite->SetActive(false);
		}

		Button::Update(dt);
	}
}