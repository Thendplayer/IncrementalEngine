#ifndef _FONT_H
#define _FONT_H

#include "FontFactory.h"
#include "Actor.h"

#include <string>

namespace MyEngine 
{
	class Text : public Actor
	{
	public:
		Text();
		~Text() override;

		void SetFont(const std::wstring& font);
		void ClearFont();

		void SetFontSize(float fontSize);

		void SetText(const std::wstring& value);
		void ClearText();

		void SetTextColor(unsigned long color);

		virtual FloatRect GetLocalBounds() override;

		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;
		
	private:
		IFW1FontWrapper* _fontWrapper;

		std::wstring _value;
		float _fontSize;
		unsigned long _color;
	};
}

#endif