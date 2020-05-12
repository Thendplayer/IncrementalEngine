#ifndef _RENDERINGENGINE_H
#define _RENDERINGENGINE_H

#include "D3DImplementation.h"
#include "RenderCamera.h"
#include "ShaderManager.h"
#include "Bitmap.h"

namespace IncrementalEngine
{
	#define DEFAULT_2D_CAMERA_POSITION D3DXVECTOR3(0.0f, 0.0f, -10.0f)

	class RenderingEngine
	{
	public:
		HRESULT Init(RenderWindow* renderWindow);
		void Update(float dt);
		HRESULT Draw(Drawable* target);

		D3DImplementation* GetDirect3DImplementation();
		RenderCamera* GetCamera();
		ShaderManager* GetShaderManager();
	
		RenderingEngine();
		virtual ~RenderingEngine();

	private:
		D3DImplementation* _direct3D;
		RenderCamera* _camera;
		ShaderManager* _shaderManager;
	};
}

#endif