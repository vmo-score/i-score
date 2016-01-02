#pragma once
#include <Process/Process.hpp>

template<typename Model_T, typename System_T, typename Component_T>
class GenericComponentFactory;

template<typename Model_T, typename System_T, typename Component_T>
using ComponentFactoryKey =  StringKey<GenericComponentFactory<Model_T, System_T, Component_T>>;

template<
        typename Model_T, // e.g. ProcessModel - maybe ProcessEntity ?
        typename System_T, // e.g. LocalTree::DocumentPlugin
        typename Component_T> // e.g. ProcessComponent
class GenericComponentFactory :
        public iscore::GenericFactoryInterface<ComponentFactoryKey<Model_T, System_T, Component_T>>
{
    public:
        using factory_key_type = ComponentFactoryKey<Model_T, System_T, Component_T>;

        static const iscore::FactoryBaseKey& staticFactoryKey() {
            static const iscore::FactoryBaseKey s{
                "ComponentFactory<" +
                System_T::className +
                Component_T::className + ">"
            };
            return s;
        }

        const iscore::FactoryBaseKey& factoryKey() const final override {
            return staticFactoryKey();
        }

        virtual bool matches(
                Model_T&,
                const System_T&,
                const iscore::DocumentContext&) const = 0;
};


template<
        typename Model_T, // e.g. ProcessModel - maybe ProcessEntity ?
        typename System_T, // e.g. LocalTree::DocumentPlugin
        typename Component_T, // e.g. ProcessComponent
        typename Factory_T> // e.g. ProcessComponentFactoryList
class GenericComponentFactoryList final :
        public iscore::FactoryListInterface
{
        std::vector<std::unique_ptr<Factory_T>> m_list;

    public:
        using factory_t = Factory_T;
        static const iscore::FactoryBaseKey& staticFactoryKey() {
            return Factory_T::staticFactoryKey();
        }

        iscore::FactoryBaseKey name() const final override {
            return Factory_T::staticFactoryKey();
        }

        void insert(std::unique_ptr<iscore::FactoryInterfaceBase> e) final override
        {
            if(auto pf = dynamic_unique_ptr_cast<Factory_T>(std::move(e)))
                m_list.push_back(std::move(pf));
        }

        const auto& list() const
        { return m_list; }

        Factory_T* factory(
                Model_T& model,
                const System_T& doc,
                const iscore::DocumentContext& ctx) const
        {
            for(auto& factory : list())
            {
                if(factory->matches(model, doc, ctx))
                {
                    return factory.get();
                }
            }

            return nullptr;
        }
};