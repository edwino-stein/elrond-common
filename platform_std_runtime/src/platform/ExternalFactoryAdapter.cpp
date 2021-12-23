#include "platform/ExternalFactoryAdapter.hpp"

using elrond::platform::ExternalFactoryAdapter;
using elrond::platform::FactoryInterface;

ExternalFactoryAdapter::ExternalFactoryAdapter(const std::string& path)
:
    _handle(path),
    _factory(nullptr)
{
    try
    {
        GetApiVerH getApiVer = this->_handle.getFunctionPtr<GetApiVerP>(GetApiVerName);
        GetFactoryH getFactory = this->_handle.getFunctionPtr<GetFactoryP>(GetFactoryName);

        const elrond::byte majorVer = elrond::lowByteHighWord(getApiVer());
        const elrond::byte buildType = elrond::BUILD_TYPE & 0xF0;

        if(buildType == ELROND_BUILD_Release && majorVer != elrond::MAJOR_VER)
        {
            throw std::runtime_error("Invalid module version");
        }

        this->_factory = getFactory();
        if (this->_factory == nullptr) throw std::runtime_error("Invalid module factory");
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error(std::string("Unable to load elrond module: ") + e.what()); 
    }
}

const FactoryInterface& ExternalFactoryAdapter::factory() const
{
    return *(this->_factory);
}
