#pragma once
namespace MyEngine
{
	class EngineComponent
	{
	protected:
		virtual void Update(float dt) = 0;
		virtual void Draw() = 0;
	};
}
