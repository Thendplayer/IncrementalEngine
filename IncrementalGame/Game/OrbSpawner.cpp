#include "OrbSpawner.h"

#include <MainEngine.h>

#include <time.h>
#include <cstdlib>

namespace MagicIdle 
{
	void OrbSpawner::Init()
	{
		srand(time(NULL));
		_targetTime = (float)(std::rand()) / (static_cast<float>(RAND_MAX / 40)) + 10;
		_time = 0;

		_orb = Engine::Get()->Scene()->Create<Orb>();
		_orb->SetActive(false);
	}
	
	void OrbSpawner::Update(float dt)
	{
		if (_time >= _targetTime)
		{
			srand(time(NULL));
			std::rand();
			_targetTime = (float)(std::rand()) / (static_cast<float>(RAND_MAX / 40)) + 10;
			_time = 0;

			_orb->SetActive(true);
			_orb->SetRandomPosition(-_renderWindow->GetScreenHeight() * .5f);
			
			_orb->SetValues(
				static_cast<float>(std::rand()) / static_cast <float>(RAND_MAX / 15) + 5,
				static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 10)) + 10,
				static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 5)) + 3
			);
		}
		else if (_orb->IsActive())
		{
			auto height = _renderWindow->GetScreenHeight() * .5f;
			if (_orb->GetPosition().y > height)
			{
				_orb->SetActive(false);
			}
			else if (_orb->Pressed()) 
			{
				_totalEarnedPtr->Add(*_currencyPtr * .5f);
				_currencyPtr->Add(*_currencyPtr * .5f);
				_orb->SetActive(false);

				Engine::Get()->Audio()->Play(Engine::Get()->Resources()->GetSound("OrbSound"));
			}
		}

		_time += dt;
	}
	
	void OrbSpawner::SetCurrencyPtrs(KmbNumber* currencyPtr, KmbNumber* totalEarnedPtr)
	{
		_currencyPtr = currencyPtr;
		_totalEarnedPtr = totalEarnedPtr;
	}
}