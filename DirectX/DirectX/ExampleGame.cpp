#include "ExampleGame.h"
#include "MainEngine.h"

namespace MyGame
{
	void ExampleGame::Init()
	{
		_actor = Engine::Get()->GetScene()->Create<Actor>();
		_actor->SetPosition(0, 0);
		_actor->SetRotation(0);
		_actor->SetScale(1, 1);
		_actor->SetTexture(Engine::Get()->GetResources()->GetTexture("Sonic"));
	}

	void ExampleGame::DeInit()
	{
		delete this;
	}

	void ExampleGame::Update(float dt)
	{
		auto input = Engine::Get()->GetInput();
		
		if (input->IsKeyDown(DirectInputKey::W))
		{
			_actor->SetScale(_actor->GetScale().x + 2 * dt, _actor->GetScale().y + 2 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::S))
		{
			_actor->SetScale(_actor->GetScale().x - 2 * dt, _actor->GetScale().y - 2 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::UpArrow))
		{
			_actor->SetPosition(_actor->GetPosition().x, _actor->GetPosition().y - 100 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::DownArrow))
		{
			_actor->SetPosition(_actor->GetPosition().x, _actor->GetPosition().y + 100 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::RightArrow))
		{
			_actor->SetPosition(_actor->GetPosition().x + 100 * dt, _actor->GetPosition().y);
		}
		
		if (input->IsKeyDown(DirectInputKey::LeftArrow))
		{
			_actor->SetPosition(_actor->GetPosition().x - 100 * dt, _actor->GetPosition().y);
		}
		
		if (input->IsKeyDown(DirectInputKey::Space))
		{
			_actor->SetRotation(_actor->GetRotation() + 5000 * dt);
		}
	}
}
