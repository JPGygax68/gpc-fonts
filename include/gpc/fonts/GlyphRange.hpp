#pragma once

#include <cstdint>

namespace gpc {

    namespace fonts {
    
        struct GlyphRange {
            uint32_t	starting_codepoint;
            size_t      count;
        };
        
    } // ns fonts
    
} // ns gpc 