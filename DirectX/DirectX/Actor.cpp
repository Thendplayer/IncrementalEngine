#include "Actor.h"
#include "Utils.h"

namespace MyEngine 
{
	Actor::Actor() :
		_texture(NULL)
	{
	}
	
	Actor::~Actor()
	{
		CHECKED_DELETE(_texture);

		vector<Actor*> children = _children;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->SetParent(nullptr);
		}
		children.clear();
	}

	void Actor::SetTexture(Texture* texture)
	{
		if (_texture != nullptr)
		{
			if (_texture->GetTexture() == texture)
			{
				return;
			}

			CHECKED_DELETE(_texture);
		}

		auto bitmap = new Bitmap;
		CopyParameters(bitmap);
		HRESULT result = bitmap->Create(texture);

		if (FAILED(result)) 
		{
			throw;
		}

		_texture = bitmap;
		Center();
	}

	void Actor::ClearTexture()
	{
		CHECKED_DELETE(_texture);
	}

	void Actor::Init()
	{
	}

	void Actor::Update()
	{
		_texture->Update(GetTransform(), GetLocalBounds());
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
		HRESULT result;

		if (_texture != nullptr)
		{
			result = _texture->Draw(deviceContext);
		
			if (FAILED(result))
			{
				return CO_E_ERRORINAPP;
			}
		}

		return S_OK;
	}

	void Actor::Center()
	{
		auto origin = D3DXVECTOR2(GetLocalBounds().width(), GetLocalBounds().height()) / 2.0f;
		SetOrigin(origin);
	}

	FloatRect Actor::GetLocalBounds()
	{
		D3DXVECTOR2 size(0.0f, 0.0f);

		if (_texture != nullptr)
		{
			size = D3DXVECTOR2(
				_texture->GetSize().x * _scale.x, 
				_texture->GetSize().y * _scale.y
			);
		}

		FloatRect bounds = { 
			_position.x, 
			_position.y, 
			size.x, 
			size.y 
		};

		return bounds;
	}

	FloatRect Actor::GetGlobalBounds()
	{
		return GetWorldTransform()->TransformRect(GetLocalBounds());
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