#include "Actor.h"

namespace MyEngine 
{
	Actor::Actor()
	{
	}
	
	Actor::~Actor()
	{
	}

	void Actor::Center()
	{
		auto width = (*GetLocalBounds()).right - (*GetLocalBounds()).left;
		auto height = (*GetLocalBounds()).bottom - (*GetLocalBounds()).top;

		auto origin = D3DXVECTOR2(width, height) / 2.0f;
		SetOrigin(origin);
	}

	RECT* Actor::GetLocalBounds()
	{
		return nullptr; //TODO: Continue from here
	}

	HRESULT Actor::Draw(ID3D11DeviceContext* deviceContext)
	{
		return S_OK;
	}

	Transform* Actor::GetWorldTransform() const
	{
		if (_parent != nullptr)
		{
			return &(GetTransform() * *_parent->GetWorldTransform());
		}
	}

	D3DXVECTOR2* Actor::GetWorldPosition() const
	{
		return &(*GetWorldTransform() * GetOrigin());
	}

	void Actor::SetWorldPosition(D3DXVECTOR2* value)
	{
		D3DXVECTOR2 newPosition;

		if (_parent != nullptr)
		{
			newPosition = _parent->GetWorldTransform()->GetInverse().TransformPoint(*value);
		}
		else 
		{
			newPosition = *value;
		}

		SetPosition(newPosition);
	}
	
	Actor* Actor::GetParent() const
	{
		return _parent;
	}
	
	void Actor::SetParent(Actor* value)
	{
		if (value != _parent)
		{
			auto prevWorldPosition = GetWorldPosition();

			if (_parent != nullptr)
			{
				(*_parent)._children.erase(
					remove(
						(*_parent)._children.begin(), 
						(*_parent)._children.end(),
						value
					), 
					(*_parent)._children.end() 
				);
			}

			if (value != nullptr)
			{
				(*value)._children.push_back(this);
			}

			_parent = value;
			SetWorldPosition(prevWorldPosition);
		}
	}
}