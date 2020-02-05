#if !defined  _ELROND_TEST_EXTERNAL_MODULE_HPP
#define _ELROND_TEST_EXTERNAL_MODULE_HPP

    #include "elrond.hpp"

    namespace elrond {
        namespace test {

            class ExternalModuleTest {

                private:
                    
                    using ModSetAppT = void (*)(ELROND_MOD_INFO_APP_P);
                    using ModNewT = ELROND_MOD_INFO_MOD_P (*)();
                    using ModDeleteT = void (*)(ELROND_MOD_INFO_MOD_P);
                    using ModStringHandleT = ELROND_MOD_INFO_STR_T (*)();
                    using ModNumHandleT = ELROND_MOD_INFO_NUM_T (*)();

                protected:
                    
                    void* dlHandle = nullptr;
                    elrond::interface::Module* inst = nullptr;
                    
                    ModNewT newInstance = nullptr;
                    ModDeleteT delInstance = nullptr;
                    
                    elrond::dWord _apiVer = 0;
                    elrond::String _className = "";
                    elrond::String _prettyName = "";
                    elrond::String _authorName = "";
                    elrond::String _authorEmail = "";
                    elrond::String _version = "";
                    
                public:

                    elrond::dWord const& apiVer;
                    elrond::String const& className;
                    elrond::String const& prettyName;
                    elrond::String const& authorName;
                    elrond::String const& authorEmail;
                    elrond::String const& version;

                    ExternalModuleTest(elrond::String path, elrond::interface::Runtime& app);
                    virtual ~ExternalModuleTest();
                    
                    elrond::interface::Module& getInstance() const;
            };
        }
    }

#endif
