#pragma once

namespace gpc {

    namespace fonts {
    
        struct BoundingBox {
            int x_min, x_max;   // A negative x_min represents extent before origin of first glyph
            int y_min, y_max;   // "min" is the descent and (almost?) always negative, "max" is ascent
            int width() const { return x_max - x_min; }
            int height() const { return y_max - y_min; }
        };

    } // ns fonts
   
} // ns gpc
