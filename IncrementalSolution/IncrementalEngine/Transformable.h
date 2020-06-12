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

#ifndef _TRANSFORMABLE_H
#define _TRANSFORMABLE_H

#include "Transform.h"

namespace IncrementalEngine
{
    class Transformable
    {
    public:
        Transformable();

        virtual void SetPosition(float x, float y);
        virtual void SetPosition(const D3DXVECTOR2& position);
        virtual void SetScale(float factorX, float factorY);
        virtual void SetScale(const D3DXVECTOR2& factors);
        virtual void SetOrigin(float x, float y);
        virtual void SetOrigin(const D3DXVECTOR2& origin);
        virtual void SetRotation(float angle);
        
        virtual const D3DXVECTOR2& GetPosition() const;
        virtual float GetRotation() const;
        virtual const D3DXVECTOR2& GetScale() const;
        virtual const D3DXVECTOR2& GetOrigin() const;

        void Move(float offsetX, float offsetY);
        void Move(const D3DXVECTOR2& offset);

        void Rotate(float angle);

        void Scale(float factorX, float factorY);
        void Scale(const D3DXVECTOR2& factor);

        const Transform& GetTransform() const;
        const Transform& GetInverseTransform() const;

    protected:
        mutable bool _transformNeedUpdate;

    private:
        D3DXVECTOR2 _origin;
        D3DXVECTOR2 _position;
        D3DXVECTOR2 _scale;
        float _rotation;

        mutable Transform _transform;
        mutable Transform _inverseTransform;
        mutable bool _inverseTransformNeedUpdate;
    };
}

#endif