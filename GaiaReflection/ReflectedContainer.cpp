#include "ReflectedContainer.hpp"

namespace Gaia::Reflection
{
    /// Get registered reflected elements of a certain type.
    const std::list<ReflectedElement*>& ReflectedContainer::GetReflectedElements(const std::string &type_name)
    {
        static const std::list<ReflectedElement*> empty_elements_list;

        auto category_finder = ElementsMap.find(type_name);
        if (category_finder != ElementsMap.end())
        {
            return category_finder->second;
        }
        return empty_elements_list;
    }

    /// Register a reflected element into this container.
    void ReflectedContainer::RegisterElement(const std::unordered_set<std::string> &type_names, ReflectedElement *element)
    {
        for (const auto& type_name : type_names)
        {
            auto category_finder = ElementsMap.find(type_name);
            if (category_finder == ElementsMap.end())
            {
                category_finder = ElementsMap.emplace(type_name, std::list<ReflectedElement*>());
            }
            category_finder->second.emplace_back(element);
        }
        ElementsSet.emplace(element);
    }

    /// Get registered reflected elements of all types.
    const std::unordered_set<ReflectedElement *> &ReflectedContainer::GetReflectedElements()
    {
        return ElementsSet;
    }
}