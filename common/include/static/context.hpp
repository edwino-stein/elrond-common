#ifndef ELROND_COMMON_STATIC_CONTEXT_HPP
    #define ELROND_COMMON_STATIC_CONTEXT_HPP

    #include "elrond_common_types.hpp"

    namespace elrond
    {
        const elrond::interface::Context& ctx(const elrond::interface::Module& inst);
        const elrond::interface::Context& ctx(const elrond::interface::Module* const inst);
    }

#endif
