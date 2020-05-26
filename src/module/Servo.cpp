#include "module/Servo.hpp"

using ServoModule = elrond::module::Servo;
using elrond::interface::ConfigMap;
using elrond::channel::RxChannel;
using elrond::LoopControl;

/*  ****************************************************************************
    ******************* elrond::module::Servo Implementation *******************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    ServoModule::~Servo(){}
#endif

void ServoModule::onInit(ConfigMap& cfg, LoopControl& lc)
{
    if(!cfg.isInt("channel")) elrond::error("Invalid or missing key \"channel\".");
    const int ch = cfg.asInt("channel");

    if(!cfg.isInt("pin")) elrond::error("Invalid or missing key \"pin\".");
    const int pin = cfg.asInt("pin");

    int chm = 0;
    if(cfg.isInt("chm")) chm = cfg.asInt("chm");

    if(cfg.isBool("inverted")) this->inverted = cfg.asBool("inverted");

    this->pin.attach(pin);

    this->ch.init(
        ch,
        chm,
        [](const elrond::word data, elrond::TaskContext* const ctx)
        {
            ServoModule* const me = (ServoModule *) ctx;
            me->pin.write(me->inverted ? elrond::high - data : data);
        },
        this
    );
}

ELROND_DEFINE_INTER_MOD(
    elrond::Servo,
    "Servo",
    "Edwino Stein",
    "edwino.stein@gmail.com"
)
