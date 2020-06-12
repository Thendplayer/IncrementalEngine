#pragma once

#include <Actor.h>
#include "Orb.h"
#include <KmbNumber.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class OrbSpawner : public Actor
	{
	public:
		virtual void Init() override;
		virtual void Update(float dt) override;

		void SetCurrencyPtrs(KmbNumber* currencyPtr, KmbNumber* totalEarnedPtr);

	private:
		Orb* _orb;
		KmbNumber* _currencyPtr;
		KmbNumber* _totalEarnedPtr;

		float _time;
		float _targetTime;
	};
}