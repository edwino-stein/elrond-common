#ifndef ELROND_COMMON_MODULE_BASE_HPP
    #define ELROND_COMMON_MODULE_BASE_HPP

    #include "module/Abstract.hpp"

    namespace elrond
    {
        namespace module
        {
            template<elrond::ModuleType M>
            class Base : public elrond::module::Abstract
            {
                public:
                    elrond::ModuleType moduleType() const override;
            };
        }
    }

#endif
