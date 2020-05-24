#include "Actor.h"
#include "Utils.h"

namespace IncrementalEngine 
{	
	Actor::~Actor()
	{
		vector<Actor*> children = _children;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->SetParent(nullptr);
		}
		_children.clear();
	}

	void Actor::Init()
	{
	}

	void Actor::Update()
	{
	}

	void Actor::SetActive(bool active)
	{
		_active = active;
	}

	bool Actor::IsActive()
	{
		return _active;
	}

	void Actor::UpdateRecursive()
	{
		if (!_active) return;

		Update();

		for (int i = 0; i < _children.size(); i++)
		{
			_children[i]->UpdateRecursive();
		}
	}

	HRESULT Actor::DrawRecursive(ID3D11DeviceContext* deviceContext)
	{
		HRESULT result;

		if (!_active) return S_OK;

		result = Draw(deviceContext);

		if (FAILED(result))
		{
			return CO_E_ERRORINAPP;
		}

		for (int i = 0; i < _children.size(); i++)
		{
			result = _children[i]->DrawRecursive(deviceContext);
			
			if (FAILED(result))
			{
				return CO_E_ERRORINAPP;
			}
		}

		return S_OK;
	}

	HRESULT Actor::Draw(ID3D11DeviceContext* deviceContext)
	{
		return S_OK;
	}

	void Actor::Center()
	{
		auto origin = D3DXVECTOR2(GetLocalBounds().width() * .5f, GetLocalBounds().height() * .5f);
		SetOrigin(origin);
	}

	FloatRect Actor::GetLocalBounds()
	{
		return FloatRect();
	}

	FloatRect Actor::GetGlobalBounds()
	{
		return GetWorldTransform().TransformRect(GetLocalBounds());
	}

	const Transform Actor::GetWorldTransform()
	{
		auto worldTransform = Transformable();
		
		worldTransform.SetPosition(GetWorldPosition());
		worldTransform.SetRotation(GetWorldRotation());
		worldTransform.SetScale(GetWorldScale());
		worldTransform.SetOrigin(GetOrigin());

		return worldTransform.GetTransform();
	}

	const D3DXVECTOR2 Actor::GetWorldPosition()
	{
		if (_parent != nullptr)
		{
			return _parent->GetWorldPosition() + GetPosition();
		}

		return GetPosition();
	}

	const D3DXVECTOR2 Actor::GetWorldScale()
	{
		if (_parent != nullptr)
		{
			D3DXVECTOR2 scale = GetScale();
			D3DXVECTOR2 parentWorldScale = _parent->GetWorldScale();
			D3DXVECTOR2 worldScale = {
				parentWorldScale.x * scale.x,
				parentWorldScale.y * scale.y
			};

			return worldScale;
		}

		return GetScale();
	}

	const float Actor::GetWorldRotation()
	{
		if (_parent != nullptr)
		{
			float worldRotation = _parent->GetWorldRotation() + GetRotation();
			worldRotation = static_cast<float>(fmod(worldRotation, 360));

			if (worldRotation < 0)
			{
				worldRotation += 360.f;
			}

			return worldRotation;
		}

		return GetRotation();
	}

	void Actor::SetWorldPosition(D3DXVECTOR2 value)
	{
		D3DXVECTOR2 newPosition;

		if (_parent != nullptr)
		{
			newPosition = _parent->GetWorldTransform().GetInverse().TransformPoint(value);
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

	void Actor::SetParent(Actor* value, const bool fixWorldPosition)
	{
		if (value != _parent)
		{
			auto prevWorldPosition = GetWorldTransform() * GetOrigin();

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

			if (fixWorldPosition) 
			{
				SetWorldPosition(prevWorldPosition);
			}
		}
	}
}