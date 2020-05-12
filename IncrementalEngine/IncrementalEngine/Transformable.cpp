////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2019 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// This script is a modification of the SFML source code, 
// to accommodate it into the Incremental Engine solution.
// 
////////////////////////////////////////////////////////////

#include "Transformable.h"

namespace IncrementalEngine 
{
    Transformable::Transformable() :
        _origin(0, 0),
        _position(0, 0),
        _rotation(0),
        _scale(1, 1),
        _transform(),
        _transformNeedUpdate(true),
        _inverseTransform(),
        _inverseTransformNeedUpdate(true)
    {
    }

    void Transformable::SetPosition(float x, float y)
    {
        _position.x = x;
        _position.y = y;
        _transformNeedUpdate = true;
        _inverseTransformNeedUpdate = true;
    }

    void Transformable::SetPosition(const D3DXVECTOR2& position)
    {
        SetPosition(position.x, position.y);
    }

    void Transformable::SetRotation(float angle)
    {
        _rotation = static_cast<float>(fmod(angle, 360));
        if (_rotation < 0)
            _rotation += 360.f;

        _transformNeedUpdate = true;
        _inverseTransformNeedUpdate = true;
    }

    void Transformable::SetScale(float factorX, float factorY)
    {
        _scale.x = factorX;
        _scale.y = factorY;
        _transformNeedUpdate = true;
        _inverseTransformNeedUpdate = true;
    }

    void Transformable::SetScale(const D3DXVECTOR2& factors)
    {
        SetScale(factors.x, factors.y);
    }

    void Transformable::SetOrigin(float x, float y)
    {
        _origin.x = x;
        _origin.y = y;
        _transformNeedUpdate = true;
        _inverseTransformNeedUpdate = true;
    }

    void Transformable::SetOrigin(const D3DXVECTOR2& origin)
    {
        SetOrigin(origin.x, origin.y);
    }

    const D3DXVECTOR2& Transformable::GetPosition() const
    {
        return _position;
    }

    float Transformable::GetRotation() const
    {
        return _rotation;
    }

    const D3DXVECTOR2& Transformable::GetScale() const
    {
        return _scale;
    }

    const D3DXVECTOR2& Transformable::GetOrigin() const
    {
        return _origin;
    }

    void Transformable::Move(float offsetX, float offsetY)
    {
        SetPosition(_position.x + offsetX, _position.y + offsetY);
    }

    void Transformable::Move(const D3DXVECTOR2& offset)
    {
        SetPosition(_position.x + offset.x, _position.y + offset.y);
    }

    void Transformable::Rotate(float angle)
    {
        SetRotation(_rotation + angle);
    }

    void Transformable::Scale(float factorX, float factorY)
    {
        SetScale(_scale.x * factorX, _scale.y * factorY);
    }

    void Transformable::Scale(const D3DXVECTOR2& factor)
    {
        SetScale(_scale.x * factor.x, _scale.y * factor.y);
    }

    const Transform& Transformable::GetTransform() const
    {
        if (_transformNeedUpdate)
        {
            float angle  = -_rotation * 3.141592654f / 180.f;
            float cosine = static_cast<float>(std::cos(angle));
            float sine   = static_cast<float>(std::sin(angle));
            float sxc    = _scale.x * cosine;
            float syc    = _scale.y * cosine;
            float sxs    = _scale.x * sine;
            float sys    = _scale.y * sine;
            float tx     = -_origin.x * sxc - _origin.y * sys + _position.x;
            float ty     =  _origin.x * sxs - _origin.y * syc + _position.y;
            
            _transform = Transform(
                sxc, sys, tx,
               -sxs, syc, ty,
                0.f, 0.f, 1.f
            );

            _transformNeedUpdate = false;
        }

        return _transform;
    }

    const Transform& Transformable::GetInverseTransform() const
    {
        if (_inverseTransformNeedUpdate)
        {
            _inverseTransform = GetTransform().GetInverse();
            _inverseTransformNeedUpdate = false;
        }

        return _inverseTransform;
    }
}