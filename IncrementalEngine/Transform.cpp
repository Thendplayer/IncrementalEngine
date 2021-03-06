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

#include "Transform.h"

namespace IncrementalEngine 
{
    const Transform Transform::Identity;

    Transform::Transform()
    {
        _matrix[0] = 1.f; _matrix[4] = 0.f; _matrix[8]  = 0.f; _matrix[12] = 0.f;
        _matrix[1] = 0.f; _matrix[5] = 1.f; _matrix[9]  = 0.f; _matrix[13] = 0.f;
        _matrix[2] = 0.f; _matrix[6] = 0.f; _matrix[10] = 1.f; _matrix[14] = 0.f;
        _matrix[3] = 0.f; _matrix[7] = 0.f; _matrix[11] = 0.f; _matrix[15] = 1.f;
    }

    Transform::Transform(
        float a00, float a01, float a02,
        float a10, float a11, float a12,
        float a20, float a21, float a22
    )
    {
        _matrix[0] = a00; _matrix[4] = a01; _matrix[8]  = 0.f; _matrix[12] = a02;
        _matrix[1] = a10; _matrix[5] = a11; _matrix[9]  = 0.f; _matrix[13] = a12;
        _matrix[2] = 0.f; _matrix[6] = 0.f; _matrix[10] = 1.f; _matrix[14] = 0.f;
        _matrix[3] = a20; _matrix[7] = a21; _matrix[11] = 0.f; _matrix[15] = a22;
    }

    const float* Transform::GetMatrix() const
    {
        return _matrix;
    }

    Transform Transform::GetInverse() const
    {
        float det = _matrix[0] * (_matrix[15] * _matrix[5] - _matrix[7] * _matrix[13]) -
                    _matrix[1] * (_matrix[15] * _matrix[4] - _matrix[7] * _matrix[12]) +
                    _matrix[3] * (_matrix[13] * _matrix[4] - _matrix[5] * _matrix[12]);

        if (det != 0.f)
        {
            return Transform( (_matrix[15] * _matrix[5] - _matrix[7] * _matrix[13]) / det,
                             -(_matrix[15] * _matrix[4] - _matrix[7] * _matrix[12]) / det,
                              (_matrix[13] * _matrix[4] - _matrix[5] * _matrix[12]) / det,
                             -(_matrix[15] * _matrix[1] - _matrix[3] * _matrix[13]) / det,
                              (_matrix[15] * _matrix[0] - _matrix[3] * _matrix[12]) / det,
                             -(_matrix[13] * _matrix[0] - _matrix[1] * _matrix[12]) / det,
                              (_matrix[7]  * _matrix[1] - _matrix[3] * _matrix[5])  / det,
                             -(_matrix[7]  * _matrix[0] - _matrix[3] * _matrix[4])  / det,
                              (_matrix[5]  * _matrix[0] - _matrix[1] * _matrix[4])  / det
            );
        }
        else
        {
            return Identity;
        }
    }

    D3DXVECTOR2 Transform::TransformPoint(float x, float y) const
    {
        return D3DXVECTOR2(
            _matrix[0] * x + _matrix[4] * y + _matrix[12],
            _matrix[1] * x + _matrix[5] * y + _matrix[13]
        );
    }

    D3DXVECTOR2 Transform::TransformPoint(const D3DXVECTOR2& point) const
    {
        return TransformPoint(point.x, point.y);
    }

    FloatRect Transform::TransformRect(const FloatRect& rectangle) const
    {
        const D3DXVECTOR2 points[] =
        {
            TransformPoint(rectangle.left(), rectangle.top()),
            TransformPoint(rectangle.left(), rectangle.top() + rectangle.height()),
            TransformPoint(rectangle.left() + rectangle.width(), rectangle.top()),
            TransformPoint(rectangle.left() + rectangle.width(), rectangle.top() + rectangle.height())
        };

        float left = points[0].x;
        float top = points[0].y;
        float right = points[0].x;
        float bottom = points[0].y;

        for (int i = 1; i < 4; ++i)
        {
            if (points[i].x < left)   left = points[i].x;
            else if (points[i].x > right)  right = points[i].x;
            if (points[i].y < top)    top = points[i].y;
            else if (points[i].y > bottom) bottom = points[i].y;
        }

        return FloatRect(left, top, right - left, bottom - top);
    }

    Transform& Transform::Combine(const Transform& transform)
    {
        const float* a = _matrix;
        const float* b = transform._matrix;

        *this = Transform(a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
                          a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
                          a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
                          a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
                          a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
                          a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
                          a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
                          a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
                          a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);

        return *this;
    }

    Transform& Transform::Translate(float x, float y)
    {
        Transform translation(1, 0, x,
                              0, 1, y,
                              0, 0, 1);

        return Combine(translation);
    }

    Transform& Transform::Translate(const D3DXVECTOR2& offset)
    {
        return Translate(offset.x, offset.y);
    }

    Transform& Transform::Rotate(float angle)
    {
        float rad = angle * 3.141592654f / 180.f;
        float cos = std::cos(rad);
        float sin = std::sin(rad);

        Transform rotation(cos, -sin, 0,
                           sin,  cos, 0,
                           0,    0,   1);

        return Combine(rotation);
    }

    Transform& Transform::Rotate(float angle, float centerX, float centerY)
    {
        float rad = angle * 3.141592654f / 180.f;
        float cos = std::cos(rad);
        float sin = std::sin(rad);

        Transform rotation(cos, -sin, centerX * (1 - cos) + centerY * sin,
                           sin,  cos, centerY * (1 - cos) - centerX * sin,
                           0,    0,   1);

        return Combine(rotation);
    }

    Transform& Transform::Rotate(float angle, const D3DXVECTOR2& center)
    {
        return Rotate(angle, center.x, center.y);
    }

    Transform& Transform::Scale(float scaleX, float scaleY)
    {
        Transform scaling(scaleX, 0,      0,
                          0,      scaleY, 0, 
                          0,      0,      1);

        return Combine(scaling);
    }

    Transform& Transform::Scale(float scaleX, float scaleY, float centerX, float centerY)
    {
        Transform scaling(scaleX, 0,      centerX * (1 - scaleX),
                          0,      scaleY, centerY * (1 - scaleY),
                          0,      0,      1);

        return Combine(scaling);
    }

    Transform& Transform::Scale(const D3DXVECTOR2& factors)
    {
        return Scale(factors.x, factors.y);
    }

    Transform& Transform::Scale(const D3DXVECTOR2& factors, const D3DXVECTOR2& center)
    {
        return Scale(factors.x, factors.y, center.x, center.y);
    }

    Transform operator *(const Transform& left, const Transform& right)
    {
        return Transform(left).Combine(right);
    }

    Transform& operator *=(Transform& left, const Transform& right)
    {
        return left.Combine(right);
    }

    D3DXVECTOR2 operator *(const Transform& left, const D3DXVECTOR2& right)
    {
        return left.TransformPoint(right);
    }

    bool operator ==(const Transform& left, const Transform& right)
    {
        const float* a = left.GetMatrix();
        const float* b = right.GetMatrix();

        return ((a[0] == b[0])   && (a[1] == b[1])   && (a[3] == b[3]) && 
                (a[4] == b[4])   && (a[5] == b[5])   && (a[7] == b[7]) &&
                (a[12] == b[12]) && (a[13] == b[13]) && (a[15] == b[15]));
    }

    bool operator !=(const Transform& left, const Transform& right)
    {
        return !(left == right);
    }
}