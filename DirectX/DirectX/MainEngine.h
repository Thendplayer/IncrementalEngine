#ifndef _Engine_H
#define _Engine_H

#include <windows.h>
#include "EngineGame.h"
#include "RenderingEngine.h"

namespace MyEngine
{
	class Engine
	{
	private:
		static Engine* ENGINE_INSTANCE;
		HINSTANCE hInstance;
		RenderingEngine* renderingEngine;

		void Init();
		void Update(float dt);
		void Draw();

		Engine();

	public:
		static Engine* Get();
		void DeInit();
		bool IsOpen();
		void Run(HINSTANCE hInstance, EngineGame* game);

		~Engine();
	};
}

#endif