#include "RenderCamera.h"
#include "Math.h"

namespace IncrementalEngine 
{
	RenderCamera::RenderCamera() :
		_position(0.0f, 0.0f, 0.0f),
		_rotation(0.0f, 0.0f, 0.0f)
	{
	}

	RenderCamera::~RenderCamera()
	{
	}

	void RenderCamera::Draw()
	{
		D3DXVECTOR3 up, position, lookAt;
		float yaw, pitch, roll;
		D3DXMATRIX rotationMatrix;

		position = _position;
		up = DEFAULT_UP;
		lookAt = DEFAULT_LOOK_AT;

		pitch = RAD2DEG(_rotation.x);
		yaw = RAD2DEG(_rotation.y);
		roll = RAD2DEG(_rotation.z);

		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

		D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
		D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

		lookAt = position + lookAt;

		D3DXMatrixLookAtLH(&_viewMatrix, &position, &lookAt, &up);
	}

	void RenderCamera::SetPosition(float x, float y, float z)
	{
		_position = D3DXVECTOR3(x, y, z);
	}

	void RenderCamera::SetPosition(D3DXVECTOR3 position)
	{
		_position = position;
	}

	void RenderCamera::SetRotation(float x, float y, float z)
	{
		_rotation = D3DXVECTOR3(x, y, z);
	}

	void RenderCamera::SetRotation(D3DXVECTOR3 rotation)
	{
		_rotation = rotation;
	}

	D3DXVECTOR3 RenderCamera::GetPosition()
	{
		return _position;
	}

	D3DXVECTOR3 RenderCamera::GetRotation()
	{
		return _rotation;
	}

	void RenderCamera::GetViewMatrix(D3DXMATRIX& viewMatrix)
	{
		viewMatrix = _viewMatrix;
	}
}