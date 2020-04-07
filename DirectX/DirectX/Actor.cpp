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

		auto origin = Vector2f(width, height) / 2.0f;
		SetOrigin(origin);
	}

	RECT* Actor::GetLocalBounds()
	{
		return nullptr; //TODO: Continue from here
	}

	HRESULT Actor::Draw(ID3D11DeviceContext* deviceContext)
	{
		
	}
	
	Transform* Actor::GetWorldTransform() const
	{
		if (_parent != nullptr)
		{
			return &(GetTransform() * *_parent->GetWorldTransform());
		}
	}
	
	Vector2f* Actor::GetWorldPosition() const
	{
		return &(*GetWorldTransform() * GetOrigin());
	}
	
	void Actor::SetWorldPosition(Vector2f* value)
	{
		Vector2f newPosition;

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