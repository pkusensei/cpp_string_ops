#include "Ops.h"

std::string_view trim(std::string_view text)
{
    return trim_start(trim_end(text));
}

std::string_view trim_start(std::string_view text)
{
    auto it = std::find_if(text.cbegin(), text.cend(),
                           [](char c) { return !std::isspace(c); });
    if (it == text.cend())
        return std::string_view();

    auto diff = it - text.cbegin();
    text.remove_prefix(diff);
    return text;
}

std::string_view trim_end(std::string_view text)
{
    auto it = std::find_if(text.crbegin(), text.crend(),
                           [](char c) { return !isspace(c); });
    if (it == text.crend())
        return std::string_view();

    auto diff = it - text.crbegin();
    text.remove_suffix(diff);
    return text;
}
