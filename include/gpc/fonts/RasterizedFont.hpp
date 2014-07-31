#pragma once

#include <vector>
#include <cstdint>

#include "RasterizedGlyphCBox.hpp"
#include "GlyphRange.hpp"

namespace gpc {

    namespace fonts {

        /*
            A Rasterized Glyph Set struct contains just what its name says: a set of glyphs, 
            rasterized into one or more grayscale bitmaps, plus the information needed to
            access those glyphs.

            This includes an index making it easy to find the glyph box corresponding to a given 
            Unicode code point (provided of course that code point is contained in the set).

            The struct is intended to be easy to serialize and deserialize, containing 
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

            std::vector<GlyphRange> index;
            std::vector<Variant>    variants;

			/* Re-code (if needed) to account for font variants
            auto findGlyph(uint32_t cp) -> GlyphRecord * {
                size_t base = 0; // base glyph index for current range
                for (auto range_it = index.begin(); range_it != index.end(); base += (*range_it).count, range_it++)
                    if (cp >= (*range_it).starting_codepoint && cp < ((*range_it).starting_codepoint + (*range_it).count))
                        return &glyphs[base + (cp - (*range_it).starting_codepoint)];
                return nullptr;
            }
			*/
        };

    } // ns fonts
    
} // ns gpc
