#include "mock/ModuleInstanceHandle.hpp"

using elrond::mock::ModuleInstanceHandle;
using elrond::mock::ExternalInstanceModuleHandle;
using elrond::interface::Factory;
using elrond::interface::Module;

/*   ModuleInstanceHandle   */

ModuleInstanceHandle::ModuleInstanceHandle(const elrond::string& name)
: _name(name), _instance(nullptr), loopEnable(false), loopTs(elrond::seconds(0)) {}

elrond::string ModuleInstanceHandle::name() const
{ return this->_name; }

Module& ModuleInstanceHandle::instance() const
{ return *(this->_instance); }

/*   ExternalInstanceModuleHandle   */

ExternalInstanceModuleHandle::ExternalInstanceModuleHandle(const elrond::string& name, const elrond::string& path)
: ModuleInstanceHandle(name), _dlHandle(path), _factory(elrond::platform::parseExternalFactoryFromDlHandle(_dlHandle))
{ this->_instance = this->factory().create(); }

ExternalInstanceModuleHandle::~ExternalInstanceModuleHandle()
{ this->factory().destroy(this->_instance); }

Factory& ExternalInstanceModuleHandle::factory() const
{ return this->_factory; }
