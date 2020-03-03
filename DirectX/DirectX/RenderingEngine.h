#ifndef _RenderingEngine_H
#define _RenderingEngine_H

#include <windows.h>
#include <windowsx.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

namespace MyEngine
{
	class RenderingEngine
	{
	private:
		HINSTANCE hInstance;
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
		IDXGISwapChain* swapChain;
		ID3D11RenderTargetView* renderTargetView;
		ID3D11Texture2D* depthStencil;
		ID3D11DepthStencilView* depthStencilView;
		HWND hWnd;
		WNDCLASSEX wc;

		void InitWindow();
		HRESULT InitD3D();

	public:
		HWND Init();
		void Update(float dt);
		void Draw();

		RenderingEngine(HINSTANCE _hInstance);
		~RenderingEngine();
	};
}

#endif