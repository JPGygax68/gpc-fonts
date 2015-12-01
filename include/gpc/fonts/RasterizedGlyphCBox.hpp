#pragma once

#include "BoundingBox.hpp"

namespace gpc {

    namespace fonts {
    
        /* Rasterized Glyph Control Box
         */         
        struct RasterizedGlyphCBox: public BoundingBox {
            int adv_x, adv_y;
        };
        
    } // ns fonts
    
} // ns gpc
