#pragma once

#include <cereal/types/vector.hpp>

#include "./RasterizedFont.hpp"

namespace cereal {

	template <class Archive>
	void serialize(Archive & archive, gpc::fonts::GlyphRange &range)
	{
		archive(range.starting_codepoint, range.count);
	}

	template <class Archive>
	void serialize(Archive & archive, gpc::fonts::RasterizedFont::GlyphRecord &glrec)
	{
		archive(glrec.cbox, glrec.pixel_base);
	}

	template <class Archive>
	void serialize(Archive & archive, gpc::fonts::RasterizedFont::Variant &var)
	{
		archive(var.glyphs, var.pixels);
	}

	template <class Archive>
	void serialize(Archive & archive, gpc::fonts::RasterizedGlyphCBox &cbox)
	{
		archive(cbox.x_min, cbox.x_max, cbox.y_min, cbox.y_max, cbox.adv_x, cbox.adv_y);
	}

	template <class Archive>
	void serialize(Archive & archive, gpc::fonts::RasterizedFont &rfont)
	{
		archive(rfont.index, rfont.variants);
	}

} // ns cereal