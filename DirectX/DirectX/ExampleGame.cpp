#include "ExampleGame.h"
#include "MainEngine.h"

namespace MyGame
{
	ExampleGame::ExampleGame(): EngineGame()
	{
	}

	ExampleGame::~ExampleGame()
	{
		
	}

	void ExampleGame::Init()
	{
		bitmap = Engine::Get()->GetScene()->Create<Bitmap>();
		bitmap->Init(L"../DirectX/data/avatar.png", 256, 256);

		x = y = 200.0f;
		bitmap->SetPosition(x, y);
	}

	void ExampleGame::DeInit()
	{
		delete this;
	}

	void ExampleGame::Update(float dt)
	{
		auto input = Engine::Get()->GetInput();
		float speed = 500.0f;

		if (input->IsKeyDown(DirectInputKey::UpArrow))
		{
			y -= speed * dt;
		}

		if (input->IsKeyDown(DirectInputKey::DownArrow))
		{
			y += speed * dt;
		}

		if (input->IsKeyDown(DirectInputKey::LeftArrow))
		{
			x -= speed * dt;
		}

		if (input->IsKeyDown(DirectInputKey::RightArrow))
		{
			x += speed * dt;
		}

		bitmap->SetPosition(x, y);
	}
}
