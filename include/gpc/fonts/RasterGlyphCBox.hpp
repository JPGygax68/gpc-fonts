#pragma once

namespace gpc {

    namespace fonts {
    
        /* Rasterized Glyph Control Box
         */         
        struct RasterGlyphCBox {
            int width, rows;        // width and height of the rasterized glyph image
            int left, top;          // offset from origin of top-left corner (positive = right and up)
            int adv_x, adv_y;       // advance
        };
        
    } // ns fonts
    
} // ns gpc
