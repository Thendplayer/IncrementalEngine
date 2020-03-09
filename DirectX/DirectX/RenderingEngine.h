#ifndef _RenderingEngine_H
#define _RenderingEngine_H

#include <D3D11.h>
#include <D3Dcommon.h>
#include <D3DX10.h>
#include <D3DX10math.h>
#include <D3DX11.h>
#include <DXGI.h>
#include <windows.h>
#include <windowsx.h>

#include "RenderWindow.h"

namespace MyEngine
{
	class RenderingEngine
	{
	private:
		RenderWindow* renderWindow;
		int m_videoCardMemory;
		char m_videoCardDescription[128];
		IDXGISwapChain* m_swapChain;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		ID3D11RenderTargetView* m_renderTargetView;
		ID3D11Texture2D* m_depthStencilBuffer;
		ID3D11DepthStencilState* m_depthStencilState;
		ID3D11DepthStencilView* m_depthStencilView;
		ID3D11RasterizerState* m_rasterState;
		D3DXMATRIX m_projectionMatrix;
		D3DXMATRIX m_worldMatrix;
		D3DXMATRIX m_orthoMatrix;
		ID3D11DepthStencilState* m_depthDisabledStencilState;

		HRESULT InitD3D();
		
		HRESULT SetupAdapterOutput(unsigned int& numerator, unsigned int& denominator);
		HRESULT CreateDeviceAndSwapChain(unsigned int numerator, unsigned int denominator);
		HRESULT SetupRenderTarget();
		HRESULT SetupDepthStencilBufferAndState();
		HRESULT CreateDepthStencilState(bool enableZBuffer);
		HRESULT SetupDeviceRasterizerState();
		void SetupViewport();
		void SetupD3DMatrices();

	public:
		HRESULT Init(RenderWindow* _renderWindow);
		void Update(float dt);
		void Draw();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		void GetProjectionMatrix(D3DXMATRIX& projectionMatrix);
		void GetWorldMatrix(D3DXMATRIX& worldMatrix);
		void GetOrthoMatrix(D3DXMATRIX& orthoMatrix);
		void GetVideoCardInfo(char* cardName, int& memory);
		void TurnZBufferOn();
		void TurnZBufferOff();

		RenderingEngine();
		~RenderingEngine();
	};
}

#endif