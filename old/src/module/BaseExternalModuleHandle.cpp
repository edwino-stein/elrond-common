#include "module/BaseExternalModuleHandle.hpp"

#ifdef LINUX_PLATFORM
    #include <dlfcn.h>
#endif

using elrond::module::BaseExternalModuleHandle;
using elrond::interface::Runtime;
using elrond::interface::Module;

/*  ****************************************************************************
    ****************** elrond DL wrapper functions definition ******************
    ****************************************************************************/
namespace elrond {

    BaseExternalModuleHandle::ModBaseHandleT loadModule(elrond::String path);
    void unloadModule(BaseExternalModuleHandle::ModBaseHandleT handle);

    template <class T>
    T getSymbol(BaseExternalModuleHandle::ModBaseHandleT handle,
                elrond::String symbol, const bool req);

    elrond::String getFileExt(elrond::String path);
}


/*  ****************************************************************************
    ********** elrond::module::BaseExternalModuleHandle Implementation *********
    ****************************************************************************/

BaseExternalModuleHandle::BaseExternalModuleHandle(elrond::String path, Runtime& app)
{
    try{

        this->baseHandle = elrond::loadModule(path);

        this->newInstance = elrond::getSymbol<ModNewT>(
            this->baseHandle,
            ELROND_TO_STR(ELROND_MOD_NEW_INST_FUNC_N),
            true
        );

        this->delInstance = elrond::getSymbol<ModDeleteT>(
            this->baseHandle,
            ELROND_TO_STR(ELROND_MOD_DEL_INST_FUNC_N),
            true
        );

        ModSetAppT setAppInstance = elrond::getSymbol<ModSetAppT>(
            this->baseHandle,
            ELROND_TO_STR(ELROND_MOD_SET_APP_FUNC_N),
            true
        );

        ModIntHandleT getApiVersion = elrond::getSymbol<ModIntHandleT>(
            this->baseHandle,
            ELROND_TO_STR(ELROND_MOD_API_VER_FUNC_N),
            true
        );

        ModStringHandleT getMainClass = elrond::getSymbol<ModStringHandleT>(
            this->baseHandle,
            ELROND_TO_STR(ELROND_MOD_MAIN_CLASS_FUNC_N),
            true
        );

        setAppInstance(&app);
        this->apiVersion = getApiVersion();
        this->mainClassName = getMainClass();

    }
    catch(elrond::String e){
        throw "Unable to load the module from \"" + path + "\": \"" + e + "\"";
    }
}

BaseExternalModuleHandle::~BaseExternalModuleHandle()
{
    this->newInstance = nullptr;
    this->delInstance = nullptr;

    if(this->baseHandle != nullptr){
        elrond::unloadModule(this->baseHandle);
        this->baseHandle = nullptr;
    }
}

elrond::String BaseExternalModuleHandle::getMetaInfo(elrond::String symbol) const
{
    if(this->baseHandle != nullptr){

        ModStringHandleT funcHandle = elrond::getSymbol<ModStringHandleT>(
            this->baseHandle,
            symbol,
            false
        );

        if(funcHandle != nullptr) return funcHandle();
    }

    return "";
}

/*  ****************************************************************************
    **************** elrond DL wrapper functions implementation ****************
    ****************************************************************************/
#ifdef LINUX_PLATFORM

    BaseExternalModuleHandle::ModBaseHandleT elrond::loadModule(elrond::String path)
    {
        if(path[0] != '/' && path[0] != '.') path = "./"+path;
        if(elrond::getFileExt(path) != "so") path += ".so";

        BaseExternalModuleHandle::ModBaseHandleT handle = ::dlopen(
            path.c_str(),
            RTLD_NOW | RTLD_GLOBAL
        );

        if(!handle) throw elrond::String(dlerror());
        return handle;
    }

    void elrond::unloadModule(BaseExternalModuleHandle::ModBaseHandleT handle)
    { ::dlclose(handle); }

    template <class T>
    T elrond::getSymbol(BaseExternalModuleHandle::ModBaseHandleT handle,
                        elrond::String symbol, const bool req)
    {
        T sym = (T) ::dlsym(handle, symbol.c_str());
        if((sym == nullptr) && req) throw elrond::String(dlerror());
        return sym;
    }

#endif

elrond::String elrond::getFileExt(elrond::String path)
{
    elrond::sizeT i = path.rfind('.', path.length());
    if (i != std::string::npos) return path.substr(i + 1, path.length() - i);
    return "";
}
