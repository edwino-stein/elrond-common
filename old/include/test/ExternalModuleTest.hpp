#if !defined  _ELROND_TEST_EXTERNAL_MODULE_HPP
#define _ELROND_TEST_EXTERNAL_MODULE_HPP

    #include "elrond_test_types.hpp"

    namespace elrond {
        namespace test {

            class ExternalModuleTest: public elrond::module::BaseExternalModuleHandle {

                protected:

                    elrond::interface::Module* inst = nullptr;
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
