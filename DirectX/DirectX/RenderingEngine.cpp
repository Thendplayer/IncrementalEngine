#include <Windows.h>
#include <cassert>

#include "RenderingEngine.h"
#include "Config.h"
#include "Math.h"

namespace MyEngine
{
	RenderingEngine::RenderingEngine(HINSTANCE _hInstance) :
		device(NULL),
		deviceContext(NULL),
		swapChain(NULL),
		renderTargetView(NULL),
		depthStencil(NULL),
		depthStencilView(NULL)
	{
        hInstance = _hInstance;
		Init();
	}

	RenderingEngine::~RenderingEngine()
	{
		if (deviceContext)
			deviceContext->ClearState();
		CHECKED_RELEASE(renderTargetView);
		CHECKED_RELEASE(swapChain);
		CHECKED_RELEASE(deviceContext);
		CHECKED_RELEASE(device);
	}

	void RenderingEngine::Init()
	{
		InitWindow();
		
		HRESULT hr = InitD3D();
		assert(SUCCEEDED(hr));
	}

	void RenderingEngine::Update(float dt)
	{
		
	}

	void RenderingEngine::Draw()
	{
		
	}

    LRESULT WINAPI WindowProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

	void RenderingEngine::InitWindow()
	{
		WNDCLASSEX wc;

        ZeroMemory(&wc, sizeof(WNDCLASSEX));

        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_CLASSDC;
        wc.lpfnWndProc = WindowProc;
        wc.cbClsExtra = 0L;
        wc.cbWndExtra = 0L;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hIcon = NULL;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = NULL;
        wc.lpszMenuName = NULL;
        wc.lpszClassName = APPLICATION_NAME;

        RegisterClassEx(&wc);

        RECT wr = {
        	0,
        	0,
            SCREEN_WIDTH,
            SCREEN_HEIGHT
        };
		
        AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

        hWnd = CreateWindowEx(
	        NULL,
			APPLICATION_NAME,
			APPLICATION_NAME,
	        WS_OVERLAPPEDWINDOW,
			WINDOW_POSITION_X,
			WINDOW_POSITION_Y,
	        wr.right - wr.left,
	        wr.bottom - wr.top,
	        NULL,
	        NULL,
	        hInstance,
	        NULL
        );

        ShowWindow(hWnd, SW_SHOWDEFAULT);
	}

	HRESULT RenderingEngine::InitD3D()
	{
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);
		
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
		swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		if (
			FAILED(
				D3D11CreateDeviceAndSwapChain(
					NULL, 
					D3D_DRIVER_TYPE_HARDWARE, 
					NULL, 
					0, 
					featureLevels, 
					numFeatureLevels,
					D3D11_SDK_VERSION, 
					&swapChainDesc,
					&swapChain, 
					&device, 
					NULL, 
					&deviceContext
				)
			)
		)
		{
			return FALSE;
		}

		ID3D11Texture2D* pBackBuffer;
		if (
			FAILED(
				swapChain->GetBuffer(
					0, 
					__uuidof(ID3D11Texture2D), 
					(LPVOID*)&pBackBuffer)
				)
			)
		{
			return FALSE;
		}

		HRESULT hr = device->CreateRenderTargetView(
			pBackBuffer, 
			NULL, 
			&renderTargetView
		);
		
		pBackBuffer->Release();

		if (FAILED(hr))
		{
			return FALSE;
		}

		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory(&descDepth, sizeof(descDepth));
		
		descDepth.Width = SCREEN_WIDTH;
		descDepth.Height = SCREEN_HEIGHT;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		
		hr = device->CreateTexture2D(
			&descDepth, 
			NULL, 
			&depthStencil
		);
		
		if (FAILED(hr))
		{
			return hr;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		depthStencilViewDesc.Format = descDepth.Format;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		
		hr = device->CreateDepthStencilView(
			depthStencil, 
			&depthStencilViewDesc, 
			&depthStencilView
		);
		
		if (FAILED(hr))
		{
			return hr;
		}

		deviceContext->OMSetRenderTargets(
			1, 
			&renderTargetView, 
			depthStencilView
		);

		D3D11_VIEWPORT viewport;
		
		viewport.Width = (FLOAT)SCREEN_WIDTH;
		viewport.Height = (FLOAT)SCREEN_HEIGHT;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;

		deviceContext->RSSetViewports(
			1, 
			&viewport
		);

		return S_OK;
	}

	LRESULT WINAPI WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
		switch (message)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_KEYDOWN:
			{
				switch (wParam)
				{
					case VK_ESCAPE:
						PostQuitMessage(0);
						return 0;
						break;
				}
			}
		}
		
		return DefWindowProc(hWnd, message, wParam, lParam);
    }
}