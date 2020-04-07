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

namespace MyEngine
{
    class Transformable
    {
        public:
        Transformable();
        ~Transformable();

        void SetPosition(float x, float y);
        void SetPosition(const Vector2f& position);
        void SetRotation(float angle);
        void SetScale(float factorX, float factorY);
        void SetScale(const Vector2f& factors);
        void SetOrigin(float x, float y);
        void SetOrigin(const Vector2f& origin);
        const Vector2f& GetPosition() const;
        float GetRotation() const;
        const Vector2f& GetScale() const;
        const Vector2f& GetOrigin() const;

        void Move(float offsetX, float offsetY);
        void Move(const Vector2f& offset);

        void Rotate(float angle);

        void Scale(float factorX, float factorY);
        void Scale(const Vector2f& factor);

        const Transform& GetTransform() const;
        const Transform& GetInverseTransform() const;

    private:
        Vector2f _origin;
        Vector2f _position;
        float _rotation;
        Vector2f _scale;
        mutable Transform _transform;
        mutable bool _transformNeedUpdate;
        mutable Transform _inverseTransform;
        mutable bool _inverseTransformNeedUpdate;
    };
}

#endif