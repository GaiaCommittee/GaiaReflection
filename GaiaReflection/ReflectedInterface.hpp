#pragma once

#include <functional>
#include <string>
#include <map>
#include <list>
#include <type_traits>

namespace Gaia::Reflection
{
    /**
     * @brief If a interface is derived from this class,
     *        then classes derived from it can be reflected.
     */
    class ReflectedInterface
    {
    };

    namespace ReflectedClasses
    {
        template <typename InterfaceType>
        class ReflectedInterfaceAccessor
        {
        public:
            static void RegisterDerivedClass (
                    const std::string& name, std::function<ReflectedInterface*()>& constructor)
            {
                InterfaceType::ReflectedClasses->emplace(name, constructor);
            }
        };

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
                ReflectedInterfaceAccessor<InterfaceType>::RegisterDerivedClass(
                        name, []{return new ClassType();});
            }
        };
    }
}

#ifndef REFLECT_INTERFACE
#define REFLECT_INTERFACE(InterfaceName) \
        ; \
    private: \
        static std::unordered_map<std::string, \
            std::function<Gaia::Reflection::ReflectedInterface*()>> DerivedClasses; \
    protected: \
        static const decltype(DerivedClasses)& GetDerivedClasses() {return DerivedClasses;}\
    private:
#endif

#ifndef REFLECT_DERIVED_CLASS
#define REFLECT_DERIVED_CLASS(InterfaceName, ClassName) \
    namespace GeneratedReflection::ReflectedDerivedClasses::ClassName##MetaData \
    { \
        inline const Gaia::Reflection::ReflectedClasses::ReflectedDerivedClassRegister \
            <InterfaceName, ClassName> ClassName##AutoRegister{#ClassName}; \
    }
#endif