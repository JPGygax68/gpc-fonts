#pragma once

#include <cassert>
#include <algorithm>

#include "./CharacterRange.hpp"

namespace gpc {

    namespace fonts {
    
        class CharacterSet {
        public:
            auto add(uint32_t start, uint32_t count = 1) -> CharacterSet & {
                using namespace std;
                
                // Find where to insert the new range
                auto it = begin(_ranges);
                while (it != end(_ranges) && start > (it->starting_codepoint + it->count)) it++;
                uint32_t first = it != end(_ranges) ? min(start, it->starting_codepoint) : start;

                // Find out how many of the successors the new range will replace, and what last character is
                auto it2 = it;
                while (it2 != end(_ranges) && (start + count) > it2->starting_codepoint) it2++;
                uint32_t last = it2 != end(_ranges) ? it2->starting_codepoint + it2->count : start + count;

                // Erase the successors that are no longer needed
                _ranges.erase(it, it2 != end(_ranges) ? it2 + 1 : end(_ranges));

                // Insert our new range
                _ranges.emplace_back<CharacterRange>({ first, last - first });

                return *this;
            }

            bool contains(uint32_t ch) const {
                for (const auto &range : _ranges)
                    if (range.contains(ch)) return true;
                return false;
            }

            auto ranges() const -> const std::vector<CharacterRange> & { return _ranges; }

        private:

            std::vector<CharacterRange> _ranges;
        };
        
    } // ns fonts
    
} // ns gpc 