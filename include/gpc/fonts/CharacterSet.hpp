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
                
                // After last current range ?
                if (it == end(_ranges)) {
                    _ranges.emplace_back<CharacterRange>({start, count});
                }
                // No: beginning before or inside an existing range, or appending to one
                else {
                    uint32_t first = min(it->starting_codepoint, start);

                    // Find last of the successors we'll replace
                    auto it2 = it;
                    for (auto itn = it2; ++itn != end(_ranges) && (start + count) >= itn->starting_codepoint; it2 = itn);

                    // Compute last (+1: non-inclusive) character in new range
                    uint32_t last = max(start + count, it2->starting_codepoint + it2->count);

                    // Erase the ranges we're replacing
                    _ranges.erase(it, it2 + 1);

                    // Insert our new range
                    _ranges.emplace_back<CharacterRange>({ first, last - first });
                }

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