#ifndef _EngineGame_H
#define _EngineGame_H

namespace MyEngine
{
	class EngineGame
	{
	private:
		static EngineGame* GAME_INSTANCE;
		
	protected:
		EngineGame(EngineGame* game);
	
	public:
		static EngineGame* Get();
		
		virtual void Init() = 0;
		virtual void DeInit() = 0;
		virtual void Update(float dt) = 0;

		~EngineGame();
	};
}

#endif