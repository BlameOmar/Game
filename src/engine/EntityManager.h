/**************************************************************************************************
 * @file    EntityManager.h
 * @date    2014-04-06
 * @brief   Manages Entities
 * @details <#Detailed Description#>
 **************************************************************************************************/

#pragma once

#include <map>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>

#include "Array.h"
#include "Entity.h"
#include "ComponentManager.h"

namespace evansbros {
    namespace game {
        class EntityManager {
        public:
            EntityManager(ComponentManager & componentManager);

            size_t countEntities() const;
            UniqueID createEntity();
            bool entityExists(UniqueID uid) const;
            Entity & getEntity(UniqueID uid);
            const Entity & getEntity(UniqueID uid) const;
            Entity * getAllEntities();
            const Entity * getAllEntities() const;
            void destroyEntity(UniqueID uid);
            void destoryAllEntities();

            template <class ComponentType>
            UniqueID addToEntity(UniqueID entityUID) {
                if (!entityExists(entityUID)) {
                    throw std::runtime_error("The specified entity could not be found.");
                }
                if (entityHas<ComponentType>(entityUID)) {
                    throw std::runtime_error("A component of this type already exists.");
                }
                const std::type_index t = std::type_index(typeid(ComponentType));
                UniqueID componentUID = componentManager.add<ComponentType>({entityUID});
                entityToComponentMaps[t][entityUID] = componentUID;

                return componentUID;
            }

            template <class ComponentType>
            ComponentType & getBelongingToEntity(UniqueID entityUID) {
                if (!entityHas<ComponentType>(entityUID)) {
                    throw std::runtime_error("The specified component could not be found.");
                }
                const std::type_index t = std::type_index(typeid(ComponentType));
                return componentManager.get<ComponentType>(entityToComponentMaps[t][entityUID]);
            }

            template <class ComponentType>
            const ComponentType & getBelongingToEntity(UniqueID entityUID) const {
                if (!entityHas<ComponentType>(entityUID)) {
                    throw std::runtime_error("The specified component could not be found.");
                }
                const std::type_index t = std::type_index(typeid(ComponentType));
                return componentManager.get<ComponentType>(entityToComponentMaps.at(t).at(entityUID));
            }

            template <class ComponentType>
            Entity & getOwnerOf(UniqueID componentUID) {
                if (!componentManager.exists<ComponentType>(componentUID)) {
                    throw std::runtime_error("The specified component could not be found.");
                }
                return entityLookupTable[componentManager.get<ComponentType>(componentUID).getEntityUID()];
            }

            template <class ComponentType>
            const Entity & getOwnerOf(UniqueID componentUID) const {
                if (!componentManager.exists<ComponentType>(componentUID)) {
                    throw std::runtime_error("The specified component could not be found.");
                }
                return entityLookupTable.at(componentManager.get<ComponentType>(componentUID).getEntityUID());
            }

            template <class ComponentType>
            bool entityHas(UniqueID entityUID) const {
                const std::type_index t = std::type_index(typeid(ComponentType));
                if (entityToComponentMaps.count(t) == 0) {
                    return false;
                }
                return entityToComponentMaps.at(t).count(entityUID) != 0;
            }
        private:
            static UniqueID nextUID;
            
            Array<Entity> entityArray;

            std::unordered_map<UniqueID, Index> entityLookupTable;
            std::map<std::type_index, std::unordered_map<UniqueID, UniqueID>> entityToComponentMaps;

            ComponentManager & componentManager;
        };
    }
}