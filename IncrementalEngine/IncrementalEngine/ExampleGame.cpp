#include "ExampleGame.h"
#include "MainEngine.h"

namespace MyGame
{
	void ExampleGame::Init()
	{
		_background = Engine::Get()->GetScene()->Create<Sprite>();
		_background->SetTexture(Engine::Get()->GetResources()->GetTexture("Background"));
		_background->SetScale(.5f, .5f);

		_displayText = Engine::Get()->GetScene()->Create<Text>();
		_displayText->SetFont(L"Oswald");
		_displayText->SetFontSize(140);
		_displayText->SetText(L"Click the button.");
		_displayText->SetTextColor(63, 161, 227);
		_displayText->SetPosition(-125, -125);

		_tap = Engine::Get()->GetScene()->Create<Tap>();
		_tap->SetPosition(155, 120);
	}

	void ExampleGame::DeInit()
	{
	}

	void ExampleGame::Update(float dt)
	{
		_displayText->SetText(std::to_wstring(_tap->GetValue()));

		auto input = Engine::Get()->GetInput();
		
		if (input->IsKeyDown(DirectInputKey::W))
		{
			_tap->SetScale(_tap->GetScale().x + 2 * dt, _tap->GetScale().y + 2 * dt);
		}
		
		if (input->IsKeyDown(DirectInputKey::S))
		{
			_tap->SetScale(_tap->GetScale().x - 2 * dt, _tap->GetScale().y - 2 * dt);
		}
		
		if (input->IsKeyDown(DirectInputKey::UpArrow))
		{
			_tap->SetPosition(_tap->GetPosition().x, _tap->GetPosition().y - 100 * dt);
		}
		
		if (input->IsKeyDown(DirectInputKey::DownArrow))
		{
			_tap->SetPosition(_tap->GetPosition().x, _tap->GetPosition().y + 100 * dt);
		}
		
		if (input->IsKeyDown(DirectInputKey::RightArrow))
		{
			_tap->SetPosition(_tap->GetPosition().x + 100 * dt, _tap->GetPosition().y);
		}
		
		if (input->IsKeyDown(DirectInputKey::LeftArrow))
		{
			_tap->SetPosition(_tap->GetPosition().x - 100 * dt, _tap->GetPosition().y);
		}
		
		if (input->IsKeyDown(DirectInputKey::Space))
		{
			_tap->SetRotation(_tap->GetRotation() + 200 * dt);
		}
		
		if (input->IsKeyDown(DirectInputKey::P))
		{
			Engine::Get()->GetSoundEngine()->Play(Engine::Get()->GetResources()->GetSound("Points"));
		}
	}
}
