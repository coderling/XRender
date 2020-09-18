#pragma once
#include <functional>

#include <geometry.h>

namespace XRender
{
    class Transform final
    {
    public:
        Transform();
        void SetPosition(const Vec3f& position);
        const Vec3f& GetPosition() const;
        void SetRotation(const Vec3f& rotation);
        const Vec3f& GetRotation() const;
        void SetScale(const Vec3f& scale);
        const Vec3f& GetScale() const;
        const Matrix& WorldMatrix() const;
        const Vec3f Up() const;
        const Vec3f Forward() const;
    private:
        void UpdateWorldMatrix();
        Vec3f position;
        Vec3f rotation;
        Vec3f scale;
        Matrix world_matrix;
    };
}