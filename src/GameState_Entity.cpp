/**************************************************************************************************
 * Title:         GameState_Entity.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-21
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "GameState.h"

namespace evansbros {
    namespace game {
        ID GameState::createEntity() {
            ID entity_id = Entity::next_id++;
            Index entity_index = entities.add({entity_id});
            entityLookupTable[entity_id] = entity_index;

            return entity_id;
        }

        Entity & GameState::getEntityWithID(ID entity_id) {
            if (!existsEntityWithID(entity_id)) {
                throw std::runtime_error("Entity not found");
            }
            return entities[entityLookupTable[entity_id]];
        }

        const Entity & GameState::getEntityWithID(ID entity_id) const {
            if (!existsEntityWithID(entity_id)) {
                throw std::runtime_error("Entity not found");
            }
            return entities[entityLookupTable.at(entity_id)];
        }

        bool GameState::existsEntityWithID(ID entity_id) const {
            if (entityLookupTable.count(entity_id) == 0) {
                return false;
            }
            return true;
        }

        void GameState::destroyEntityWithID(ID entity_id) {
            if (!existsEntityWithID(entity_id)) {
                throw std::runtime_error("Entity not found");
            }
            if (existsSpatialComponentWithEntityID(entity_id)) {
                destroySpatialComponentWithID(getSpatialComponentWithEntityID(entity_id).id);
                entityToSpatialComponentMap.erase(entity_id);
            }

            Index temp_index = entityLookupTable[entity_id];
            Entity temp_entity = entities[entities.getCount() - 1];
            entities[temp_index] = temp_entity;
            entities.deleteLast();
            entityLookupTable.erase(entity_id);
            entityLookupTable[temp_entity.id] = temp_index;
        }

    }
}