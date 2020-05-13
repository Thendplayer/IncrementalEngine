#include <Windows.h>
#include <cassert>

#include "D3DImplementation.h"
#include "Config.h"
#include "Utils.h"

namespace IncrementalEngine
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
		unsigned int numerator, denominator;
		
		_renderWindow = renderWindow;

		result = SetupAdapterOutput(numerator, denominator);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		result = CreateDeviceAndSwapChain(numerator, denominator);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		result = SetupRenderTarget();
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		result = SetupDepthStencilBufferAndState();
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		result = SetupDeviceRasterizerState();
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		SetupViewport();
		SetupD3DMatrices();

		const bool depth = false;
		result = CreateDepthStencilState(_depthDisabledStencilState, depth);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		TurnZBufferOff();

		return S_OK;
	}

	void D3DImplementation::BeginScene(float red, float green, float blue, float alpha)
	{
		float color[4] = { red, green, blue, alpha };
		TurnZBufferOff();
		_deviceContext->ClearRenderTargetView(_renderTargetView, color);
		_deviceContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void D3DImplementation::EndScene()
	{
		if (VSYNC_ENABLED)
		{
			_swapChain->Present(1, 0);
		}
		else
		{
			_swapChain->Present(0, 0);
		}

		TurnZBufferOn();
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
			return CO_E_ERRORINAPP;
		}

		result = factory->EnumAdapters(0, &adapter);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		result = adapter->EnumOutputs(0, &adapterOutput);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		result = adapterOutput->GetDisplayModeList(
			DXGI_FORMAT_R8G8B8A8_UNORM, 
			DXGI_ENUM_MODES_INTERLACED, 
			&numModes, 
			NULL
		);
		
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		displayModeList = new DXGI_MODE_DESC[numModes];
		if (!displayModeList)
		{
			return CO_E_ERRORINAPP;
		}

		result = adapterOutput->GetDisplayModeList(
			DXGI_FORMAT_R8G8B8A8_UNORM, 
			DXGI_ENUM_MODES_INTERLACED, 
			&numModes, 
			displayModeList
		);
		
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		for (unsigned int i = 0; i < numModes; i++)
		{
			if (displayModeList[i].Width == (unsigned int)_renderWindow->GetScreenWidth())
			{
				if (displayModeList[i].Height == (unsigned int)_renderWindow->GetScreenHeight())
				{
					numerator = displayModeList[i].RefreshRate.Numerator;
					denominator = displayModeList[i].RefreshRate.Denominator;
				}
			}
		}

		result = adapter->GetDesc(&adapterDesc);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
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
			return CO_E_ERRORINAPP;
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

		swapChainDesc.BufferDesc.Width = _renderWindow->GetScreenWidth();
		swapChainDesc.BufferDesc.Height = _renderWindow->GetScreenHeight();
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

		swapChainDesc.Windowed = !FULLSCREEN;

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
			return CO_E_ERRORINAPP;
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
			return CO_E_ERRORINAPP;
		}

		result = _device->CreateRenderTargetView(backBufferPtr, NULL, &_renderTargetView);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
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

		depthBufferDesc.Width = _renderWindow->GetScreenWidth();
		depthBufferDesc.Height = _renderWindow->GetScreenHeight();
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
			return CO_E_ERRORINAPP;
		}

		const bool depth = true;
		CreateDepthStencilState(_depthStencilState, depth);

		_deviceContext->OMSetDepthStencilState(_depthStencilState, 1);

		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		result = _device->CreateDepthStencilView(_depthStencilBuffer, &depthStencilViewDesc, &_depthStencilView);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
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
			return CO_E_ERRORINAPP;
		}

		_deviceContext->RSSetState(_rasterState);

		return S_OK;
	}

	void D3DImplementation::SetupViewport()
	{
		D3D11_VIEWPORT viewport;
		
		viewport.Width = (float)_renderWindow->GetScreenWidth();
		viewport.Height = (float)_renderWindow->GetScreenHeight();
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		_deviceContext->RSSetViewports(1, &viewport);
	}

	void D3DImplementation::SetupD3DMatrices()
	{
		float fieldOfView = (float)D3DX_PI / 4.0f;
		float screenAspect = (float)_renderWindow->GetScreenWidth() / (float)_renderWindow->GetScreenHeight();

		D3DXMatrixPerspectiveFovLH(&_projectionMatrix, fieldOfView, screenAspect, SCREEN_NEAR, SCREEN_DEPTH);

		D3DXMatrixIdentity(&_worldMatrix);

		D3DXMatrixOrthoLH(&_orthoProjectionMatrix, (float)_renderWindow->GetScreenWidth(), (float)_renderWindow->GetScreenHeight(), SCREEN_NEAR, SCREEN_DEPTH);
	
		D3DXMATRIX scaling, rotation, translation, worldMatrix;
		
		D3DXMatrixScaling(&scaling, 1, -1, 1);
		D3DXMatrixRotationZ(&rotation, 0);
		D3DXMatrixTranslation(&translation, 0, 0, 0);

		D3DXMatrixMultiply(&worldMatrix, &scaling, &rotation);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translation);

		SetWorldMatrix(worldMatrix);
	}

	HRESULT D3DImplementation::CreateDepthStencilState(ID3D11DepthStencilState*& depthStencilState, bool enableZBuffer)
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

		result = _device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
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
	}

	void D3DImplementation::SetWorldMatrix(D3DXMATRIX& worldMatrix)
	{
		_worldMatrix = worldMatrix;
	}

	void D3DImplementation::GetOrthoProjectionMatrix(D3DXMATRIX& orthoProjectionMatrix)
	{
		orthoProjectionMatrix = _orthoProjectionMatrix;
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