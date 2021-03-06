#include "BenchinePCH.h"
#include "Components/PhysicsComponent2D.h"
#include "Components/TransformComponent.h"
#include <future>

#include "Debugging/DebugRenderer.h"

PhysicsComponent2D::PhysicsComponent2D(const CollisionMode collisionMode)
    : m_CollisionMode(collisionMode)
    , m_PhysicsCallback([](PolygonCollisionResult, PhysicsComponent2D*, PhysicsComponent2D*){})
    , m_CallBackOverriden(false)
    , m_Velocity()
    
    , m_IsOnGround(false)
{
    
}

PhysicsComponent2D::~PhysicsComponent2D()
{

}

void PhysicsComponent2D::Initialize()
{
    switch (m_CollisionMode)
    {
    case CollisionMode::STATIC:
        GetGameObject()->GetScene()->AddStaticObject(this);
        break;
    case CollisionMode::DYNAMIC:
        GetGameObject()->GetScene()->AddDynamicObject(this);
        break;
    case CollisionMode::TRIGGER:
        GetGameObject()->GetScene()->AddTrigger(this);
        break;
    }
}

void PhysicsComponent2D::Update([[maybe_unused]] float dT)
{
    m_IsOnGround = false;
    const auto tMat = glm::translate(glm::mat3(1.f), static_cast<glm::vec2>(GetTransform()->GetPosition()));
    const auto sMat = glm::scale(glm::mat3(1.f), GetTransform()->GetScale());

    const auto transformMat = tMat * sMat;

    for (size_t v = 0; v < m_BaseCollider.size(); ++v)
    {
        m_Collider.at(v) = transformMat * glm::vec3(m_BaseCollider.at(v), 1.f);
    }
    
    DEBUGONLY(DebugRenderer::DrawPolygon(m_Collider));
}

void PhysicsComponent2D::HandleCollision(PhysicsComponent2D* pOtherComponent)
{
    const auto collisionResult = sat::PolygonCollision(this, pOtherComponent);
    if (collisionResult.intersect)
    {
        switch (m_CollisionMode)
        {
        case CollisionMode::STATIC:
            m_PhysicsCallback(collisionResult, this, pOtherComponent);
            break;
        case CollisionMode::DYNAMIC:
            if (!m_CallBackOverriden)
            {
                if (pOtherComponent->GetCollisionMode() == CollisionMode::STATIC)
                {
                    GetTransform()->Move(collisionResult.minimumTranslationVector);
                }
            }
            m_PhysicsCallback(collisionResult, this, pOtherComponent);
            break;
        case CollisionMode::TRIGGER:
            m_PhysicsCallback(collisionResult, this, pOtherComponent);
            break;
        }
    }
}