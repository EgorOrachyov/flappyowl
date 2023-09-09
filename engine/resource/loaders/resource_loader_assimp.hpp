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

#ifndef GAME_ENGINE_TUTORIAL_RESOURCE_LOADER_ASSIMP_HPP
#define GAME_ENGINE_TUTORIAL_RESOURCE_LOADER_ASSIMP_HPP

#include "math/mat.hpp"
#include "math/vec.hpp"
#include "resource/resource.hpp"
#include "resource/resource_loader.hpp"
#include "resource/resource_meta.hpp"
#include "resource/resource_pak.hpp"

#include <assimp/mesh.h>
#include <assimp/scene.h>

namespace wmoge {

    /**
     * @class ResourceLoaderAssimp
     * @brief Loader for a mesh an animation data based on assimp library
     */
    class ResourceLoaderAssimp final : public ResourceLoader {
    public:
        ~ResourceLoaderAssimp() override = default;
        bool     load(const StringId& name, const ResourceMeta& meta, ref_ptr<Resource>& res) override;
        bool     can_load(const StringId& resource_type) override;
        StringId get_name() override;

    private:
        bool process_node(struct AssimpImportContext& context, aiNode* node, const Mat4x4f& parent_transform, const Mat4x4f& inv_parent_transform);
        bool process_mesh(struct AssimpImportContext& context, aiMesh* mesh, const Mat4x4f& transform, const Mat4x4f& inv_transform);
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_RESOURCE_LOADER_ASSIMP_HPP
