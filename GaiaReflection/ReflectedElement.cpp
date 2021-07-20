#include "ReflectedElement.hpp"
#include "ReflectedContainer.hpp"

#include <GaiaExceptions/GaiaExceptions.hpp>

namespace Gaia::Reflection
{
    /// Constructor which will auto register itself to the container.
    ReflectedElement::ReflectedElement(const std::string &type_name, ReflectedContainer *container)
    {
        if (container)
        {
            container->RegisterElement({type_name}, this);
        } else throw Exceptions::NullPointerException("Reflected Container");
    }

    /// Constructor which will auto register itself to the container.
    ReflectedElement::ReflectedElement(const std::initializer_list<std::string> &type_names,
                                       ReflectedContainer *container)
    {
        if (container)
        {
            container->RegisterElement(type_names, this);
        } else throw Exceptions::NullPointerException("Reflected Container");
    }
}