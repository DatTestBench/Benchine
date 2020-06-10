#include "BenchinePCH.h"
#include "Components/PhysicsComponent2D.h"
#include "Components/TransformComponent.h"
PhysicsComponent2D::PhysicsComponent2D()
{
    
}

PhysicsComponent2D::~PhysicsComponent2D()
{

}

void PhysicsComponent2D::Initialize()
{
	GetGameObject()->GetScene()->AddPhysicsObject(this);
}

Collider2D PhysicsComponent2D::GetColliderTransformed()
{
    auto transformedCollider = m_Collider;
    auto tMat = glm::translate(glm::mat3(1.f), static_cast<glm::vec2>(GetTransform()->GetPosition()));

    for (auto& vertex : transformedCollider)
    {
        vertex =  tMat * glm::vec3(vertex, 1.f);
    }
    return transformedCollider;
}

void PhysicsComponent2D::HandleCollision(PhysicsComponent2D* pOtherComponent)
{
    auto collisionResult = sat::PolygonCollision(this, pOtherComponent);

    if (collisionResult.intersect && collisionResult.minimumTranslationVector.y >= 0)
    {
        GetTransform()->Move(collisionResult.minimumTranslationVector);
        //pOtherComponent->GetTransform()->Move(collisionResult.minimumTranslationVector / 2.f);
    }

}