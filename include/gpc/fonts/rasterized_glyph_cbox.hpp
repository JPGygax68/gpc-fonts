#pragma once

#include "bounding_box.hpp"

namespace gpc {

    namespace fonts {
    
        /* Rasterized Glyph Control Box
         */         
        struct rasterized_glyph_cbox {
            bounding_box bounds;
            int adv_x, adv_y;
        };
        
    } // ns fonts
    
} // ns gpc
