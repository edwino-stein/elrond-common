#ifndef ELROND_COMMON_STATIC_CONTEXT_HPP
    #define ELROND_COMMON_STATIC_CONTEXT_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        elrond::pointer<elrond::interface::Context>
        ctx(const elrond::interface::Module& inst);

        elrond::pointer<elrond::interface::Context>
        ctx(const elrond::interface::Module* const inst);
    }

#endif
