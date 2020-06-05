#pragma once

#include <Button.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class ActionButtonView : public Button
	{
	public:
		virtual void Init() override;
		virtual void Update() override;

	private:
		Texture* _onTexture;
		Texture* _offTexture;
	};
}
