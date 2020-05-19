#pragma once

#include <Button.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class ActionButton : public Actor
	{
	public:
		virtual void Init() override;
		virtual void Update() override;

	private:
		Button* _button;

		Texture* _onTexture;
		Texture* _offTexture;
	};
}
