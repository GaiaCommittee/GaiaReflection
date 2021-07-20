#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>

namespace Gaia::Reflection
{
    class ReflectedElement;

    /**
     * @brief A base class which provide reflected elements auto register support.
     */
    class ReflectedContainer
    {
        friend class ReflectedElement;

    private:
        /// All registered elements.
        std::unordered_set<ReflectedElement*> ElementsSet;

        /// Registered elements.
        std::unordered_multimap<std::string, std::list<ReflectedElement*>> ElementsMap;

        /**
         * @brief Register a reflected element into this container.
         * @param type_name Type names of the element to register.
         * @param element Pointer to the element.
         */
        void RegisterElement(const std::unordered_set<std::string> &type_names, ReflectedElement* element);

    protected:
        /**
         * @brief Get registered reflected elements with a certain type.
         * @param type_name Name of the type to get.
         * @return
         *  List of reflected elements with the give name, or an empty list if category of the given name
         *  does not exist.
         */
        const std::list<ReflectedElement*>& GetReflectedElements(const std::string& type_name);

        /**
         * @brief Get registered reflected elements of all types.
         * @return
         *  List of reflected elements with the give name, or an empty list if no element has been
         *  registered into this container.
         */
        const std::unordered_set<ReflectedElement*>& GetReflectedElements();

    public:
        /// Declare destructor virtual.
        virtual ~ReflectedContainer() = default;
    };
}