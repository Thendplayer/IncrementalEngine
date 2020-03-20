#ifndef _RENDERINGENGINE_H
#define _RENDERINGENGINE_H

#include "D3DImplementation.h"
#include "RenderCamera.h"
#include "TextureShaderRenderer.h"

namespace MyEngine
{
	#define DEFAULT_2D_CAMERA_POSITION D3DXVECTOR3(0.0f, 0.0f, -10.0f)

	class RenderingEngine
	{
	public:
		HRESULT Init(RenderWindow* renderWindow);
		void Update(float dt);
		void Draw();
	
		RenderingEngine();
		~RenderingEngine();

	private:
		D3DImplementation* _direct3D;
		RenderCamera* _camera;
		TextureShaderRenderer* _textureShaderRenderer;
	};
}

#endif