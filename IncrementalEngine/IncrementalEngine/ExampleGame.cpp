#include "ExampleGame.h"
#include "MainEngine.h"

namespace MyGame
{
	void ExampleGame::Init()
	{
		_background = Engine::Get()->Scene()->Create<Sprite>();
		_background->SetTexture(Engine::Get()->Resources()->GetTexture("Background"));
		_background->SetScale(.5f, .5f);

		_displayText = Engine::Get()->Scene()->Create<Text>();
		_displayText->SetFont(L"Oswald");
		_displayText->SetFontSize(140);
		_displayText->SetText(std::to_wstring(Engine::Get()->Storage()->GetInt("Tap")));
		_displayText->SetTextColor(63, 161, 227);
		_displayText->SetPosition(-125, -125);

		_tap = Engine::Get()->Scene()->Create<Tap>();
		_tap->SetPosition(155, 120);
		_tap->SetValue(Engine::Get()->Storage()->GetInt("Tap"));
	}

	void ExampleGame::DeInit()
	{
	}

	void ExampleGame::Update(float dt)
	{
		_displayText->SetText(std::to_wstring(_tap->GetValue()));
	}
}
