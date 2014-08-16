#pragma once

#include <cassert>

#include "./CharacterRange.hpp"

namespace gpc {

    namespace fonts {
    
        class CharacterSet {
        public:
            auto add(uint32_t ch) -> CharacterSet & {
                _ranges.emplace_back<CharacterRange>({ ch, 1 });
                collate();
                return *this;
            }

            bool contains(uint32_t ch) const {
                for (const auto &range : _ranges)
                    if (range.contains(ch)) return true;
                return false;
            }

            auto ranges() const -> const std::vector<CharacterRange> & { return _ranges; }

        private:

            void collate() {
                assert(!_ranges.empty());
                size_t i = 0;
                while (i < _ranges.size()) {
                    auto &current = _ranges[i];
                    while ((i + 1) < _ranges.size()) {
                        auto &succ = _ranges[i + 1];
                        if (succ.starting_codepoint == current.starting_codepoint + current.count) {
                            current.count += succ.count;
                            _ranges.erase(_ranges.begin() + i + 1);
                        }
                        else break;
                    }
                    i++;
                }
            }

            std::vector<CharacterRange> _ranges;
        };
        
    } // ns fonts
    
} // ns gpc 