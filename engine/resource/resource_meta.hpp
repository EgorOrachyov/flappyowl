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

#ifndef GAME_ENGINE_TUTORIAL_RESOURCE_META_HPP
#define GAME_ENGINE_TUTORIAL_RESOURCE_META_HPP

#include "core/class.hpp"
#include "core/fast_vector.hpp"
#include "core/string_id.hpp"
#include "io/yaml.hpp"
#include "resource/resource.hpp"

#include <filesystem>
#include <optional>
#include <vector>

namespace wmoge {

    /**
     * @class ResourceMeta
     * @brief Meta information of a particular resource
     */
    struct ResourceMeta {
        class Class*            resource_class = nullptr;
        class ResourcePak*      pak            = nullptr;
        StringId                loader;
        fast_vector<StringId>   deps;
        std::filesystem::path   path_on_disk;
        std::optional<YamlTree> import_options;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_RESOURCE_META_HPP
