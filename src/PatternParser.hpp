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

    inline std::vector<Rule> TryParse() const {
        if (pattern.empty()) throw std::invalid_argument("Pattern must have at least 1 character");

        auto parsed = std::vector<Rule>();
        parsed.reserve(pattern.size());
        
        for (char c : pattern)
            parsed.emplace_back(TryConvertCharacterToRule(c));

        return parsed;
    }
private:
    inline Rule TryConvertCharacterToRule(char c) const {
        switch (c)
        {
        case 'F':
            return Rule::Forward;
        case '+':
            return Rule::Plus;
        case '-':
            return Rule::Minus;
        case '[':
            return Rule::Save;
        case ']':
            return Rule::Restore;
        default:
            std::stringstream ss;
            ss << "Character " << c << " does not match any pattern";
            throw std::invalid_argument(ss.str()); 
        }
    }
private:
    std::string_view pattern;
};

#endif