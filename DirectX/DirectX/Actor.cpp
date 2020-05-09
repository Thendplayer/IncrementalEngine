#include "Actor.h"
#include "Utils.h"

namespace MyEngine 
{	
	Actor::~Actor()
	{
		vector<Actor*> children = _children;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->SetParent(nullptr);
		}
		children.clear();
	}

	void Actor::Init()
	{
	}

	void Actor::Update()
	{
	}

	void Actor::UpdateRecursive()
	{
		Update();

		for (int i = 0; i < _children.size(); i++)
		{
			_children[i]->UpdateRecursive();
		}
	}

	HRESULT Actor::DrawRecursive(ID3D11DeviceContext* deviceContext)
	{
		HRESULT result;

		for (int i = 0; i < _children.size(); i++)
		{
			result = _children[i]->DrawRecursive(deviceContext);
			
			if (FAILED(result))
			{
				return CO_E_ERRORINAPP;
			}
		}

		result = Draw(deviceContext);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		return S_OK;
	}

	HRESULT Actor::Draw(ID3D11DeviceContext* deviceContext)
	{
		return S_OK;
	}

	void Actor::Center()
	{
		auto origin = D3DXVECTOR2(GetLocalBounds().width(), GetLocalBounds().height()) / 2.0f;

		if (_parent != nullptr)
		{
			origin -= _parent->GetOrigin();
		}

		SetOrigin(origin);
	}

	FloatRect Actor::GetLocalBounds()
	{
		return FloatRect();
	}

	FloatRect Actor::GetGlobalBounds()
	{
		return GetWorldTransform()->TransformRect(GetLocalBounds());
	}

	const Transform Actor::GetCombinedTransform()
	{
		if (_parent != nullptr) 
		{
			return _parent->GetCombinedTransform() * GetTransform();
		}

		return GetTransform();
	}

	const Transform* Actor::GetWorldTransform() const
	{
		if (_parent != nullptr)
		{
			return &(GetTransform() * *_parent->GetWorldTransform());
		}

		return &GetTransform();
	}

	D3DXVECTOR2 Actor::GetWorldPosition() const
	{
		return (*GetWorldTransform() * GetOrigin());
	}

	void Actor::SetWorldPosition(D3DXVECTOR2 value)
	{
		D3DXVECTOR2 newPosition;

		if (_parent != nullptr)
		{
			newPosition = _parent->GetWorldTransform()->GetInverse().TransformPoint(value);
		}
		else 
		{
			newPosition = value;
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