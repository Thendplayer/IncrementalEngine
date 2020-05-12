#include "ExampleGame.h"
#include "MainEngine.h"

namespace MyGame
{
	void ExampleGame::Init()
	{
		_displayText = Engine::Get()->GetScene()->Create<Text>();
		_displayText->SetFont(L"Oswald");
		_displayText->SetFontSize(140);
		_displayText->SetText(L"Click the button.");
		_displayText->SetTextColor(63, 161, 227);
		_displayText->SetPosition(-125, -125);

		_background = Engine::Get()->GetScene()->Create<Sprite>();
		_background->SetTexture(Engine::Get()->GetResources()->GetTexture("Background"));
		_background->SetScale(.5f, .5f);

		_tap = Engine::Get()->GetScene()->Create<Tap>();
		_tap->SetScale(.5f, .5f);
		_tap->SetPosition(170, 125);
	}

	void ExampleGame::DeInit()
	{
	}

	void ExampleGame::Update(float dt)
	{
		_displayText->SetText(std::to_wstring(_tap->GetValue()));
	}
}
