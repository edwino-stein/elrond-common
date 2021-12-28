#include "module/Loopback.hpp"
#include "channel/BufferWrapper.hpp"

using elrond::module::Loopback;
using elrond::interface::Module;
using elrond::interface::Runtime;
using elrond::interface::ConfigMap;
using elrond::interface::ChannelManager;
using elrond::LoopControl;
using elrond::channel::BufferWrapper;

/*  ****************************************************************************
    ****************** elrond::module::Loopback Implementation *****************
    ****************************************************************************/

#ifdef ELROND_WITH_DESTRUCTORS
    Loopback::~Loopback(){}
#endif

bool Loopback::send(elrond::byte data[], const elrond::sizeT length)
{
    BufferWrapper txBuffer(data, length);

    this->receive(
        [](
            elrond::byte rxBuf[],
            const elrond::sizeT rxLen, elrond::TaskContext* const ctx
        )
        {
            BufferWrapper* const txb = (BufferWrapper* const) ctx;
            if(rxLen != txb->length) return (elrond::sizeT) 0;
            for(elrond::sizeT i = 0; i < rxLen; ++i) rxBuf[i] = txb->data[i];
            return rxLen;
        },
        &txBuffer
    );

    return true;
}

ELROND_DEFINE_INTER_MOD(
    elrond::Loopback,
    "Loopback Transport",
    "Edwino Stein",
    "edwino.stein@gmail.com"
)
