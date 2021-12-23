#include "test/InputTest.hpp"
#include "test/InputTriggerTest.hpp"

using elrond::test::InputTest;
using elrond::input::InputListener;
using elrond::test::InputTriggerTest;

void InputTest::addInputListener(const elrond::sizeT key, InputListener* listener)
{
    auto it = this->inputMap.find(key);
    if(it == this->inputMap.end()){
        this->inputMap[key] = InputListenerCollectionP(new InputListenerCollection);
    }

    this->inputMap[key]->push_back(listener);
}

void InputTest::triggerInput(InputTriggerTest* trigger, const elrond::word data)
{
    auto it = this->inputMap.find(trigger->key());
    if(it == this->inputMap.end()) return;

    std::for_each(
        it->second->begin(),
        it->second->end(),
        [&data](InputListener* l)
        { l->trigger(data); }
    );
}
