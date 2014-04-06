/**************************************************************************************************
 * @file    ComponentManager.h
 * @date    2014-04-03
 * @brief   Manages Subclasses of Component
 * @details <#Detailed Description#>
 **************************************************************************************************/

#pragma once

#include <map>
#include <unordered_map>
#include <typeindex>
#include <functional>

#include "Component.h"

namespace evansbros {
    namespace game {
        class ComponentManager {
        public:
            /**
             * Adds a component of the parametized type.
             * @author Omar Stefan Evans
             * @date   2014-04-03, 2014-04-04
             * @param  component the component to add
             * @return the UniqueID assigned to the component
             * @post   The component has been added.
             * @see    remove
             * @see    get
             * @see    exists
             */
            template <class ComponentType>
            UniqueID add(ComponentType component) {
                component.uid = nextUID++;

                std::type_index t = std::type_index(typeid(component));
                if (componentArrays_data.count(t) == 0) {
                    const size_t initialSize = 1;
                    componentArrays_count[t] = 0;
                    componentArrays_size[t] = initialSize;
                    componentArrays_data[t] = new ComponentType[initialSize];
                }

                size_t & count = componentArrays_count[t];
                size_t & size = componentArrays_size[t];

                if (count == size) {
                    const size_t newSize = size * 2;
                    ComponentType * temp = new ComponentType[newSize];
                    for (int i = 0; i < count; ++i) {
                        temp[i] = static_cast<ComponentType *>(componentArrays_data[t])[i];
                    }
                    size = newSize;
                    delete [] componentArrays_data[t];
                    componentArrays_data[t] = temp;
                }

                componentLookupTables[t][component.uid] = count;
                static_cast<ComponentType *>(componentArrays_data[t])[count] = component;
                componentLookupTables[t][component.uid] = count;
                ++count;

                removeFunctionLookupTable[component.uid] = &ComponentManager::remove<ComponentType>;
                return component.uid;
            }


            /**
             * Counts the number of components of the parametized type.
             * @author Omar Stefan Evans
             * @date   2014-04-03
             * @return the number of components being managed
             * @see    getAll
             */
            template <class ComponentType>
            size_t count() const {
                const std::type_index t = std::type_index(typeid(ComponentType));
                if (componentArrays_data.count(t) == 0) {
                    return 0;
                }
                return componentArrays_count.at(t);
            }


            /**
             * Checks if a component of the parametized type exists with the given UniqueID.
             * @author Omar Stefan Evans
             * @date   2014-04-03
             * @param  uid a UniqueID
             * @return true if a component of the specified type exists with that UniqueID
             * @see    add
             * @see    remove
             * @see    get
             */
            template <class ComponentType>
            bool exists(UniqueID uid) const {
                const std::type_index t = std::type_index(typeid(ComponentType));
                if (componentArrays_data.count(t) == 0) {
                    return false;
                }
                return componentLookupTables.at(t).count(uid) != 0;
            }


            /**
             * Gets the component of the parametized type with the given UniqueID.
             * @author  Omar Stefan Evans
             * @date    2014-04-03
             * @param   uid a UniqueID
             * @pre     The component must exist; otherwise, an exception is thrown.
             * @return  the specified component by reference
             * @remarks std::runtime_error is thrown if the component does not exist.
             * @see     add
             * @see     remove
             * @see     exists
             */
            template <class ComponentType>
            ComponentType & get(UniqueID uid) {
                if (!exists<ComponentType>(uid)) {
                    throw std::runtime_error("The specified component could not be found.");
                }
                const std::type_index t = std::type_index(typeid(ComponentType));
                const Index i = componentLookupTables[t][uid];
                return static_cast<ComponentType *>(componentArrays_data[t])[i];
            }


            /**
             * Gets the component of the parametized type with the given UniqueID.
             * @author  Omar Stefan Evans
             * @date    2014-04-03
             * @param   uid a UniqueID
             * @pre     The component must exist; otherwise, an exception is thrown.
             * @return  the specified component by reference (const)
             * @remarks std::runtime_error is thrown if the component does not exist.
             * @see     add
             * @see     remove
             * @see     exists
             */
            template <class ComponentType>
            const ComponentType & get(UniqueID uid) const {
                if (!exists<ComponentType>(uid)) {
                    throw std::runtime_error("The specified component could not be found.");
                }
                const std::type_index t = std::type_index(typeid(ComponentType));
                const Index i = componentLookupTables.at(t).at(uid);
                return static_cast<ComponentType *>(componentArrays_data.at(t))[i];
            }


            /**
             * Enables access to the array of components of the parametized type.
             * @author Omar Stefan Evans
             * @date   2014-04-04
             * @return a pointer to the first component, or nullptr if no such array exists
             * @see    count
             */
            template <class ComponentType>
            ComponentType * getAll() {
                const std::type_index t = std::type_index(typeid(ComponentType));
                if (componentArrays_data.count(t) == 0) {
                    return nullptr;
                }
                return static_cast<ComponentType *>(componentArrays_data[t]);
            }


            /**
             * Enables access to the array of components of the parametized type.
             * @author Omar Stefan Evans
             * @date   2014-04-04
             * @return a pointer to the first component (const), or nullptr if no such array exists
             * @see    count
             */
            template <class ComponentType>
            const ComponentType * getAll() const {
                const std::type_index t = std::type_index(typeid(ComponentType));
                if (componentArrays_data.count(t) == 0) {
                    return nullptr;
                }
                return static_cast<ComponentType *>(componentArrays_data.at(t));
            }


            /**
             * Removes the component of the parametized type with the given UniqueID.
             * @author  Omar Stefan Evans
             * @date    2014-04-04
             * @param   uid a UniqueID
             * @pre     The component must exist.
             * @post    The component has been removed.
             * @remarks std::runtime_error is thrown if the component does not exist.
             * @see     add
             * @see     exists
             * @see     get
             * @see     removeComponent
             */
            template <class ComponentType>
            void remove(UniqueID uid) {
                if (!exists<ComponentType>(uid)) {
                    throw std::runtime_error("The specified component could not be found.");
                }
                const std::type_index t = std::type_index(typeid(ComponentType));

                const Index lastIndex = --componentArrays_count[t];
                const ComponentType & lastComponent = static_cast<ComponentType *>(componentArrays_data[t])[lastIndex];

                const Index thisIndex = componentLookupTables[t][uid];
                ComponentType & thisComponent = static_cast<ComponentType *>(componentArrays_data[t])[thisIndex];

                thisComponent = lastComponent;

                componentLookupTables[t][lastComponent.uid] = thisIndex;
                componentLookupTables[t].erase(uid);
                removeFunctionLookupTable.erase(uid);
            }


            /**
             * Removes the component with the given UniqueID.
             * @author  Omar Stefan Evans
             * @date    2014-04-04
             * @param   uid a UniqueID
             * @pre     The component must exist.
             * @post    The component has been removed.
             * @remarks std::runtime_error is thrown if the component does not exist.
             * @see     add
             * @see     exists
             * @see     get
             * @see     remove
             */
            void removeComponent(UniqueID uid);

            
        private:
            static UniqueID nextUID;

            std::map<std::type_index, size_t> componentArrays_count;
            std::map<std::type_index, size_t> componentArrays_size;
            std::map<std::type_index, Component *> componentArrays_data;

            std::map<std::type_index, std::unordered_map<UniqueID, Index>> componentLookupTables;
            std::unordered_map<UniqueID, std::function<void(ComponentManager *, UniqueID)>> removeFunctionLookupTable;
        };
    }
}