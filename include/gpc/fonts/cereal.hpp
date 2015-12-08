#pragma once

#include <cereal/types/vector.hpp>

#include "./rasterized_font.hpp"

namespace cereal {

	template <class Archive>
	void serialize(Archive & archive, gpc::fonts::character_range &range)
	{
		archive(range.starting_codepoint, range.count);
	}

	template <class Archive>
	void serialize(Archive & archive, gpc::fonts::rasterized_font::glyph_record &glrec)
	{
		archive(glrec.cbox, glrec.pixel_base);
	}

	template <class Archive>
	void serialize(Archive & archive, gpc::fonts::rasterized_font::variant &var)
	{
		archive(var.glyphs, var.pixels);
	}

	template <class Archive>
	void serialize(Archive & archive, gpc::fonts::rasterized_glyph_cbox &cbox)
	{
		archive(cbox.x_min, cbox.x_max, cbox.y_min, cbox.y_max, cbox.adv_x, cbox.adv_y);
	}

	template <class Archive>
	void serialize(Archive & archive, gpc::fonts::rasterized_font &rfont)
	{
		archive(rfont.index, rfont.variants);
	}

} // ns cereal