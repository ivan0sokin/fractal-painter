#ifndef _PATTERN_PARSER_HPP
#define _PATTERN_PARSER_HPP

#include <string_view>
#include <vector>
#include <stdexcept>
#include <sstream>

#include "Rule.hpp"

class PatternParser {
public:
    constexpr PatternParser() noexcept = default;
    constexpr PatternParser(std::string_view pattern) noexcept : pattern(pattern) {}

    inline std::vector<Rule> Parse() {
        if (pattern.empty()) throw std::invalid_argument("Pattern must have at least 1 character");

        auto parsed = std::vector<Rule>();
        parsed.reserve(pattern.size());
        for (char c : pattern) {
            switch (c)
            {
            case 'F':
                parsed.emplace_back(Rule::Forward);
                break;
            case '+':
                parsed.emplace_back(Rule::Plus);
                break;
            case '-':
                parsed.emplace_back(Rule::Minus);
                break;
            case '[':
                parsed.emplace_back(Rule::Save);
                break;
            case ']':
                parsed.emplace_back(Rule::Restore);
                break;            
            default:
                std::stringstream ss;
                ss << "Character " << c << " does not match any pattern";
                throw std::invalid_argument(ss.str()); 
            }
        }

        return parsed;
    }
private:
    std::string_view pattern;
};

#endif