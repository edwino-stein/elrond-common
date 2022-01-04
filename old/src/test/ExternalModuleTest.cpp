#include "test/ExternalModuleTest.hpp"

using elrond::module::BaseExternalModuleHandle;
using elrond::test::ExternalModuleTest;
using elrond::interface::Runtime;
using elrond::interface::Module;

ExternalModuleTest::ExternalModuleTest(elrond::String path, Runtime& app):
BaseExternalModuleHandle(path, app), apiVer(apiVersion), className(mainClassName),
prettyName(_prettyName), authorName(_authorName), authorEmail(_authorEmail), version(_version)
{
    this->_prettyName = this->getMetaInfo(ELROND_TO_STR(ELROND_MOD_PRETTY_NAME_FUNC_N));
    this->_authorName = this->getMetaInfo(ELROND_TO_STR(ELROND_MOD_AUTHOR_NAME_FUNC_N));
    this->_authorEmail = this->getMetaInfo(ELROND_TO_STR(ELROND_MOD_AUTHOR_EMAIL_FUNC_N));
    this->_version = this->getMetaInfo(ELROND_TO_STR(ELROND_MOD_VERSION_FUNC_N));
    this->inst = this->newInstance();
}

ExternalModuleTest::~ExternalModuleTest()
{
    if(this->inst != nullptr){
        if(this->delInstance != nullptr) this->delInstance(this->inst);
        else delete this->inst;   
        this->inst = nullptr;
    }
}

Module& ExternalModuleTest::getInstance() const
{ return *(this->inst); }
