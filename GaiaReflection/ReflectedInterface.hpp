#pragma once

#include <functional>
#include <string>
#include <map>
#include <list>
#include <type_traits>

namespace Gaia::Reflection
{
    class ReflectedInterface;

    namespace ReflectedClasses
    {
        /**
         * @brief Instance of the register will auto register the bound reflected derived class type
         *        into the reflected interface.
         * @attention One reflected derived class should have only one register.
         * @tparam InterfaceType Type of the reflected interface.
         * @tparam ClassType Type of the reflected derived class to register.
         */
        template <typename InterfaceType, typename ClassType,
                typename = typename std::enable_if_t<std::is_base_of_v<ReflectedInterface, InterfaceType>>,
                typename = typename std::enable_if_t<std::is_base_of_v<InterfaceType, ClassType>>>
        class ReflectedDerivedClassRegister
        {
        public:
            /// Register the bound reflected derived class.
            explicit ReflectedDerivedClassRegister(const char* name) noexcept
            {
                InterfaceType::DerivedClasses.emplace(name, []{return new ClassType();});
            }
        };
    }

    /**
     * @brief If a interface is derived from this class,
     *        then classes derived from it can be reflected.
     */
    class ReflectedInterface
    {
    public:
        /// Declare destructor virtual.
        virtual ~ReflectedInterface() = default;
    };
}

#ifndef REFLECT_INTERFACE
#define REFLECT_INTERFACE(InterfaceName) \
        template <typename, typename, typename, typename> \
        friend class Gaia::Reflection::ReflectedClasses::ReflectedDerivedClassRegister; \
    private: \
        static std::unordered_map<std::string, \
            std::function<InterfaceName*()>> DerivedClasses; \
    public: \
        static const decltype(DerivedClasses)& GetDerivedClasses() {return DerivedClasses;} \
    private:
#endif

#ifndef REFLECT_DERIVED_CLASS
#define REFLECT_DERIVED_CLASS(InterfaceName, ClassName) \
    namespace GeneratedReflection::InterfaceName##Reflections::ClassName##MetaData \
    { \
        inline const Gaia::Reflection::ReflectedClasses::ReflectedDerivedClassRegister \
            <InterfaceName, ClassName> ClassName##AutoRegister{#ClassName}; \
    }
#endif