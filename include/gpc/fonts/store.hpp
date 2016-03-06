#pragma once

#include <sstream>

#include <cereal/archives/binary.hpp>

#include "./rasterized_font.hpp"
#include "./cereal.hpp"

namespace gpc {
    
    namespace fonts {
        
        // TODO?: put this into its own header file "load.hpp" ?

        auto load(const uint8_t *data, size_t size)
        {
            rasterized_font rastfont;
            
            std::stringstream is(std::string{ reinterpret_cast<const char *>(data), size });
            cereal::BinaryInputArchive archive(is);
            archive(rastfont);
            
            return rastfont;
        }
        
    } // ns fonts
    
} // ns gpc
