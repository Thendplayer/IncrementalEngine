#ifndef _Engine_H
#define _Engine_H

#include <windows.h>

#include "EngineGame.h"
#include "RenderingEngine.h"
#include "RenderWindow.h"
#include "InputManager.h"
#include "SoundEngine.h"
#include "FontFactory.h"
#include "SaveSystem.h"
#include "Scene.h"
#include "Resources.h"
#include "Utils.h"
#include "Config.h"

namespace IncrementalEngine
{
	class Engine
	{
	public:
		static Engine* Get();

		Engine();
		virtual ~Engine();
		
		void Run(EngineGame* game);
		void Close();

		void SetIcon(LPCWSTR icon);

		SceneManager* Scene();
		ResourcesManager* Resources();
		InputManager* Input();
		SoundEngine* Audio();
		SaveSystem* Storage();

	private:
		static Engine* ENGINE_INSTANCE;

		RenderingEngine* _renderingEngine;
		RenderWindow* _renderWindow;
		InputManager* _inputManager;
		SoundEngine* _soundEngine;
		SceneManager* _sceneManager;
		ResourcesManager* _resourcesManager;
		SaveSystem* _saveSystem;
		
		Config _config;
		bool _open;

		void Init();
		void Update(float dt);
		void Draw();
		void DeInit();
	};
}

#endif