#ifndef _D3D_IMPLEMENTATION_H
#define _D3D_IMPLEMENTATION_H

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <DXGI.h>
#include <D3Dcommon.h>
#include <D3D11.h>
#include <D3DX10math.h>
#include <windows.h>
#include <windowsx.h>

#include "RenderWindow.h"

namespace MyEngine
{
	class D3DImplementation
	{
	public:
		HRESULT Init(RenderWindow* renderWindow);
		void Update(float dt);
		void Draw();

		void BeginScene(float red, float green, float blue, float alpha);
		void EndScene();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		void GetProjectionMatrix(D3DXMATRIX& projectionMatrix);
		void GetWorldMatrix(D3DXMATRIX& worldMatrix);
		void SetWorldMatrix(D3DXMATRIX& worldMatrix);
		void GetOrthoProjectionMatrix(D3DXMATRIX& orthoMatrix);
		void GetVideoCardInfo(char* cardName, int& memory);
		void TurnZBufferOn();
		void TurnZBufferOff();

		D3DImplementation();
		virtual ~D3DImplementation();

	private:
		RenderWindow* _renderWindow;
		int _videoCardMemory;
		char _videoCardDescription[128];
		IDXGISwapChain* _swapChain;
		ID3D11Device* _device;
		ID3D11DeviceContext* _deviceContext;
		ID3D11RenderTargetView* _renderTargetView;
		ID3D11Texture2D* _depthStencilBuffer;
		ID3D11DepthStencilState* _depthStencilState;
		ID3D11DepthStencilView* _depthStencilView;
		ID3D11RasterizerState* _rasterState;
		D3DXMATRIX _projectionMatrix;
		D3DXMATRIX _worldMatrix;
		D3DXMATRIX _orthoProjectionMatrix;
		ID3D11DepthStencilState* _depthDisabledStencilState;

		HRESULT SetupAdapterOutput(unsigned int& numerator, unsigned int& denominator);
		HRESULT CreateDeviceAndSwapChain(unsigned int numerator, unsigned int denominator);
		HRESULT SetupRenderTarget();
		HRESULT SetupDepthStencilBufferAndState();
		HRESULT CreateDepthStencilState(bool enableZBuffer);
		HRESULT SetupDeviceRasterizerState();
		void SetupViewport();
		void SetupD3DMatrices();
	};
}

#endif