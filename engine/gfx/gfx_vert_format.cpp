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

#include "gfx_vert_format.hpp"

#include "core/crc32.hpp"

#include <cassert>
#include <cstring>

namespace wmoge {

    GfxVertElements::GfxVertElements() {
        std::memset(&m_elements, 0, sizeof(m_elements));
    }
    bool GfxVertElements::operator==(const GfxVertElements& other) const {
        return std::memcmp(&m_elements, &other.m_elements, sizeof(m_elements)) == 0;
    }
    std::size_t GfxVertElements::hash() const {
        return Crc32::hash(&m_elements, sizeof(m_elements));
    }
    void GfxVertElements::add_element(StringId name, GfxFormat format, int buffer, int offset, int stride, bool instanced) {
        assert(m_elements_count < GfxLimits::MAX_VERT_ATTRIBUTES);
        m_elements_names[m_elements_count]     = std::move(name);
        m_elements[m_elements_count].format    = format;
        m_elements[m_elements_count].buffer    = buffer;
        m_elements[m_elements_count].stride    = stride;
        m_elements[m_elements_count].offset    = offset;
        m_elements[m_elements_count].instanced = instanced;
        m_elements_count += 1;
    }

}// namespace wmoge