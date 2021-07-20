#pragma once

#include <string>
#include "ReflectedContainer.hpp"

namespace Gaia::Reflection
{
    class ReflectedContainer;

    /**
     * @brief The interface which will auto register itself into the container.
     */
    class ReflectedElement
    {
    private:
        /// The container which this element is registered into.
        ReflectedContainer* HostContainer {nullptr};

    protected:
        /// Default constructor for none reflection situation.
        ReflectedElement() = default;

        /**
         * @brief Constructor which will auto register itself to the container.
         * @param type_name Type name of this element for container to categorize elements.
         * @param container Pointer to the container to found this element.
         * @details
         *  This constructor should be invoked by derived class constructors, and parameters should be
         *  passed from there.
         */
        ReflectedElement(const std::string& type_name, ReflectedContainer* container);

        /**
         * @brief Constructor which will auto register itself to the container.
         * @param type_name Type names of this element for container to categorize elements.
         * @param container Pointer to the container to found this element.
         * @details
         *  This constructor should be invoked by derived class constructors, and parameters should be
         *  passed from there.
         */
        ReflectedElement(const std::initializer_list<std::string>& type_names, ReflectedContainer* container);

        /**
         * @brief Get the host reflected container which this element is registered into.
         * @return Pointer to the host reflected container, or null if this element has not been registered.
         */
        [[nodiscard]] inline ReflectedContainer* GetHostContainer() const noexcept
        {
            return HostContainer;
        }

    public:
        /// Declare destructor virtual.
        virtual ~ReflectedElement() = default;
    };
}