#pragma once

#include <cstdint>

namespace gpc {

    namespace fonts {
    
        struct CharacterRange {
            uint32_t	starting_codepoint;
            size_t      count;
            bool contains(uint32_t ch) const { return ch >= starting_codepoint && ch < starting_codepoint + count; }
        };
        
    } // ns fonts
    
} // ns gpc 