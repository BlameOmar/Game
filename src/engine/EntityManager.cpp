/**************************************************************************************************
 * @file    EntityManager.cpp
 * @date    2014-04-06
 * @brief   Manages Entities
 * @details <#Detailed Description#>
 **************************************************************************************************/

#include "EntityManager.h"

namespace evansbros {
    namespace game {

        EntityManager::EntityManager(ComponentManager & componentManager)
        : componentManager(componentManager) {}

        UniqueID EntityManager::nextUID = 0;

        size_t EntityManager::countEntities() const {
            return entityArray.getCount();
        }

        UniqueID EntityManager::createEntity() {
            UniqueID uid = nextUID++;
            entityLookupTable[uid] = entityArray.add({uid});
            return uid;
        }

        bool EntityManager::entityExists(UniqueID uid) const {
            return entityLookupTable.count(uid) != 0;
        }

        Entity & EntityManager::getEntity(UniqueID uid) {
            if (!entityExists(uid)) {
                throw std::runtime_error("The specified entity could not be found.");
            }
            return entityArray[entityLookupTable[uid]];
        }

        const Entity & EntityManager::getEntity(UniqueID uid) const {
            if (!entityExists(uid)) {
                throw std::runtime_error("The specified entity could not be found.");
            }
            return entityArray[entityLookupTable.at(uid)];
        }

        Entity * EntityManager::getAllEntities() {
            return entityArray.getData();
        }

        const Entity * EntityManager::getAllEntities() const {
            return entityArray.getData();
        }

        void EntityManager::destroyEntity(UniqueID uid) {
            if (!entityExists(uid)) {
                throw std::runtime_error("The specified entity could not be found.");
            }
            for (auto & pair: entityToComponentMaps) {
                if (pair.second.count(uid) != 0) {
                    componentManager.removeComponent(pair.second[uid]);
                }
            }
            Index thisIndex = entityLookupTable[uid];
            Index lastIndex = entityArray.getCount() - 1;

            Entity & thisEntity = entityArray[thisIndex];
            Entity & lastEntity = entityArray[lastIndex];

            thisEntity = lastEntity;
            entityArray.deleteLast();

            entityLookupTable[lastEntity.uid] = thisIndex;
            entityLookupTable.erase(uid);

        }
        void EntityManager::destoryAllEntities() {
            while (countEntities() != 0) {
                destroyEntity(entityArray[0].uid);
            }
        }
    }
}