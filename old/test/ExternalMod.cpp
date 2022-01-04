#include "elrond.hpp"

class ExternalMod : public elrond::module::BaseModule {
    protected:
        elrond::channel::RxChannel rx;
        elrond::channel::TxChannel tx;
        elrond::gpio::DOutPin pin;
        elrond::input::InputListener input;

    public:
        virtual ~ExternalMod();
        void onInit(elrond::interface::ConfigMap& cfg, elrond::LoopControl& lc) override;
        void onStart() override;
        void loop() override;
        void onStop() override;
};

ExternalMod::~ExternalMod(){}

void ExternalMod::onInit(elrond::interface::ConfigMap& cfg, elrond::LoopControl& lc)
{
    elrond::info() << "External::onInit" << elrond::endl;

    lc.enable = true;
    lc.interval = 1000;

    this->pin.attach(0);
    this->rx.init(
        0,
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { ((ExternalMod*) ctx)->pin.write(data); },
        this
    );

    this->tx.init(0, 0);
    this->input.init(
        0,
        0,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        { ((ExternalMod*) ctx)->tx.trigger(data); },
        this
    );
}

void ExternalMod::onStart()
{ elrond::info() << "External::onStart" << elrond::endl; }

void ExternalMod::loop()
{ elrond::info() << "External::loop" << elrond::endl; }

void ExternalMod::onStop()
{ elrond::info() << "External::onStop" << elrond::endl; }

ELROND_DEFINE_MODULE(ExternalMod)
ELROND_DEFINE_MODULE_PRETTY_NAME("External Module Test")
ELROND_DEFINE_MODULE_AUTHOR_NAME("Elrond Half-elven")
ELROND_DEFINE_MODULE_AUTHOR_EMAIL("elrond@rivendell.com")
ELROND_DEFINE_MODULE_VERSION(ELROND_API_VERSION_STR)
