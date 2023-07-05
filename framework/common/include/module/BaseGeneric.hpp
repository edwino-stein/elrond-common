#ifndef ELROND_COMMON_MODULE_BASE_GENERIC_HPP
    #define ELROND_COMMON_MODULE_BASE_GENERIC_HPP

    #include "module/Base.ipp"

    namespace elrond
    {
        namespace module
        {
            class BaseGeneric : public elrond::module::Base<elrond::ModuleType::GENERIC>
            {
                public:
                    ELROND_DEFAULT_CLASS_SPECIAL_MEMBERS(BaseGeneric)
            };
        }
    }

#endif
