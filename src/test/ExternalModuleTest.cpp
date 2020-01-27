#include "test/ExternalModuleTest.hpp"

#include <dlfcn.h>

using elrond::test::ExternalModuleTest;
using elrond::interface::Runtime;
using elrond::interface::Module;

ExternalModuleTest::ExternalModuleTest(elrond::String path, elrond::interface::Runtime& app):
apiVer(_apiVer), className(_className), prettyName(_prettyName),
authorName(_authorName), authorEmail(_authorEmail), version(_version)
{
    this->dlHandle = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if(!this->dlHandle) throw dlerror();

    ModSetAppT setAppInstance = (ModSetAppT) dlsym(
        this->dlHandle,
        ELROND_TO_STR(ELROND_MOD_SET_APP_FUNC_N)
    );
    if(setAppInstance == nullptr) throw dlerror();

    this->newInstance = (ModNewT) dlsym(
        this->dlHandle,
        ELROND_TO_STR(ELROND_MOD_NEW_INST_FUNC_N)
    );
    if(this->newInstance == nullptr) throw dlerror();

    this->delInstance = (ModDeleteT) dlsym(
        this->dlHandle,
        ELROND_TO_STR(ELROND_MOD_DEL_INST_FUNC_N)
    );
    if(this->delInstance == nullptr) throw dlerror();

    ModNumHandleT getApiVersion = (ModNumHandleT) dlsym(
        this->dlHandle,
        ELROND_TO_STR(ELROND_MOD_API_VER_FUNC_N)
    );
    if(getApiVersion == nullptr) throw dlerror();

    ModStringHandleT getMainClass = (ModStringHandleT) dlsym(
        this->dlHandle,
        ELROND_TO_STR(ELROND_MOD_MAIN_CLASS_FUNC_N)
    );
    if(getMainClass == nullptr) throw dlerror();

    setAppInstance(&app);
    this->inst = this->newInstance();
    this->_apiVer = getApiVersion();
    this->_className = getMainClass();

    ModStringHandleT getPrettyName = (ModStringHandleT) dlsym(
        this->dlHandle,
        ELROND_TO_STR(ELROND_MOD_PRETTY_NAME_FUNC_N)
    );

    ModStringHandleT getAuthorName = (ModStringHandleT) dlsym(
        this->dlHandle,
        ELROND_TO_STR(ELROND_MOD_AUTHOR_NAME_FUNC_N)
    );

    ModStringHandleT getAuthorEmail = (ModStringHandleT) dlsym(
        this->dlHandle,
        ELROND_TO_STR(ELROND_MOD_AUTHOR_EMAIL_FUNC_N)
    );

    ModStringHandleT getVersion = (ModStringHandleT) dlsym(
        this->dlHandle,
        ELROND_TO_STR(ELROND_MOD_VERSION_FUNC_N)
    );

    if(getPrettyName != nullptr) this->_prettyName = getPrettyName();
    if(getAuthorName != nullptr) this->_authorName = getAuthorName();
    if(getAuthorEmail != nullptr) this->_authorEmail = getAuthorEmail();
    if(getVersion != nullptr) this->_version = getVersion();
}

ExternalModuleTest::~ExternalModuleTest()
{
    if(this->delInstance != nullptr){
        if(this->inst != nullptr) this->delInstance(this->inst);
    }

    this->newInstance = nullptr;
    this->delInstance = nullptr;
    this->inst = nullptr;

    if(this->dlHandle != nullptr){
        dlclose(this->dlHandle);
        this->dlHandle = nullptr;
    }
}

Module& ExternalModuleTest::getInstance() const
{ return *(this->inst); }
