#ifndef _Engine_H
#define _Engine_H

#include <windows.h>
#include "EngineGame.h"

namespace MyEngine
{
	class Engine
	{
	private:
		static Engine* ENGINE_INSTANCE;

		void Init();
		void Update();
		void Draw();

		Engine();

	public:
		static Engine* Get();
		void Run(HINSTANCE hInstance, EngineGame* game);

		~Engine();
	};
}

#endif