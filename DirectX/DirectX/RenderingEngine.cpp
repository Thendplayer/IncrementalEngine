#include <Windows.h>
#include <cassert>

#include "RenderingEngine.h"
#include "Config.h"
#include "Utils.h"

namespace MyEngine
{
	RenderingEngine::RenderingEngine() :
		m_swapChain(0),
		m_device(0),
		m_deviceContext(0),
		m_renderTargetView(0),
		m_depthStencilBuffer(0),
		m_depthStencilState(0),
		m_depthStencilView(0),
		m_rasterState(0),
		m_depthDisabledStencilState(0)
	{
	}

	RenderingEngine::~RenderingEngine()
	{
		if (m_swapChain)
		{
			m_swapChain->SetFullscreenState(FALSE, NULL);
		}
		
		if (m_deviceContext)
		{
			m_deviceContext->ClearState();
		}
		
		CHECKED_RELEASE(m_depthDisabledStencilState);
		CHECKED_RELEASE(m_rasterState);
		CHECKED_RELEASE(m_depthStencilView);
		CHECKED_RELEASE(m_depthStencilState);
		CHECKED_RELEASE(m_depthStencilBuffer);
		CHECKED_RELEASE(m_renderTargetView);
		CHECKED_RELEASE(m_deviceContext);
		CHECKED_RELEASE(m_device);
		CHECKED_RELEASE(m_swapChain);
	}

	HRESULT RenderingEngine::Init(RenderWindow* _renderWindow)
	{
		HRESULT result;
		renderWindow = _renderWindow;
		
		result = InitD3D();
		if (FAILED(result))
		{
			MessageBox(renderWindow->GetHWND(), L"Could not initialize Direct3D.", L"Error", MB_OK);
			return FALSE;
		}
		
		TurnZBufferOff();
		UpdateWindow(renderWindow->GetHWND());

		return S_OK;
	}

	void RenderingEngine::Update(float dt)
	{
		float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
		m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		
	}

	void RenderingEngine::Draw()
	{
		
	}

	HRESULT RenderingEngine::InitD3D()
	{
		HRESULT result;
		unsigned int numerator;
		unsigned int denominator;

		result = SetupAdapterOutput(numerator, denominator);
		if (FAILED(result))
		{
			return FALSE;
		}

		result = CreateDeviceAndSwapChain(numerator, denominator);
		if (FAILED(result))
		{
			return FALSE;
		}

		result = SetupRenderTarget();
		if(FAILED(result))
		{
			return FALSE;
		}
		
		result = SetupDepthStencilBufferAndState();
		if (FAILED(result))
		{
			return FALSE;
		}

		result = SetupDeviceRasterizerState();
		if (FAILED(result))
		{
			return FALSE;
		}

		SetupViewport();

		SetupD3DMatrices();

		const bool enable2dRendering = true;
		result = CreateDepthStencilState(enable2dRendering);
		
		if (FAILED(result))
		{
			return FALSE;
		}

		return S_OK;
	}

	HRESULT RenderingEngine::SetupAdapterOutput(unsigned int& numerator, unsigned int& denominator)
	{
		HRESULT result;
		IDXGIFactory* factory;
		IDXGIAdapter* adapter;
		IDXGIOutput* adapterOutput;
		unsigned int numModes, stringLength;
		DXGI_MODE_DESC* displayModeList;
		DXGI_ADAPTER_DESC adapterDesc;

		result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
		if (FAILED(result))
		{
			return FALSE;
		}

		result = factory->EnumAdapters(0, &adapter);
		if (FAILED(result))
		{
			return FALSE;
		}

		result = adapter->EnumOutputs(0, &adapterOutput);
		if (FAILED(result))
		{
			return FALSE;
		}

		result = adapterOutput->GetDisplayModeList(
			DXGI_FORMAT_R8G8B8A8_UNORM, 
			DXGI_ENUM_MODES_INTERLACED, 
			&numModes, 
			NULL
		);
		
		if (FAILED(result))
		{
			return FALSE;
		}

		displayModeList = new DXGI_MODE_DESC[numModes];
		if (!displayModeList)
		{
			return FALSE;
		}

		result = adapterOutput->GetDisplayModeList(
			DXGI_FORMAT_R8G8B8A8_UNORM, 
			DXGI_ENUM_MODES_INTERLACED, 
			&numModes, 
			displayModeList
		);
		
		if (FAILED(result))
		{
			return FALSE;
		}

		for (unsigned int i = 0; i < numModes; i++)
		{
			if (displayModeList[i].Width == (unsigned int)renderWindow->ScreenWidth)
			{
				if (displayModeList[i].Height == (unsigned int)renderWindow->ScreenHeight)
				{
					numerator = displayModeList[i].RefreshRate.Numerator;
					denominator = displayModeList[i].RefreshRate.Denominator;
				}
			}
		}

		result = adapter->GetDesc(&adapterDesc);
		if (FAILED(result))
		{
			return FALSE;
		}

		m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

		int error = wcstombs_s(
			&stringLength, 
			m_videoCardDescription, 
			128, 
			adapterDesc.Description, 
			128
		);
		
		if (error != 0)
		{
			return FALSE;
		}

		delete[] displayModeList;
		displayModeList = 0;

		adapterOutput->Release();
		adapterOutput = 0;

		adapter->Release();
		adapter = 0;

		factory->Release();
		factory = 0;

		return S_OK;
	}

	HRESULT RenderingEngine::CreateDeviceAndSwapChain(unsigned int numerator, unsigned int denominator)
	{
		HRESULT result;
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		D3D_FEATURE_LEVEL featureLevel;

		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		swapChainDesc.BufferCount = 1;

		swapChainDesc.BufferDesc.Width = renderWindow->ScreenWidth;
		swapChainDesc.BufferDesc.Height = renderWindow->ScreenHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		if (VSYNC_ENABLED)
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
		}
		else
		{
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		}

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		swapChainDesc.OutputWindow = renderWindow->GetHWND();

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		if (FULLSCREEN)
		{
			swapChainDesc.Windowed = false;
		}
		else
		{
			swapChainDesc.Windowed = true;
		}

		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.Flags = 0;

		featureLevel = D3D_FEATURE_LEVEL_11_0;

		result = D3D11CreateDeviceAndSwapChain(
			NULL, 
			D3D_DRIVER_TYPE_HARDWARE, 
			NULL, 
			0, 
			&featureLevel, 
			1, 
			D3D11_SDK_VERSION, 
			&swapChainDesc, 
			&m_swapChain,
			&m_device, 
			NULL, 
			&m_deviceContext
		);
		
		if (FAILED(result))
		{
			return FALSE;
		}
		
		return S_OK;
	}

	HRESULT RenderingEngine::SetupRenderTarget()
	{
		HRESULT result;
		ID3D11Texture2D* backBufferPtr;

		result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
		if (FAILED(result))
		{
			return FALSE;
		}

		result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
		if (FAILED(result))
		{
			return FALSE;
		}

		backBufferPtr->Release();
		backBufferPtr = 0;

		return S_OK;
	}

	HRESULT RenderingEngine::SetupDepthStencilBufferAndState()
	{
		HRESULT result;
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

		depthBufferDesc.Width = renderWindow->ScreenWidth;
		depthBufferDesc.Height = renderWindow->ScreenHeight;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;

		result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
		if (FAILED(result))
		{
			return FALSE;
		}

		const bool depth = true;
		CreateDepthStencilState(depth);

		m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
		if (FAILED(result))
		{
			return FALSE;
		}

		m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

		return S_OK;
	}

	HRESULT RenderingEngine::SetupDeviceRasterizerState()
	{
		HRESULT result;
		D3D11_RASTERIZER_DESC rasterDesc;
		
		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
		if (FAILED(result))
		{
			return FALSE;
		}

		m_deviceContext->RSSetState(m_rasterState);

		return S_OK;
	}

	void RenderingEngine::SetupViewport()
	{
		D3D11_VIEWPORT viewport;
		
		viewport.Width = (float)renderWindow->ScreenWidth;
		viewport.Height = (float)renderWindow->ScreenHeight;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		m_deviceContext->RSSetViewports(1, &viewport);
	}

	void RenderingEngine::SetupD3DMatrices()
	{
		float fieldOfView = (float)D3DX_PI / 4.0f;
		float screenAspect = (float)renderWindow->ScreenWidth / (float)renderWindow->ScreenHeight;

		D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, SCREEN_NEAR, SCREEN_DEPTH);

		D3DXMatrixIdentity(&m_worldMatrix);

		D3DXMatrixOrthoLH(&m_orthoMatrix, (float)renderWindow->ScreenWidth, (float)renderWindow->ScreenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	}

	HRESULT RenderingEngine::CreateDepthStencilState(bool enableZBuffer)
	{
		HRESULT result;
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

		depthStencilDesc.DepthEnable = enableZBuffer;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
		if (FAILED(result))
		{
			return FALSE;
		}

		return S_OK;
	}

	ID3D11Device* RenderingEngine::GetDevice()
	{
		return m_device;
	}

	ID3D11DeviceContext* RenderingEngine::GetDeviceContext()
	{
		return m_deviceContext;
	}

	void RenderingEngine::GetProjectionMatrix(D3DXMATRIX& projectionMatrix)
	{
		projectionMatrix = m_projectionMatrix;
	}

	void RenderingEngine::GetWorldMatrix(D3DXMATRIX& worldMatrix)
	{
		worldMatrix = m_worldMatrix;
		return;
	}

	void RenderingEngine::GetOrthoMatrix(D3DXMATRIX& orthoMatrix)
	{
		orthoMatrix = m_orthoMatrix;
	}

	void RenderingEngine::GetVideoCardInfo(char* cardName, int& memory)
	{
		strcpy_s(cardName, 128, m_videoCardDescription);
		memory = m_videoCardMemory;
	}

	void RenderingEngine::TurnZBufferOn()
	{
		m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
	}

	void RenderingEngine::TurnZBufferOff()
	{
		m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);
	}
}