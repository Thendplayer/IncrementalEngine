#include "ExampleGame.h"
#include "MainEngine.h"

namespace MyGame
{
	void ExampleGame::Init()
	{
		_actor = Engine::Get()->GetScene()->Create<Actor>();
		_actor->SetPosition(100, 100);
		_actor->SetScale(0.5f, 0.5f);
		_actor->SetTexture(Engine::Get()->GetResources()->GetTexture("Avatar"));
	}

	void ExampleGame::DeInit()
	{
		delete this;
	}

	void ExampleGame::Update(float dt)
	{
		auto input = Engine::Get()->GetInput();
		
		if (input->IsKeyDown(DirectInputKey::UpArrow))
		{
			_actor->SetScale(_actor->GetScale().x + 2 * dt, _actor->GetScale().y + 2 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::DownArrow))
		{
			_actor->SetScale(_actor->GetScale().x - 2 * dt, _actor->GetScale().y - 2 * dt);
		}

		if (input->IsKeyDown(DirectInputKey::RightArrow))
		{
			_actor->SetPosition(_actor->GetPosition().x + 100 * dt, _actor->GetPosition().y);
		}

		if (input->IsKeyDown(DirectInputKey::LeftArrow))
		{
			_actor->SetPosition(_actor->GetPosition().x - 100 * dt, _actor->GetPosition().y);
		}
	}
}
