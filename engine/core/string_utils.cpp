/**********************************************************************************/
/* Flappyowl game                                                                 */
/* Available at github https://github.com/EgorOrachyov/flappyowl                  */
/**********************************************************************************/
/* MIT License                                                                    */
/*                                                                                */
/* Copyright (c) 2023 Egor Orachyov                                               */
/*                                                                                */
/* Permission is hereby granted, free of charge, to any person obtaining a copy   */
/* of this software and associated documentation files (the "Software"), to deal  */
/* in the Software without restriction, including without limitation the rights   */
/* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      */
/* copies of the Software, and to permit persons to whom the Software is          */
/* furnished to do so, subject to the following conditions:                       */
/*                                                                                */
/* The above copyright notice and this permission notice shall be included in all */
/* copies or substantial portions of the Software.                                */
/*                                                                                */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  */
/* SOFTWARE.                                                                      */
/**********************************************************************************/

#include "string_utils.hpp"

#include <cstdlib>

namespace wmoge {

    float StringUtils::to_float(const std::string& str) {
        return std::strtof(str.c_str(), nullptr);
    }
    double StringUtils::to_double(const std::string& str) {
        return std::strtod(str.c_str(), nullptr);
    }
    int StringUtils::to_int(const std::string& str, int base) {
        return std::stoi(str, nullptr, base);
    }
    unsigned long StringUtils::to_ulong(const std::string& str, int base) {
        return std::stoul(str, nullptr, base);
    }
    std::string StringUtils::from_int(int value) {
        char buffer[64];
        snprintf(buffer, 64, "%i", value);
        return buffer;
    }
    std::string StringUtils::from_uint(unsigned int value) {
        char buffer[64];
        snprintf(buffer, 64, "%u", value);
        return buffer;
    }
    std::string StringUtils::from_float(float value, int precision) {
        char buffer[64];
        snprintf(buffer, 64, "%.*f", precision, value);
        return buffer;
    }
    std::string StringUtils::from_double(double value, int precision) {
        char buffer[64];
        snprintf(buffer, 64, "%.*lf", precision, value);
        return buffer;
    }
    std::string StringUtils::from_bool(bool value) {
        return value ? "true" : "false";
    }
    std::string StringUtils::from_ptr(const void* value) {
        char buffer[64];
        snprintf(buffer, 64, "%p", value);
        return buffer;
    }
    std::string StringUtils::from_mem_size(std::size_t bytes_size) {
        const double STEP      = 1024;
        const int    PRECISION = 2;
        double       size_f    = static_cast<double>(bytes_size);
        char         buffer[64];

        if (size_f < STEP) {
            snprintf(buffer, 64, "%.*lf bytes", PRECISION, size_f);
            return buffer;
        }
        size_f /= STEP;

        if (size_f < STEP) {
            snprintf(buffer, 64, "%.*lf KB", PRECISION, size_f);
            return buffer;
        }
        size_f /= STEP;

        if (size_f < STEP) {
            snprintf(buffer, 64, "%.*lf MB", PRECISION, size_f);
            return buffer;
        }
        size_f /= STEP;

        snprintf(buffer, 64, "%.*lf GB", PRECISION, size_f);
        return buffer;
    }
    void StringUtils::split(const std::string& what, const std::string& splitters, std::vector<std::string>& result) {
        std::size_t pos = 0;

        while (pos < what.length()) {
            std::size_t token = what.find_first_of(splitters, pos);
            std::string word  = what.substr(pos, token);
            pos               = token != std::string::npos ? token + 1 : what.length();

            if (!word.empty()) {
                result.push_back(std::move(word));
            }
        }
    }

}// namespace wmoge