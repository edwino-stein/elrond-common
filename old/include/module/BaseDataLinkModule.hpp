#if !defined  _ELROND_BASE_DATA_LINK_MODULE_HPP
    #define _ELROND_BASE_DATA_LINK_MODULE_HPP

    #include "module/BaseModule.hpp"

    namespace elrond {
        namespace module {

            class BaseDataLinkModule : public elrond::module::BaseModule {

                private:
                    elrond::interface::ChannelManager* _chm_ = nullptr;

                public:

                    #ifdef ELROND_WITH_DESTRUCTORS
                        virtual ~BaseDataLinkModule();
                    #endif

                    elrond::ModuleType getType() const override;

                    bool hasCHM() const;
                    void setCHM(elrond::interface::ChannelManager* const chm);
                    elrond::interface::ChannelManager& getCHM() const;

                    virtual void receive(elrond::channel::OnChmReceiveHandleT handle,
                                         elrond::TaskContext* const ctx = nullptr);

                    virtual bool send(elrond::byte data[], const elrond::sizeT length)=0;
            };
        }
    }

#endif
