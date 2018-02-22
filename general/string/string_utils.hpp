// string_utils.hpp
//
// MIT License
//
// Copyright (c) 2017 Heikki Hellgren <heiccih@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef STRING_STRING_UTIL_HPP_
#define STRING_STRING_UTIL_HPP_

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <functional>
#include <locale>
#include <random>
#include <string>
#include <vector>

namespace drodil {
namespace general {
namespace string {

/// \brief Splits string to vector based on given delimeter
///
/// \param[in] str   std::string to split
/// \param[in] delim std::string to split with
///
/// \return std::vector<std::string>
static inline std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> ret;
    if (str.empty()) {
        return ret;
    }

    std::string::size_type start = 0;
    do {
        std::size_t x = str.find(delim, start);
        if (x == std::string::npos) {
            break;
        }
        std::string substr = str.substr(start, x - start);
        ret.push_back(substr);
        start += (delim.size() + substr.size());
    } while (true);

    ret.push_back(str.substr(start));

    return ret;
}

/// \brief Trim string from the start
///
/// \param[in|out] trimmed std::string to trim
///
/// \return std::string
static inline std::string& l_trim(std::string& trimmed)
{
    std::ignore = trimmed.erase(trimmed.begin(), std::find_if(trimmed.begin(), trimmed.end(),
                                                  std::not1(std::ptr_fun<int, int>(std::isspace))));
    return trimmed;
}

/// \brief Trim string from the end
///
/// \param[in|out] trimmed std::string to trim
///
/// \return std::string
static inline std::string& r_trim(std::string& trimmed)
{
    std::ignore = trimmed.erase(
        std::find_if(trimmed.rbegin(), trimmed.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
        trimmed.end());
    return trimmed;
}

/// \brief Trim string from the start and end
///
/// \param[in|out] trimmed String to trim
///
/// \return std::string
static inline std::string& trim(std::string& trimmed)
{
    return l_trim(r_trim(trimmed));
}

/// \brief Generate random string
///
/// \param[in] length size_t Size of the generated string
///
/// \return std::string
static inline std::string random_string(std::size_t length)
{
    static auto& chrs = "0123456789"
                        "abcdefghijklmnopqrstuvwxyz"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) -
                                                                                          2);
    std::string ret;
    ret.reserve(length);

    while (length > 0) {
        ret += chrs[pick(rg)];
        --length;
    }

    return ret;
}

} // namespace string
} // namespace general
} // namespace drodil

#endif // STRING_STRING_UTIL_HPP_
