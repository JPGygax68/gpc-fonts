#pragma once

#include <sstream>
#include <map>

#include <cereal/archives/binary.hpp>

#include "./rasterized_font.hpp"
#include "./cereal.hpp"

namespace gpc {
    
    namespace fonts {
        
        // TODO?: put this into its own header file "load.hpp" ?

        inline auto load(const uint8_t *data, size_t size)
        {
            rasterized_font rastfont;
            
            std::stringstream is(std::string{ reinterpret_cast<const char *>(data), size });
            cereal::BinaryInputArchive archive(is);
            archive(rastfont);
            
            return rastfont;
        }

        inline auto get(const uint8_t *data, size_t size) -> rasterized_font *
        {
            static std::map<const uint8_t *, std::unique_ptr<rasterized_font>> map;

            return map.emplace(data, std::make_unique<rasterized_font>(load(data, size))).first->second.get();
        }

    } // ns fonts
    
} // ns gpc
