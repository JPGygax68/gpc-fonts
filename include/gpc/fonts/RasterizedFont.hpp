#pragma once

#include <vector>
#include <cstdint>
#include <algorithm>

#include "RasterizedGlyphCBox.hpp"
#include "CharacterRange.hpp"
#include "BoundingBox.hpp"

namespace gpc {

    namespace fonts {

        /*
            A Rasterized Font struct contains just what its name says: a set of glyphs, 
            rasterized into one or more grayscale bitmaps, plus the information needed to
            access those glyphs.

            This includes an index making it easy to find the glyph box corresponding to a given 
            Unicode code point (provided of course that code point is contained in the set).

            The struct is intended to be easy to serialize and de-serialize, containing 
            nothing but trivial or STL types.
        */

        struct RasterizedFont {
        public:

            struct GlyphRecord {
                RasterizedGlyphCBox cbox;
                size_t pixel_base;      // offset in pixel buffer where this glyph starts
            };
            
            // Contains the data specific to a given size/style combination
            struct Variant {
                std::vector<uint8_t> pixels;
                std::vector<GlyphRecord> glyphs;
            };

            std::vector<CharacterRange> index;
            std::vector<Variant>        variants;

            auto findGlyph(uint32_t cp) const -> int {

                size_t base = 0; // base glyph index for current range
                for (auto range_it = index.begin(); range_it != index.end(); base += (*range_it).count, range_it++)
                    if (cp >= (*range_it).starting_codepoint && cp < ((*range_it).starting_codepoint + (*range_it).count))
                        return base + (cp - (*range_it).starting_codepoint);
                return -1;
            }
            
            // TODO: make this capable of working with vertical scripts
            
            auto computeTextExtents(int variant, const char32_t *text, size_t count) const -> BoundingBox {

                // TODO: the implementation should be inherited from (or forwarded to) a generic routine

                int x_min = 0, x_max = 0, y_min = 0, y_max = 0;

                if (count > 0) {
                    auto &var = variants[variant];
                    auto *glyph = &var.glyphs[ findGlyph(*text) ];
                    x_min = glyph->cbox.x_min;
                    size_t i = 0;
                    int x = 0;
                    while (true) {
                        auto &cbox = glyph->cbox;
                        y_min = std::min(y_min, cbox.y_min);
                        y_max = std::max(y_max, cbox.y_max);
                        if (++i == count) break;
                        glyph = &var.glyphs[findGlyph(text[i])];
                        x += glyph->cbox.adv_x;
                    }
                    x_max = x + glyph->cbox.x_max;
                }

                return { x_min, x_max, y_min, y_max };
            }

        };

    } // ns fonts
    
} // ns gpc
