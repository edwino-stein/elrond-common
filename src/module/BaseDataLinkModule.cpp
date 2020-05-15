#include "module/BaseDataLinkModule.hpp"
#include "interface/ChannelManager.hpp"

/*  ****************************************************************************
    ************ elrond::module::BaseDataLinkModule Implementation *************
    ****************************************************************************/

namespace elrond {
    namespace module {

        #ifdef ELROND_WITH_DESTRUCTORS
            ELROND_INLINE_FUNC BaseDataLinkModule::~BaseDataLinkModule()
            { this->_chm_ = nullptr; }
        #endif

        ELROND_INLINE_FUNC elrond::ModuleType BaseDataLinkModule::getType() const
        { return elrond::ModuleType::DATA_LINK; }

        ELROND_INLINE_FUNC bool BaseDataLinkModule::hasCHM() const
        { return this->_chm_ != nullptr; }

        ELROND_INLINE_FUNC void BaseDataLinkModule::setCHM(
            elrond::interface::ChannelManager* const chm
        ){ if(!this->hasCHM()) this->_chm_ = chm; }

        ELROND_INLINE_FUNC elrond::interface::ChannelManager& BaseDataLinkModule::getCHM() const
        { return *(this->_chm_); }

        ELROND_INLINE_FUNC void BaseDataLinkModule::receive(
            elrond::channel::OnChmReceiveHandleT handle,
            elrond::TaskContext* const ctx
        ){ if(this->hasCHM()) this->getCHM().tryReceive(handle, ctx); }
    }
}
