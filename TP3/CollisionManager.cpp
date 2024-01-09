#include "CollisionManager.h"

#include <chrono>
#include <raylib.h>

using namespace std::chrono;

using namespace std;

CollisionManager::CollisionManager(EntityList& entities)
    : _entities{entities}
{}

// Returns a scalar value that represents the position of a given point as
// projected along a given axis
float projectPoint(Vector2 point, Vector2 axis)
{
    float multiplier = (point.x * axis.x + point.y * axis.y) /
        (powf(axis.x, 2) + powf(axis.y, 2));
    return multiplier * powf(axis.x, 2) + multiplier * powf(axis.y, 2);
}

// Determine minimum and maxiumum scalar values from all corners
// on a given axis
void setMinMax(HitBox& h, Vector2 axis, float& outMin, float& outMax)
{
    float biggest;
    float smallest = biggest = projectPoint(h.getTl(), axis);

    float n = projectPoint(h.getTr(), axis);
    if (n > biggest) { biggest = n; }
    if (n < smallest) { smallest = n; }

    n = projectPoint(h.getBl(), axis);
    if (n > biggest) { biggest = n; }
    if (n < smallest) { smallest = n; }

    n = projectPoint(h.getBr(), axis);
    if (n > biggest) { biggest = n; }
    if (n < smallest) { smallest = n; }

    outMin = smallest;
    outMax = biggest;
}

// Return true if two given hit boxes are overlapping as
// projected on a given axis
bool testAxis(HitBox& h1, HitBox& h2, Vector2 axis)
{
    float h1_min, h1_max, h2_min, h2_max;

    setMinMax(h1, axis, h1_min, h1_max);
    setMinMax(h2, axis, h2_min, h2_max);

    return (h2_min <= h1_max && h2_min >= h1_min) || (h2_max <= h1_max && h2_max >= h1_min);
}

// Returns true if two hitboxes are overlapping
bool checkHitBoxes(HitBox& h1, HitBox& h2)
{
    // Check by radius method to avoid expensive Separating Axis Method when possible
    // Calculate distance of each center
    const float center_distance = powf(h1.getCenterX() - h2.getCenterX(), 2.0f) + powf(
        h1.getCenterY() - h2.getCenterY(), 2.0f);

    // Add radii from both hit boxes
    const float total_radii = h1.getRadius() + h2.getRadius();
    if (total_radii > center_distance)
    {
        // Radius method is inconclusive, measure with Separating Axis Theorem instead
        // https://www.gamedev.net/resources/_/technical/game-programming/2d-rotated-rectangle-collision-r2604
        Vector2 axis1, axis2, axis3, axis4;

        axis1.x = h1.getTr().x - h1.getTl().x;
        axis1.y = h1.getTr().y - h1.getTl().y;
        if (!testAxis(h1, h2, axis1))
        {
            return false;
        }

        axis2.x = h1.getTr().x - h1.getBr().x;
        axis2.y = h1.getTr().y - h1.getBr().y;
        if (!testAxis(h1, h2, axis2))
        {
            return false;
        }

        axis3.x = h2.getTl().x - h2.getBl().x;
        axis3.y = h2.getTl().y - h2.getBl().y;
        if (!testAxis(h1, h2, axis3))
        {
            return false;
        }

        axis4.x = h2.getTl().x - h2.getTr().x;
        axis4.y = h2.getTl().y - h2.getTr().y;
        if (!testAxis(h1, h2, axis4))
        {
            return false;
        }

        return true;
    }

    return false;
}

// Check for collisions and notify entities
void CollisionManager::checkCollisions() const
{
    for (unsigned int i = 0; i < _entities.size(); i++)
    {
        if (_entities[i]->collides())
        {
            for (unsigned int j = 0; j < _entities.size(); j++)
            {
                // Make sure not to check it against itself
                if (j != i)
                {
                    if (_entities[i]->doesCollide(_entities[j]->getId()))
                    {
                        // Do the hitboxes overlap?
                        if (checkHitBoxes(_entities[i]->getHitBox(), _entities[j]->getHitBox()))
                        {
                            // If so, notify the entites
                            _entities[i]->collideEntity(*_entities[j]);
                            _entities[j]->collideEntity(*_entities[i]);
                        }
                    }
                }
            }
        }
    }
}
