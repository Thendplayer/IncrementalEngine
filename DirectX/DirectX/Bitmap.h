#ifndef _BITMAP_H_
#define _BITMAP_H_

#include "TextureBase.h"
#include "RenderWindow.h"

namespace MyEngine 
{
	class Bitmap : public TextureBase
	{
	public:
		Bitmap();
		~Bitmap();

		HRESULT Create(Texture* texture);
		virtual HRESULT Draw(ID3D11DeviceContext* deviceContext) override;

		int GetIndexCount();

	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
		};

		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;

		int _vertexCount, _indexCount;
		D3DXVECTOR2 _previousPosition;
		D3DXVECTOR2 _previousScale;

		HRESULT InitializeBuffers();
		HRESULT UpdateBuffers(ID3D11DeviceContext* deviceContext);
		void RenderBuffers(ID3D11DeviceContext* deviceContext);
	};
}

#endif