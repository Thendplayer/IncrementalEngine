#ifndef _Engine_H
#define _Engine_H

#include <windows.h>

#include "EngineGame.h"
#include "InputManager.h"
#include "RenderingEngine.h"
#include "RenderWindow.h"
#include "SoundEngine.h"
#include "FontFactory.h"
#include "Scene.h"
#include "Resources.h"
#include "Utils.h"

namespace IncrementalEngine
{
	class Engine
	{
	public:
		static Engine* Get();

		Engine();
		virtual ~Engine();
		
		void Run(EngineGame* game);
		
		Scene* GetScene();
		Resources* GetResources();
		SoundEngine* GetSoundEngine();
		InputManager* GetInput();

	private:
		static Engine* ENGINE_INSTANCE;

		RenderingEngine* _renderingEngine;
		RenderWindow* _renderWindow;
		InputManager* _inputManager;
		SoundEngine* _soundEngine;
		Scene* _scene;
		Resources* _resources;

		void Init();
		void Update(float dt);
		void Draw();
		void DeInit();

		bool IsOpen();
	};
}

#endif