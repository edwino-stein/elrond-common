#if !defined  _ELROND_BASE_EXTERNAL_MODULE_HANDLE_HPP
    #define _ELROND_BASE_EXTERNAL_MODULE_HANDLE_HPP

    #include "elrond_ext_types.hpp"

    namespace elrond {
        namespace module {

            class BaseExternalModuleHandle {

                public:

                    #ifdef LINUX_PLATFORM
                        using ModSetAppT = void (*)(ELROND_MOD_INFO_APP_P);
                        using ModNewT = ELROND_MOD_INFO_MOD_P (*)();
                        using ModDeleteT = void (*)(ELROND_MOD_INFO_MOD_P);
                        using ModStringHandleT = ELROND_MOD_INFO_STR_T (*)();
                        using ModIntHandleT = ELROND_MOD_INFO_NUM_T (*)();
                        using ModBaseHandleT = void*;
                    #endif

                    BaseExternalModuleHandle(elrond::String path, elrond::interface::Runtime& app);
                    virtual ~BaseExternalModuleHandle();

                protected:

                    ModBaseHandleT baseHandle = nullptr;
                    ModNewT newInstance = nullptr;
                    ModDeleteT delInstance = nullptr;
                    elrond::dWord apiVersion = 0;
                    elrond::String mainClassName = "";

                    elrond::String getMetaInfo(elrond::String symbol) const;
            };
        }
    }

#endif
