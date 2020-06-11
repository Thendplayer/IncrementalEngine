#include "Orb.h"

#include <MainEngine.h>

namespace MagicIdle 
{
	void Orb::Init()
	{
		Button::Init();
		SetTexture(Engine::Get()->Resources()->GetTexture("Orb"));
		SetScale(1.2f, 1.2f);
	}
	
	void Orb::Update(float dt)
	{
		Button::Update(dt);

		CheckWhereToFace();

		if (_facingRight)
		{
			MoveRight(dt);
		}
		else 
		{
			MoveLeft(dt);
		}

		auto position = GetPosition();
		SetPosition(position.x, position.y + _speed);

		_lifeTime += dt;
	}
	
	void Orb::CheckWhereToFace()
	{
		auto position = GetPosition();

		if (position.x < _minRange)
		{
			_facingRight = true;
		}
		else if (position.x > _maxRange)
		{
			_facingRight = false;
		}
	}
	
	void Orb::MoveRight(float dt)
	{
		D3DXVECTOR2 position = GetPosition();
		D3DXVECTOR2 up = _facingRight ? D3DXVECTOR2(0, -1) : D3DXVECTOR2(0, 1);

		position += up * _speed * dt;
		SetPosition(position + D3DXVECTOR2(1, 0) * std::sin(_lifeTime * _frequency) * _magnitude);
	}
	
	void Orb::MoveLeft(float dt)
	{
		D3DXVECTOR2 position = GetPosition();
		D3DXVECTOR2 up = _facingRight ? D3DXVECTOR2(0, -1) : D3DXVECTOR2(0, 1);

		position -= up * _speed * dt;
		SetPosition(position + D3DXVECTOR2(1, 0) * std::sin(_lifeTime * _frequency) * _magnitude);
	}

	void Orb::SetRandomPosition(float y)
	{
		auto xPos = static_cast<float>(std::rand()) / (
			static_cast<float>(RAND_MAX / (_maxRange - _minRange))
			) + _minRange;

		SetPosition(xPos, y);
	}

	void Orb::SetValues(float magnitude, float frequency, float speed)
	{
		_magnitude = magnitude;
		_frequency = frequency;
		_speed = speed;
	}
}