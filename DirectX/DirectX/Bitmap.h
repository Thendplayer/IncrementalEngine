#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <d3d11.h>
#include <d3dx10math.h>

#include "Texture.h"
#include "RenderWindow.h"
#include "Drawable.h"

namespace MyEngine 
{
	class Bitmap : public Drawable
	{
	public:
		void Init(
			const wchar_t* textureFilename,
			int bitmapWidth,
			int bitmapHeight
		);

		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;

		void SetPosition(float x, float y);

		int GetIndexCount();
		ID3D11ShaderResourceView* GetTexture();

		Bitmap();
		~Bitmap();

	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
		};

		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;

		int _vertexCount, _indexCount;
		Texture* _texture;
		int _bitmapWidth, _bitmapHeight;
		D3DXVECTOR2 _previousPosition;
		D3DXVECTOR2 _position;

		HRESULT InitializeBuffers();
		
		HRESULT UpdateBuffers(
			ID3D11DeviceContext* deviceContext, 
			int positionX, 
			int positionY
		);

		void RenderBuffers(ID3D11DeviceContext* deviceContext);

		HRESULT LoadTexture(WCHAR* filename);
	};
}

#endif