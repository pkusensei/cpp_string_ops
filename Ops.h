#pragma once

#include <algorithm>
#include <cctype>
#include <string_view>
#include <sstream>
#include <vector>

std::string_view trim(std::string_view text);
std::string_view trim_start(std::string_view text);
std::string_view trim_end(std::string_view text);

constexpr bool is_blank(std::string_view text)
{
    return text.empty() ||
           std::all_of(text.cbegin(), text.cend(), std::isspace);
}

template <typename CharT>
bool starts_with(std::basic_string_view<CharT> sample, std::basic_string_view<CharT> pattern) noexcept
{
    if (sample.length() < pattern.length())
        return false;

    return std::equal(pattern.cbegin(), pattern.cend(), sample.cbegin());
}

template <typename CharT>
bool ends_with(std::basic_string_view<CharT> sample, std::basic_string_view<CharT> pattern) noexcept
{
    if (sample.length() < pattern.length())
        return false;

    return std::equal(pattern.crbegin(), pattern.crend(), sample.crbegin());
}

template <typename It, typename CharT = char>
std::basic_string<CharT> string_join(It begin, It end, CharT seperator)
{
    auto result = std::basic_string<CharT>();
    for (; begin != end; ++begin)
    {
        result += std::basic_string<CharT>(*begin) + seperator;
    }
    if (!result.empty())
        return result.erase(result.length() - 1);
    return result;
}

template <typename It, typename CharT = char>
std::vector<std::basic_string_view<CharT>> string_split(It begin, It end, CharT delimiter)
{
    auto result = std::vector<std::basic_string_view<CharT>>();
    if (begin == end)
        return result;
    auto it = std::find(begin, end, delimiter);
    if (it != end)
    {
        result.emplace_back(&*begin, it - begin);
        auto rest = string_split(++it, end, delimiter);
        result.insert(result.end(), rest.begin(), rest.end());
    }
    else
    {
        result.emplace_back(&*begin, end - begin);
    }
    return result;
}

///
/// Commented code ensures Args... is over CharT
/// But that does not work with const CharT* etc.
///
/// template <typename CharT = char, template<typename...>typename... Args>
template <typename CharT = char, typename... Args>
/// std::basic_string<CharT> build_string(Args<CharT> &&... args)
std::basic_string<CharT> build_string(Args &&... args)
{
    auto ss = std::basic_stringstream<CharT>();
    // (ss << ... << std::forward<Args<CharT>>(args));
    (ss << ... << std::forward<Args>(args));
    return ss.str();
}

template <typename CharT = char>
void replace_all(std::basic_string<CharT> &target, std::basic_string_view<CharT> from,
                 std::basic_string_view<CharT> to)
{
    if (target.empty())
        return;

    auto pos = target.find(from);
    while (pos != std::basic_string<CharT>::npos)
    {
        target.replace(pos, from.length(), to);
        pos = target.find(from);
    }
}