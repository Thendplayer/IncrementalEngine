#ifndef _DRAWABLE_H
#define _DRAWABLE_H

#include <d3d11.h>
#include "RenderWindow.h"
#include "ShaderManager.h"

namespace IncrementalEngine 
{
	class Drawable 
	{
	public:
		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) = 0;

	protected:
		RenderWindow* _renderWindow;
		ShaderManager* _shaderManager;
		ID3D11Device* _device;

		void CopyParameters(Drawable* drawable) 
		{
			drawable->_renderWindow = _renderWindow;
			drawable->_shaderManager = _shaderManager;
			drawable->_device = _device;
		}
	};
}

#endif