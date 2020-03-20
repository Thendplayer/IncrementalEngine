#include <Windows.h>
#include <cassert>

#include "D3DImplementation.h"
#include "Config.h"
#include "Utils.h"

namespace MyEngine
{
	D3DImplementation::D3DImplementation() :
		_swapChain(0),
		_device(0),
		_deviceContext(0),
		_renderTargetView(0),
		_depthStencilBuffer(0),
		_depthStencilState(0),
		_depthStencilView(0),
		_rasterState(0),
		_depthDisabledStencilState(0)
	{
	}

	D3DImplementation::~D3DImplementation()
	{
		if (_swapChain)
		{
			_swapChain->SetFullscreenState(FALSE, NULL);
		}
		
		if (_deviceContext)
		{
			_deviceContext->ClearState();
		}
		
		CHECKED_RELEASE(_depthDisabledStencilState);
		CHECKED_RELEASE(_rasterState);
		CHECKED_RELEASE(_depthStencilView);
		CHECKED_RELEASE(_depthStencilState);
		CHECKED_RELEASE(_depthStencilBuffer);
		CHECKED_RELEASE(_renderTargetView);
		CHECKED_RELEASE(_deviceContext);
		CHECKED_RELEASE(_device);
		CHECKED_RELEASE(_swapChain);
	}

	HRESULT D3DImplementation::Init(RenderWindow* renderWindow)
	{
		HRESULT result;
		unsigned int numerator;
		unsigned int denominator;
		
		_renderWindow = renderWindow;

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
		if (FAILED(result))
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

		TurnZBufferOff();

		return S_OK;
	}

	void D3DImplementation::Update(float dt)
	{
		float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		_deviceContext->ClearRenderTargetView(_renderTargetView, color);
		_deviceContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		
	}

	void D3DImplementation::Draw()
	{
		
	}

	HRESULT D3DImplementation::SetupAdapterOutput(unsigned int& numerator, unsigned int& denominator)
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
			if (displayModeList[i].Width == (unsigned int)_renderWindow->ScreenWidth)
			{
				if (displayModeList[i].Height == (unsigned int)_renderWindow->ScreenHeight)
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

		_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

		int error = wcstombs_s(
			&stringLength, 
			_videoCardDescription, 
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

	HRESULT D3DImplementation::CreateDeviceAndSwapChain(unsigned int numerator, unsigned int denominator)
	{
		HRESULT result;
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		D3D_FEATURE_LEVEL featureLevel;

		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		swapChainDesc.BufferCount = 1;

		swapChainDesc.BufferDesc.Width = _renderWindow->ScreenWidth;
		swapChainDesc.BufferDesc.Height = _renderWindow->ScreenHeight;
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

		swapChainDesc.OutputWindow = _renderWindow->GetHWND();

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
			&_swapChain,
			&_device, 
			NULL, 
			&_deviceContext
		);
		
		if (FAILED(result))
		{
			return FALSE;
		}
		
		return S_OK;
	}

	HRESULT D3DImplementation::SetupRenderTarget()
	{
		HRESULT result;
		ID3D11Texture2D* backBufferPtr;

		result = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
		if (FAILED(result))
		{
			return FALSE;
		}

		result = _device->CreateRenderTargetView(backBufferPtr, NULL, &_renderTargetView);
		if (FAILED(result))
		{
			return FALSE;
		}

		backBufferPtr->Release();
		backBufferPtr = 0;

		return S_OK;
	}

	HRESULT D3DImplementation::SetupDepthStencilBufferAndState()
	{
		HRESULT result;
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

		depthBufferDesc.Width = _renderWindow->ScreenWidth;
		depthBufferDesc.Height = _renderWindow->ScreenHeight;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;

		result = _device->CreateTexture2D(&depthBufferDesc, NULL, &_depthStencilBuffer);
		if (FAILED(result))
		{
			return FALSE;
		}

		const bool depth = true;
		CreateDepthStencilState(depth);

		_deviceContext->OMSetDepthStencilState(_depthStencilState, 1);

		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		result = _device->CreateDepthStencilView(_depthStencilBuffer, &depthStencilViewDesc, &_depthStencilView);
		if (FAILED(result))
		{
			return FALSE;
		}

		_deviceContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

		return S_OK;
	}

	HRESULT D3DImplementation::SetupDeviceRasterizerState()
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

		result = _device->CreateRasterizerState(&rasterDesc, &_rasterState);
		if (FAILED(result))
		{
			return FALSE;
		}

		_deviceContext->RSSetState(_rasterState);

		return S_OK;
	}

	void D3DImplementation::SetupViewport()
	{
		D3D11_VIEWPORT viewport;
		
		viewport.Width = (float)_renderWindow->ScreenWidth;
		viewport.Height = (float)_renderWindow->ScreenHeight;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		_deviceContext->RSSetViewports(1, &viewport);
	}

	void D3DImplementation::SetupD3DMatrices()
	{
		float fieldOfView = (float)D3DX_PI / 4.0f;
		float screenAspect = (float)_renderWindow->ScreenWidth / (float)_renderWindow->ScreenHeight;

		D3DXMatrixPerspectiveFovLH(&_projectionMatrix, fieldOfView, screenAspect, SCREEN_NEAR, SCREEN_DEPTH);

		D3DXMatrixIdentity(&_worldMatrix);

		D3DXMatrixOrthoLH(&_orthoMatrix, (float)_renderWindow->ScreenWidth, (float)_renderWindow->ScreenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	}

	HRESULT D3DImplementation::CreateDepthStencilState(bool enableZBuffer)
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

		result = _device->CreateDepthStencilState(&depthStencilDesc, &_depthStencilState);
		if (FAILED(result))
		{
			return FALSE;
		}

		return S_OK;
	}

	ID3D11Device* D3DImplementation::GetDevice()
	{
		return _device;
	}

	ID3D11DeviceContext* D3DImplementation::GetDeviceContext()
	{
		return _deviceContext;
	}

	void D3DImplementation::GetProjectionMatrix(D3DXMATRIX& projectionMatrix)
	{
		projectionMatrix = _projectionMatrix;
	}

	void D3DImplementation::GetWorldMatrix(D3DXMATRIX& worldMatrix)
	{
		worldMatrix = _worldMatrix;
		return;
	}

	void D3DImplementation::GetOrthoMatrix(D3DXMATRIX& orthoMatrix)
	{
		orthoMatrix = _orthoMatrix;
	}

	void D3DImplementation::GetVideoCardInfo(char* cardName, int& memory)
	{
		strcpy_s(cardName, 128, _videoCardDescription);
		memory = _videoCardMemory;
	}

	void D3DImplementation::TurnZBufferOn()
	{
		_deviceContext->OMSetDepthStencilState(_depthStencilState, 1);
	}

	void D3DImplementation::TurnZBufferOff()
	{
		_deviceContext->OMSetDepthStencilState(_depthDisabledStencilState, 1);
	}
}