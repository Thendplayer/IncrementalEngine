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

#include <Windows.h>
#include<Eigen>

using Eigen::Vector2f;

namespace MyEngine
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

        Vector2f TransformPoint(float x, float y) const;
        Vector2f TransformPoint(const Vector2f& point) const;

        RECT TransformRect(const RECT& rectangle) const;

        Transform& Combine(const Transform& transform);

        Transform& Translate(float x, float y);
        Transform& Translate(const Vector2f& offset);

        Transform& Rotate(float angle);
        Transform& Rotate(float angle, float centerX, float centerY);
        Transform& Rotate(float angle, const Vector2f& center);

        Transform& Scale(float scaleX, float scaleY);
        Transform& Scale(float scaleX, float scaleY, float centerX, float centerY);
        Transform& Scale(const Vector2f& factors);
        Transform& Scale(const Vector2f& factors, const Vector2f& center);

    private:

        float _matrix[16];
    };

    Transform operator *(const Transform& left, const Transform& right);
    Transform& operator *=(Transform& left, const Transform& right);
    Vector2f operator *(const Transform& left, const Vector2f& right);
    bool operator ==(const Transform& left, const Transform& right);
    bool operator !=(const Transform& left, const Transform& right);
}

#endif