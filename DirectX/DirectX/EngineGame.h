#ifndef _EngineGame_H
#define _EngineGame_H

namespace MyEngine
{
	class EngineGame
	{
	public:
		EngineGame();
		~EngineGame();
		
		virtual void Init() = 0;
		virtual void DeInit() = 0;
		virtual void Update(float dt) = 0;
	};
}

#endif