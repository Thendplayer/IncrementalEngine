#include "ExampleGame.h"
#include "MainEngine.h"

namespace MyGame
{
	void ExampleGame::Init()
	{
		_sprite = Engine::Get()->GetScene()->Create<Sprite>();
		_sprite->SetPosition(0, 0);
		_sprite->SetRotation(0);
		_sprite->SetScale(1, 1);
		_sprite->SetTexture(Engine::Get()->GetResources()->GetTexture("Avatar"));

		Engine::Get()->GetSoundEngine()->Play(Engine::Get()->GetResources()->GetSound("Points"));
		_child = nullptr;
	}

	void ExampleGame::DeInit()
	{
	}

	void ExampleGame::Update(float dt)
	{
		auto input = Engine::Get()->GetInput();
		
		if (input->IsKeyDown(DirectInputKey::W))
		{
			_sprite->SetScale(_sprite->GetScale().x + 2 * dt, _sprite->GetScale().y + 2 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::S))
		{
			_sprite->SetScale(_sprite->GetScale().x - 2 * dt, _sprite->GetScale().y - 2 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::UpArrow))
		{
			_sprite->SetPosition(_sprite->GetPosition().x, _sprite->GetPosition().y - 100 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::DownArrow))
		{
			_sprite->SetPosition(_sprite->GetPosition().x, _sprite->GetPosition().y + 100 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::RightArrow))
		{
			_sprite->SetPosition(_sprite->GetPosition().x + 100 * dt, _sprite->GetPosition().y);
		}
		
		if (input->IsKeyDown(DirectInputKey::LeftArrow))
		{
			_sprite->SetPosition(_sprite->GetPosition().x - 100 * dt, _sprite->GetPosition().y);
		}
		
		if (input->IsKeyDown(DirectInputKey::Space))
		{
			_sprite->SetRotation(_sprite->GetRotation() + 200 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::P))
		{
			Engine::Get()->GetSoundEngine()->Play(Engine::Get()->GetResources()->GetSound("Points"));
		}

		if (input->IsKeyDown(DirectInputKey::C))
		{
			if (_child == nullptr)
			{
				_child = Engine::Get()->GetScene()->Create<Sprite>();
				_child->SetParent(_sprite);
				_child->SetPosition(0, 0);
				_child->SetRotation(0);
				_child->SetScale(1, 1);
				_child->SetTexture(Engine::Get()->GetResources()->GetTexture("Sonic"));
			}
		}
	}
}
