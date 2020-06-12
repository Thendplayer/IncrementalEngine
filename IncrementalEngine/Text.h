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
		enum FontAlignment
		{
			TOP_LEFT = FW1_TOP | FW1_LEFT,
			TOP_CENTER = FW1_TOP | FW1_CENTER,
			TOP_RIGHT = FW1_TOP | FW1_RIGHT,
			CENTER_LEFT = FW1_VCENTER | FW1_LEFT,
			CENTER = FW1_VCENTER | FW1_CENTER,
			CENTER_RIGHT = FW1_VCENTER | FW1_RIGHT,
			BOTTOM_LEFT = FW1_BOTTOM | FW1_LEFT,
			BOTTOM_CENTER = FW1_BOTTOM | FW1_CENTER,
			BOTTOM_RIGHT = FW1_BOTTOM | FW1_RIGHT
		};

		Text();
		~Text() override;

		virtual void Init() override;

		void SetFont(const std::wstring& fontFamily);

		void SetFontSize(float fontSize);
		void SetFontAlignment(FontAlignment alignment);

		void SetText(const std::wstring& value);
		void ClearText();

		void SetTextColor(const float r, const float g, const float b, const float a = 1);
		void SetTextColor(const D3DXVECTOR4 color);
		void SetTextColor(const std::uint32_t color);

		virtual FloatRect GetLocalBounds() override;

		virtual void Update(float dt) override;
		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;
		
	private:
		IFW1FontWrapper* _fontWrapper;
		XMMATRIX _fontWrapperMatrix;

		std::wstring _value;
		std::wstring _fontFamily;
		float _fontSize;
		std::uint32_t _color;
		UINT _flags;

		mutable bool _fontWrapperNeedUpdate;
		Transform _previousTransform;

		D3DXVECTOR2 GetTextExtent();
		XMMATRIX GetWorldMatrix(Actor* actor);
	};
}

#endif