#pragma once

#include <Sprite.h>
#include <Text.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class DisplayPanel : public Sprite
	{
	public:
		virtual void Init() override;
		virtual void Update() override;
	
	private:
		Text* _currencyText;
		Text* _currencyPerSecondText;
	};
}
