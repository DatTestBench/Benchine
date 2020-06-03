#include "BenchinePCH.h"
#include "Helpers/SAT.h"
#include "Components/PhysicsComponent2D.h"
#include "Components/TransformComponent.h"
#include "Helpers/MathHelper.h"
#include "glm/geometric.hpp"

// Collision for GameObjects
PolygonCollisionResult sat::PolygonCollision(PhysicsComponent2D* pActorA, PhysicsComponent2D* pActorB)
{
	glm::vec2 velocityDelta = pActorA->GetVelocity() - pActorB->GetVelocity();

	PolygonCollisionResult result{};
	result.intersect = true;
	result.willIntersect = true;

	Collider2D colliderA = pActorA->GetCollider(); 
	Collider2D colliderB = pActorB->GetCollider();
	size_t vertexCountA = colliderA.size();
	size_t vertexCountB = colliderB.size();

	float minIntervalDistance = std::numeric_limits<float>::infinity();
	glm::vec2 translationAxis{};
	glm::vec2 vertex{};
	glm::vec2 nextVertex{};

	// Loop through all the vertecis of both polygons
	for (size_t vertexIndex = 0; vertexIndex < vertexCountA + vertexCountB; ++vertexIndex)
	{
		if (vertexIndex < vertexCountA)
		{
			vertex = colliderA.at(vertexIndex);
			nextVertex = colliderA.at(vertexIndex + 1 == vertexCountA ? 0 : vertexIndex + 1);
		}
		else
		{
			vertex = colliderB.at(vertexIndex - vertexCountA);
			nextVertex = colliderB.at(vertexIndex - vertexCountA + 1 == vertexCountA ? 0 : vertexIndex - vertexCountA + 1);
		}

		// ===== 1. Find if the polygons are currently intersecting =====

		// Find the axis perpendicular to the current edge (vertexpair)s
		const auto axis = MakeAxis(vertex, nextVertex);

		// Find the projection of the polygon on the current axis
		float minA{ 0 }, minB{ 0 }, maxA{ 0 }, maxB{ 0 };
		ProjectPolygon(axis, colliderB, minA, maxA);
		ProjectPolygon(axis, colliderB, minB, maxB);

		// Check if the polygon projections are currentlty intersecting
		if (IntervalDistance(minA, maxA, minB, maxB) > 0)
		{
			result.intersect = false;
		}

		/***DEPRECATED**
		// ===== 2. Now find if the polygons *will* intersect =====
		// Project the velocity on the current axis
		float velocityProjection{ axis.DotProduct(dVelocity) };
		// Get the projection of polygon A during the movement
		if (velocityProjection < 0)
		{
			minA += velocityProjection;
		}
		else
		{
			maxA += velocityProjection;
		}
		// Do the same test as above for the new projection

		if (IntervalDistance(minA, maxA, minB, maxB) > 0)
			result.willIntersect = false;
		// If the polygons are not intersecting and won't intersect, exit the loop
		if (!result.intersect && !result.willIntersect)
			break;
		**DEPRECATED***/


		// If the polygon does not intersect, exit the loop
		if (!result.intersect)
			break;

		// Check if the current interval distance is the minimum one. If so store
		// the interval distance and the current distance.
		// This will be used to calculate the minimum translation vector
		float intervalDistance = abs(IntervalDistance(minA, maxA, minB, maxB));
		if (intervalDistance < minIntervalDistance)
		{
			minIntervalDistance = intervalDistance;
			translationAxis = axis;

			glm::vec2 delta = pActorA->GetTransform()->GetPosition() - pActorB->GetTransform()->GetPosition();
			if (glm::dot(delta, translationAxis) < 0)
				translationAxis = -translationAxis;
		}
	}

	// The minimum translation vector
	// can be used to push the polygons appart.
	if (result.willIntersect)
		result.minimumTranslationVector = translationAxis * minIntervalDistance;

	return result;
}


// Collision for GameObject to static collider
PolygonCollisionResult sat::PolygonCollision(PhysicsComponent2D* pActor, const Collider2D& staticPoly)
{
	glm::vec2 velocityDelta = pActor->GetVelocity();

	PolygonCollisionResult result{};
	result.intersect = true;
	result.willIntersect = true;

	Collider2D collider = pActor->GetCollider();

	size_t vertexCountA = collider.size();
	size_t vertexCountB = staticPoly.size();
	float minIntervalDistance = std::numeric_limits<float>::infinity();
	glm::vec2 translationAxis{}, currentVertex{}, nextVertex{};

	// Loop through all the vertecis of both polygons
	for (size_t vertexIndex = 0; vertexIndex < vertexCountA + vertexCountB; ++vertexIndex)
	{
		if (vertexIndex < vertexCountA)
		{
			currentVertex = collider.at(vertexIndex);
			nextVertex = collider.at(vertexIndex + 1 == vertexCountA ? 0 : vertexIndex + 1);
		}
		else
		{
			currentVertex = staticPoly.at(vertexIndex - vertexCountA);
			nextVertex = staticPoly.at(vertexIndex - vertexCountA + 1 == vertexCountA ? 0 : vertexIndex - vertexCountA + 1);
		}

		// ===== 1. Find if the polygons are currently intersecting =====

		// Find the axis perpendicular to the current edge (vertexpair)s
		glm::vec2 axis = MakeAxis(currentVertex, nextVertex);

		// Find the projection of the polygon on the current axis
		float minA{ 0 }, minB{ 0 }, maxA{ 0 }, maxB{ 0 };
		ProjectPolygon(axis, collider, minA, maxA);
		ProjectPolygon(axis, staticPoly, minB, maxB);

		// Check if the polygon projections are currentlty intersecting
		if (IntervalDistance(minA, maxA, minB, maxB) > 0)
			result.intersect = false;

		// If the polygon does not intersect, exit the loop
		if (!result.intersect)
			break;

		// Check if the current interval distance is the minimum one. If so store
		// the interval distance and the current distance.
		// This will be used to calculate the minimum translation vector
		float intervalDistance = abs(IntervalDistance(minA, maxA, minB, maxB));
		if (intervalDistance < minIntervalDistance)
		{
			minIntervalDistance = intervalDistance;
			translationAxis = axis;
			
			glm::vec2 delta = glm::vec2(pActor->GetTransform()->GetPosition()) - MathHelper::PolyCenter(staticPoly);
			if (glm::dot(delta, translationAxis) < 0)
				translationAxis = -translationAxis;
		}
	}

	// The minimum translation vector
	// can be used to push the polygons appart.
	if (result.willIntersect)
		result.minimumTranslationVector = translationAxis * minIntervalDistance;

	return result;
}

void sat::ProjectPolygon(const glm::vec2& axis, const Collider2D& polygon, float& min, float& max)
{
	// To project a point on an axis use the dot product
	float dotProduct = glm::dot(axis, polygon.at(0));
	min = max = dotProduct;
	for (size_t i = 0; i < polygon.size(); ++i)
	{
		dotProduct = glm::dot(axis, polygon.at(i));
		if (dotProduct < min)
			min = dotProduct;
		else if (dotProduct > max)
			max = dotProduct;
	}
}

float sat::IntervalDistance(float minA, float maxA, float minB, float maxB)
{
	if (minA < minB)
		return minB - maxA;
	else
		return minA - maxB;
}

glm::vec2 sat::MakeAxis(const glm::vec2& vertexA, const glm::vec2& vertexB)
{
	// Get edge
	const glm::vec2 edge = vertexB - vertexA;
	// get either perpendicular vector
	const glm::vec2 normal{ -edge.y, edge.x };
	//return normalized
	return glm::normalize(normal);
}