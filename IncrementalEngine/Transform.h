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

#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "FloatRect.h"
#include <iostream>
#include <D3DX10.h>

using namespace std;

namespace IncrementalEngine
{
    class Transform
    {
    public:
        static const Transform Identity;

        Transform();
        Transform(
            float a00, float a01, float a02,
            float a10, float a11, float a12,
            float a20, float a21, float a22
        );

        const float* GetMatrix() const;
        Transform GetInverse() const;

        D3DXVECTOR2 TransformPoint(float x, float y) const;
        D3DXVECTOR2 TransformPoint(const D3DXVECTOR2& point) const;

        FloatRect TransformRect(const FloatRect& rectangle) const;

        Transform& Combine(const Transform& transform);

        Transform& Translate(float x, float y);
        Transform& Translate(const D3DXVECTOR2& offset);

        Transform& Rotate(float angle);
        Transform& Rotate(float angle, float centerX, float centerY);
        Transform& Rotate(float angle, const D3DXVECTOR2& center);

        Transform& Scale(float scaleX, float scaleY);
        Transform& Scale(float scaleX, float scaleY, float centerX, float centerY);
        Transform& Scale(const D3DXVECTOR2& factors);
        Transform& Scale(const D3DXVECTOR2& factors, const D3DXVECTOR2& center);

    private:
        float _matrix[16];
    };

    Transform operator *(const Transform& left, const Transform& right);
    Transform& operator *=(Transform& left, const Transform& right);
    D3DXVECTOR2 operator *(const Transform& left, const D3DXVECTOR2& right);
    bool operator ==(const Transform& left, const Transform& right);
    bool operator !=(const Transform& left, const Transform& right);
}

#endif