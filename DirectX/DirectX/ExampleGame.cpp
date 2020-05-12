#include "ExampleGame.h"
#include "MainEngine.h"

namespace MyGame
{
	void ExampleGame::Init()
	{
		//Engine::Get()->GetSoundEngine()->Play(Engine::Get()->GetResources()->GetSound("Points"));

		////CYAN
		//_child = Engine::Get()->GetScene()->Create<Sprite>();
		////_child->SetParent(_text);
		//_child->SetPosition(0, 0);
		//_child->SetRotation(0);
		//_child->SetScale(1, 1);
		//_child->SetTexture(Engine::Get()->GetResources()->GetTexture("Sonic"));
		//
		////YELLOW
		//_text = Engine::Get()->GetScene()->Create<Text>();
		//_text->SetPosition(100, 100);
		//_text->SetRotation(0);
		//_text->SetScale(1, 1);
		//
		//_text->SetFont(L"FunnyKid");
		//_text->SetFontSize(120);
		//_text->SetText(L"TEST");
		//_text->SetTextColor(255, 255, 0, 1);
		//
		////BLUE
		//_sprite = Engine::Get()->GetScene()->Create<Sprite>();
		//_sprite->SetPosition(200, 200);
		//_sprite->SetRotation(0);
		//_sprite->SetScale(.5f, .5f);
		//_sprite->SetTexture(Engine::Get()->GetResources()->GetTexture("Avatar"));

		_button = Engine::Get()->GetScene()->Create<Button>();
		_button->SetPosition(200, 250);
		_button->SetRotation(0);
		_button->SetScale(1, 1);
		_button->SetTexture(Engine::Get()->GetResources()->GetTexture("Sonic"));

		_sprite = Engine::Get()->GetScene()->Create<Sprite>();
		_sprite->SetPosition(t * 10, t * 10);
		_sprite->SetRotation(0);
		_sprite->SetScale(.25f, .25f);
		_sprite->SetTexture(Engine::Get()->GetResources()->GetTexture("Avatar"));
	}

	void ExampleGame::DeInit()
	{
	}

	void ExampleGame::Update(float dt)
	{
		t -= dt * 10;
		if (_button->Released()) 
		{
			_sprite->SetPosition(t * 10, t * 10);
		}

		//auto input = Engine::Get()->GetInput();
		//
		//if (input->IsKeyDown(DirectInputKey::W))
		//{
		//	_text->SetScale(_text->GetScale().x + 2 * dt, _text->GetScale().y + 2 * dt);
		//}
		//
		//if (input->IsKeyDown(DirectInputKey::S))
		//{
		//	_text->SetScale(_text->GetScale().x - 2 * dt, _text->GetScale().y - 2 * dt);
		//}
		//
		//if (input->IsKeyDown(DirectInputKey::UpArrow))
		//{
		//	_text->SetPosition(_text->GetPosition().x, _text->GetPosition().y - 100 * dt);
		//}
		//
		//if (input->IsKeyDown(DirectInputKey::DownArrow))
		//{
		//	_text->SetPosition(_text->GetPosition().x, _text->GetPosition().y + 100 * dt);
		//}
		//
		//if (input->IsKeyDown(DirectInputKey::RightArrow))
		//{
		//	_text->SetPosition(_text->GetPosition().x + 100 * dt, _text->GetPosition().y);
		//}
		//
		//if (input->IsKeyDown(DirectInputKey::LeftArrow))
		//{
		//	_text->SetPosition(_text->GetPosition().x - 100 * dt, _text->GetPosition().y);
		//}
		//
		//if (input->IsKeyDown(DirectInputKey::Space))
		//{
		//	_text->SetRotation(_text->GetRotation() + 200 * dt);
		//}
		//
		//if (input->IsKeyDown(DirectInputKey::P))
		//{
		//	Engine::Get()->GetSoundEngine()->Play(Engine::Get()->GetResources()->GetSound("Points"));
		//}
	}
}
