#pragma once

#include <Button.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class Orb : public Button
	{
	public:
		virtual void Init() override;
		virtual void Update(float dt) override;

		void SetRandomPosition(float y);
		void SetValues(float magnitude, float frequency, float speed);

	private:
		float _lifeTime = 0;

		float _maxRange = 570;
		float _minRange = 100;

		float _magnitude = .5f;
		float _frequency = 20;
		float _speed = 5;

		bool _facingRight = false;

		void CheckWhereToFace();
		void MoveRight(float dt);
		void MoveLeft(float dt);
	};
}