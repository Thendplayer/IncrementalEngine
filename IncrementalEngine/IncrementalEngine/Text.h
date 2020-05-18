#ifndef _TEXT_H
#define _TEXT_H

#include "FontFactory.h"
#include "Actor.h"

#include <string>
#include <xnamath.h>

namespace IncrementalEngine 
{
	class Text : public Actor
	{
	#define DEFAULT_FONT_FAMILY L"Courier New"

	public:
		Text();
		~Text() override;

		virtual void Init() override;

		void SetFont(const std::wstring& fontFamily);

		void SetFontSize(float fontSize);

		void SetText(const std::wstring& value);
		void ClearText();

		void SetTextColor(const float r, const float g, const float b, const float a = 1);
		void SetTextColor(const D3DXVECTOR4 color);
		void SetTextColor(const std::uint32_t color);

		virtual FloatRect GetLocalBounds() override;

		virtual void Update() override;
		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;
		
	private:
		IFW1FontWrapper* _fontWrapper;
		XMMATRIX _fontWrapperMatrix;

		std::wstring _value;
		std::wstring _fontFamily;
		float _fontSize;
		std::uint32_t _color;

		mutable bool _fontWrapperNeedUpdate;
		Transform _previousTransform;

		D3DXVECTOR2 GetTextExtent();
	};
}

#endif