/**************************************************************************************************
 * Title:         GameState.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-18
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "GameState.h"
#include "SpatialComponent.h"
#include "CollisionalComponent.h"
#include "SpriteComponent.h"

namespace evansbros {
    namespace game {

        UniqueID GameState::createHuman(math::vector2 position)
        {
            UniqueID entityUID = entityManager.createEntity();

            UniqueID spatialComponentUID = entityManager.addToEntity<SpatialComponent>(entityUID);
            SpatialComponent & spatialComponent = componentManager.get<SpatialComponent>(spatialComponentUID);
            spatialComponent.position = position;

            UniqueID collisionalComponentUID = entityManager.addToEntity<CollisionalComponent>(entityUID);
            CollisionalComponent & collisionalComponent = componentManager.get<CollisionalComponent>(collisionalComponentUID);
            collisionalComponent.type = CollisionalComponent::Type::Circular;
            collisionalComponent.data.circularData = {{ 0.0, 0.0 }, 0.5};

            UniqueID spriteComponentUID = entityManager.addToEntity<SpriteComponent>(entityUID);
            SpriteComponent & spriteComponent = componentManager.get<SpriteComponent>(spriteComponentUID);
            spriteComponent.texture = "test";
            
            return entityUID;
        }

        UniqueID GameState::createBall(math::vector2 position)
        {
            UniqueID entityUID = entityManager.createEntity();

            UniqueID spatialComponentUID = entityManager.addToEntity<SpatialComponent>(entityUID);
            SpatialComponent & spatialComponent = componentManager.get<SpatialComponent>(spatialComponentUID);
            spatialComponent.position = position;

            UniqueID collisionalComponentUID = entityManager.addToEntity<CollisionalComponent>(entityUID);
            CollisionalComponent & collisionalComponent = componentManager.get<CollisionalComponent>(collisionalComponentUID);
            collisionalComponent.collisionGroupUID = entityUID;
            collisionalComponent.type = CollisionalComponent::Type::Circular;
            collisionalComponent.data.circularData = {{ 0.0, 0.0 }, 0.5};

            UniqueID spriteComponentUID = entityManager.addToEntity<SpriteComponent>(entityUID);
            SpriteComponent & spriteComponent = componentManager.get<SpriteComponent>(spriteComponentUID);
            spriteComponent.texture = "Ball";

            return entityUID;
        }

        UniqueID GameState::createCamera(math::vector2 position)
        {
            UniqueID entityUID = entityManager.createEntity();

            UniqueID spatialComponentUID = entityManager.addToEntity<SpatialComponent>(entityUID);
            SpatialComponent & spatialComponent = componentManager.get<SpatialComponent>(spatialComponentUID);
            spatialComponent.position = position;

//            UniqueID collisionalComponentUID = entityManager.addToEntity<CollisionalComponent>(entityUID);
//            CollisionalComponent & collisionalComponent = componentManager.get<CollisionalComponent>(collisionalComponentUID);
//            collisionalComponent.collisionGroupUID = entityUID;
//            collisionalComponent.type = CollisionalComponent::Type::Circular;
//            collisionalComponent.data.circularData = {{ 0.0, 0.0 }, 0.5};

            return entityUID;
        }


        void GameState::updateSpatialComponents(seconds dTime)
        {
            size_t count = componentManager.count<SpatialComponent>();
            SpatialComponent * components = componentManager.getAll<SpatialComponent>();
            for (size_t i = 0; i < count; ++i) {
                SpatialComponent & component = components[i];
                component.position += component.velocity * dTime.count();
                if (component.speed() < 0.0625) {
                    component.velocity = {0.0, 0.0};
                }
            }
        }

        void GameState::detectCollisions() {
            size_t count = componentManager.count<CollisionalComponent>();
            CollisionalComponent * components = componentManager.getAll<CollisionalComponent>();
            for (size_t a = 0; a < count; ++a) {
                for (size_t b = a + 1; b < count; ++b) {
                    const CollisionalComponent & collisionalComponentA = components[a];
                    const CollisionalComponent & collisionalComponentB = components[b];
                    if (collisionalComponentA.collisionGroupUID == collisionalComponentB.collisionGroupUID) {
                        continue;
                    }

                    UniqueID entityA = collisionalComponentA.getEntityUID();
                    UniqueID entityB = collisionalComponentB.getEntityUID();

                    /* Testing two circular components */
                    if (collisionalComponentA.type == collisionalComponentB.type &&
                        collisionalComponentA.type == CollisionalComponent::Type::Circular &&
                        componentsAreColliding_2circular(collisionalComponentA, collisionalComponentB)) {

                        collidingEntities.insert({entityA, entityB});
                    }

                }
            }
        }

        bool GameState::componentsAreColliding_2circular(const CollisionalComponent & collisionalComponentA,
                                                         const CollisionalComponent & collisionalComponentB) {
            const UniqueID entityA = collisionalComponentA.getEntityUID();
            const UniqueID entityB = collisionalComponentB.getEntityUID();
            const SpatialComponent & spatialComponentA = entityManager.getBelongingToEntity<SpatialComponent>(entityA);
            const SpatialComponent & spatialComponentB = entityManager.getBelongingToEntity<SpatialComponent>(entityB);

            auto circleA = collisionalComponentA.data.circularData;
            auto circleB = collisionalComponentB.data.circularData;

            circleA.center += spatialComponentA.position;
            circleB.center += spatialComponentB.position;

            return math::geometry::areIntersecting(circleA, circleB);
        }

        bool GameState::componentsAreColliding_2linear(const CollisionalComponent & collisionalComponentA,
                                                       const CollisionalComponent & collisionalComponentB) {
            const UniqueID entityA = collisionalComponentA.getEntityUID();
            const UniqueID entityB = collisionalComponentB.getEntityUID();
            const SpatialComponent & spatialComponentA = entityManager.getBelongingToEntity<SpatialComponent>(entityA);
            const SpatialComponent & spatialComponentB = entityManager.getBelongingToEntity<SpatialComponent>(entityB);

            auto lineSegmentA = collisionalComponentA.data.linearData;
            auto lineSegmentB = collisionalComponentB.data.linearData;

            lineSegmentA.midpoint += spatialComponentA.position;
            lineSegmentB.midpoint += spatialComponentB.position;

            return math::geometry::areIntersecting(lineSegmentA, lineSegmentB);
        }

        void GameState::resolveCollisions() {
            for (auto pair : collidingEntities) {
                UniqueID entityA = pair.first;
                UniqueID entityB = pair.second;
                const CollisionalComponent & collisionalComponentA = entityManager.getBelongingToEntity<CollisionalComponent>(entityA);
                const CollisionalComponent & collisionalComponentB = entityManager.getBelongingToEntity<CollisionalComponent>(entityB);
                SpatialComponent & spatialComponentA = entityManager.getBelongingToEntity<SpatialComponent>(entityA);
                SpatialComponent & spatialComponentB = entityManager.getBelongingToEntity<SpatialComponent>(entityB);
                math::vector2 collisionalComponentA_position = collisionalComponentA.data.offset + spatialComponentA.position;
                math::vector2 collisionalComponentB_position = collisionalComponentB.data.offset + spatialComponentB.position;
                real distance = (collisionalComponentA_position - collisionalComponentB_position).magnitude();
                real delta = (collisionalComponentA.data.circularData.radius + collisionalComponentB.data.circularData.radius - distance) / 2;

                math::vector2 temp = spatialComponentA.velocity;
                spatialComponentA.position += delta * (spatialComponentA.position - spatialComponentB.position) / (spatialComponentA.position - spatialComponentB.position).magnitude();
                spatialComponentA.velocity = spatialComponentB.velocity;
                spatialComponentB.position += delta * (spatialComponentB.position - spatialComponentA.position) / (spatialComponentB.position - spatialComponentA.position).magnitude();
                spatialComponentB.velocity = temp;
            }
            collidingEntities.clear();
        }

    }
}