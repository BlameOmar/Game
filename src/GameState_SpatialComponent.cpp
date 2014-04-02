/**************************************************************************************************
 * Title:         GameState_SpatialComponent.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-21
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "GameState.h"

namespace evansbros {
    namespace game {

        ID GameState::addSpatialComponentToEntity(ID entity_id) {
            if (!existsEntityWithID(entity_id)) {
                return -1;
            }
            if (entityToSpatialComponentMap.count(entity_id) == 1) {
                return entityToSpatialComponentMap[entity_id];
            }

            ID component_id = SpatialComponent::next_id++;
            Index component_index = spatialComponents.add({component_id, entity_id});
            spatialComponentLookupTable[component_id] = component_index;
            entityToSpatialComponentMap[entity_id] = component_id;

            return component_id;
        }


        SpatialComponent & GameState::getSpatialComponentWithID(ID component_id) {
            if (!existsSpatialComponentWithID(component_id)) {
                throw std::runtime_error("Component not found");
            }
            return spatialComponents[spatialComponentLookupTable[component_id]];
        }

        const SpatialComponent & GameState::getSpatialComponentWithID(ID component_id) const {
            if (!existsSpatialComponentWithID(component_id)) {
                throw std::runtime_error("Component not found");
            }
            return spatialComponents[spatialComponentLookupTable.at(component_id)];
        }

        SpatialComponent & GameState::getSpatialComponentWithEntityID(ID entity_id) {
            if (entityToSpatialComponentMap.count(entity_id) == 0) {
                throw std::runtime_error("Component not found");
            }
            return getSpatialComponentWithID(entityToSpatialComponentMap[entity_id]);
        }

        const SpatialComponent & GameState::getSpatialComponentWithEntityID(ID entity_id) const {
            if (entityToSpatialComponentMap.count(entity_id) == 0) {
                throw std::runtime_error("Component not found");
            }
            return getSpatialComponentWithID(entityToSpatialComponentMap.at(entity_id));
        }

        Entity & GameState::getOwnerOfSpatialComponent(ID component_id) {
            return getEntityWithID(getSpatialComponentWithID(component_id).entity_id);
        }

        const Entity & GameState::getOwnerOfSpatialComponent(ID component_id) const {
            return getEntityWithID(getSpatialComponentWithID(component_id).entity_id);
        }

        bool GameState::existsSpatialComponentWithID(ID component_id) const {
            if (spatialComponentLookupTable.count(component_id) == 0) {
                return false;
            }
            return true;
        }

        bool GameState::existsSpatialComponentWithEntityID(ID entity_id) const {
            return entityToSpatialComponentMap.count(entity_id) != 0;
        }

        void GameState::destroySpatialComponentWithID(ID component_id) {
            Index temp_index = spatialComponentLookupTable[component_id];
            SpatialComponent temp_component = spatialComponents[spatialComponents.getCount() - 1];
            spatialComponents[temp_index] = temp_component;
            spatialComponents.deleteLast();
            spatialComponentLookupTable.erase(component_id);
            spatialComponentLookupTable[temp_component.id] = temp_index;
        }

    }
}