#pragma once

#include <vector>

#ifndef RASTERIZED_GLYPHSET_NS
#define RASTERIZED_GLYPHSET_NS gpc
#endif

namespace RASTERIZED_GLYPHSET_NS {

    /*
        A Rasterized Glyph Set struct contains just what its name says: a set of glyphs, 
        rasterized into one or more grayscale bitmaps, plus the information needed to
        access those glyphs.

        This includes an index making it easy to find the glyph box corresponding to a given 
        Unicode code point (provided of course that code point is contained in the set).

        The struct is intended to be easy to serialize and deserialize, containing 
        nothing but trivial or STL types.
    */

    struct RasterizedGlyphSet {
    public:

        typedef unsigned long   CodePoint;
        typedef unsigned long   CharCount;
        typedef unsigned int    Index;
        typedef unsigned char   Pixel;          // grayscale pixel: one unsigned byte
        typedef unsigned int    Size;
        typedef int             Offset;

        struct Bitmap {
            Size width, height;
            std::vector<Pixel> pixels;
        };

        struct GlyphInfo {
            Index bitmap_index;
            struct {
                Offset left, top;
            } position;             // position of box within bitmap
            struct {
                int width, rows;    // width and height of the rasterized glyph image
                int left, top;      // offset from origin of top-left corner (positive = right and up)
            } control_box;          // glyph control box
            struct {
                int x, y;
            } advance;
        };

        struct Range {
            CodePoint start;
            CharCount count;
        };

        std::vector<Bitmap>     bitmaps;
        std::vector<GlyphInfo>  glyphs;
        std::vector<Range>      index;

        auto findGlyph(CodePoint cp) -> GlyphInfo * {
            size_t base = 0;
            for (auto range_it = index.begin(); range_it != index.end(); base += (*range_it).count, range_it++)
                if (cp >= (*range_it).start && cp < ((*range_it).start + (*range_it).count))
                    return &glyphs[base + (cp - (*range_it).start)];
            return nullptr;
        }
    };

} // namespace
