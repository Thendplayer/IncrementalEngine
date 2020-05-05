#include "Text.h"
#include "Utils.h"

namespace MyEngine 
{
	Text::Text() :
		_fontWrapper(NULL),
		_value(L""),
		_fontSize(12),
		_color(0)
	{
	}

	Text::~Text()
	{
		CHECKED_RELEASE(_fontWrapper);
	}

	void Text::SetFont(const std::wstring& font)
	{
		HRESULT result = FontFactory::Get()->CreateFontWrapper(_device, font.c_str(), &_fontWrapper);
		if (FAILED(result))
		{
			MessageBox(NULL, TEXT("CreateFontWrapper"), TEXT("Error"), MB_OK);
		}
	}

	void Text::ClearFont()
	{
		CHECKED_RELEASE(_fontWrapper);
	}

	void Text::SetFontSize(float fontSize)
	{
		_fontSize = fontSize;
	}

	void Text::SetText(const std::wstring& value)
	{
		_value = value;
	}

	void Text::ClearText()
	{
		_value = L"";
	}

	void Text::SetTextColor(unsigned long color)
	{
		_color = color;
	}

	FloatRect Text::GetLocalBounds()
	{
		return FloatRect();
	}
	
	HRESULT Text::Draw(ID3D11DeviceContext* deviceContext)
	{
		auto position = GetTransform() * D3DXVECTOR2(.0f, .0f);

		_fontWrapper->DrawString(
			deviceContext, 
			_value.c_str(), 
			_fontSize,
			position.x, 
			position.y, 
			_color,
			FW1_RESTORESTATE
		);

		return S_OK;
	}
}