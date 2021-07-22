#include "ReflectedElement.hpp"
#include "ReflectedContainer.hpp"

#include <GaiaExceptions/GaiaExceptions.hpp>

namespace Gaia::Reflection
{
    /// Constructor which will auto register itself to the container.
    ReflectedElement::ReflectedElement(ReflectedContainer *container, const std::string &type_name)
    {
        if (container)
        {
            container->RegisterElement(this, {type_name});
            HostContainer = container;
        } else throw Exceptions::NullPointerException("Reflected Container");
    }

    /// Constructor which will auto register itself to the container.
    ReflectedElement::ReflectedElement(ReflectedContainer *container, const std::unordered_set<std::string> &type_names)
    {
        if (container)
        {
            container->RegisterElement(this, type_names);
            HostContainer = container;
        } else throw Exceptions::NullPointerException("Reflected Container");
    }
}