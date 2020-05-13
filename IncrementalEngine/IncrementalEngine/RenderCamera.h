#ifndef _RENDERCAMERA_H
#define _RENDERCAMERA_H

#include <D3DX10math.h>

namespace IncrementalEngine 
{
	#define DEFAULT_UP D3DXVECTOR3(0.0f, 1.0f, 0.0f)
	#define DEFAULT_LOOK_AT D3DXVECTOR3(0.0f, 0.0f, 1.0f)

	class RenderCamera
	{
	public:
		void SetPosition(float x, float y, float z);
		void SetPosition(D3DXVECTOR3 position);
		void SetRotation(float x, float y, float z);
		void SetRotation(D3DXVECTOR3 rotation);

		D3DXVECTOR3 GetPosition();
		D3DXVECTOR3 GetRotation();

		void Draw();
		void GetViewMatrix(D3DXMATRIX& viewMatrix);

		RenderCamera();
		virtual ~RenderCamera();

	private:
		D3DXVECTOR3 _position;
		D3DXVECTOR3 _rotation;
		D3DXMATRIX _viewMatrix;
	};
}

#endif