#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#include "Utils.h"
#include "Config.h"
#include "Text.h"

namespace IncrementalEngine 
{
	Text::Text() :
		_fontWrapper(NULL),
		_fontFamily(DEFAULT_FONT_FAMILY),
		_value(L""),
		_fontSize(12),
		_color(0)
	{
	}

	Text::~Text()
	{
		CHECKED_RELEASE(_fontWrapper);
	}

	void Text::Init()
	{
		HRESULT result = FontFactory::Get()->CreateFontWrapper(
			_device,
			_fontFamily.c_str(),
			&_fontWrapper
		);

		if (FAILED(result))
		{
			MessageBox(NULL, TEXT("CreateFontWrapper"), TEXT("Error"), MB_OK);
		}

		_fontWrapperNeedUpdate = true;
	}

	void Text::SetFont(const std::wstring& fontFamily)
	{
		_fontFamily = fontFamily;
		Center();
		_fontWrapperNeedUpdate = true;
	}

	void Text::SetFontSize(float fontSize)
	{
		_fontSize = fontSize;
		Center();
		_fontWrapperNeedUpdate = true;
	}

	void Text::SetText(const std::wstring& value)
	{
		_value = value;
		Center();
		_fontWrapperNeedUpdate = true;
	}

	void Text::ClearText()
	{
		_value = L"";
		Center();
		_fontWrapperNeedUpdate = true;
	}

	void Text::SetTextColor(const float r, const float g, const float b, const float a)
	{
		_color = DirectX::PackedVector::XMCOLOR::XMCOLOR(b / 255, g / 255, r / 255, a);
	}

	void Text::SetTextColor(const D3DXVECTOR4 color)
	{
		SetTextColor(color.x, color.y, color.z, color.w);
	}

	void Text::SetTextColor(const std::uint32_t color)
	{
		_color = color;
	}

	FloatRect Text::GetLocalBounds()
	{
		D3DXVECTOR2 extent = GetTextExtent();
		FloatRect bounds = {
			0.f,
			0.f,
			extent.x,
			extent.y
		};

		return bounds;
	}
	
	void Text::Update()
	{
		Transform transform = GetCombinedTransform();
		if (_fontWrapperNeedUpdate || transform != _previousTransform)
		{
			_previousTransform = transform;

			XMMATRIX OrthoProjectionMatrix = XMMatrixOrthographicLH(
				_renderWindow->GetScreenWidth(),
				-_renderWindow->GetScreenHeight(),
				SCREEN_NEAR,
				SCREEN_DEPTH
			);

			D3DXVECTOR2 position = GetWorldPosition();
			XMMATRIX translationMatrix = XMMatrixTranslation(
				position.x,
				position.y,
				1.f
			);

			D3DXVECTOR2 scale = GetWorldScale();
			XMMATRIX scaleMatrix = XMMatrixScaling(
				scale.x,
				scale.y,
				1.f
			);

			float rotation = GetWorldRotation();
			_fontWrapperMatrix = scaleMatrix
				* XMMatrixRotationZ(rotation * 0.01745f)
				* translationMatrix
				* OrthoProjectionMatrix;

			_fontWrapperNeedUpdate = false;
		}
	}

	HRESULT Text::Draw(ID3D11DeviceContext* deviceContext)
	{
		FW1_RECTF rect = { 0.f, 0.f, 0.f, 0.f };
		
		_fontWrapper->DrawString(
			deviceContext,
			_value.c_str(),
			_fontFamily.c_str(),
			_fontSize,
			&rect,
			_color,
			NULL,
			reinterpret_cast<FLOAT*>(&_fontWrapperMatrix),
			FW1_CENTER | FW1_VCENTER | FW1_NOWORDWRAP | FW1_RESTORESTATE
		);

		return S_OK;
	}
	
	D3DXVECTOR2 Text::GetTextExtent()
	{
		FW1_RECTF nullRect = { 0.f, 0.f, 0.f, 0.f };
		FW1_RECTF rect = _fontWrapper->MeasureString(
			_value.c_str(), 
			_fontFamily.c_str(),
			_fontSize, 
			&nullRect, 
			FW1_NOWORDWRAP
		);

		return { rect.Right - rect.Left, rect.Bottom - rect.Top };
	}
}