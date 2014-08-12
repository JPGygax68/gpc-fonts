#pragma once

namespace gpc {

    namespace fonts {
    
        /* Rasterized Glyph Control Box
         */         
        struct RasterizedGlyphCBox {
            int x_min, x_max;
            int y_min, y_max;
            int adv_x, adv_y;
            int width() const { return x_max - x_min; }
            int height() const { return y_max - y_min; }
        };
        
    } // ns fonts
    
} // ns gpc
