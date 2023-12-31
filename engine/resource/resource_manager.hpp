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

#ifndef GAME_ENGINE_TUTORIAL_RESOURCE_MANAGER_HPP
#define GAME_ENGINE_TUTORIAL_RESOURCE_MANAGER_HPP

#include "core/async.hpp"
#include "core/fast_map.hpp"
#include "core/fast_vector.hpp"
#include "core/object.hpp"
#include "core/string_id.hpp"
#include "core/task.hpp"
#include "resource/resource.hpp"
#include "resource/resource_loader.hpp"
#include "resource/resource_meta.hpp"
#include "resource/resource_pak.hpp"

#include <filesystem>
#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

namespace wmoge {

    /**
     * @class ResourceCallback
     * @brief Callback function called when resource loading request is finished
     *
     * Use this callback function in async resource loading request.
     * As argument function accepts resource being loaded.
     * Function called when either resource successfully loaded or failed to load.
     */
    using ResourceCallback = AsyncCallback<ref_ptr<Resource>>;

    /**
     * @class ResourceManager
     * @brief Manages resources loading and caching in the engine
     *
     * Resource manager is responsible for all engine resources management.
     * It supports all common resource manipulation operations.
     *
     * - Automatically resolves resource names
     * - Uses resource pak to abstract resource storage
     * - Allows to load a resource using name
     * - Allows async loading
     * - Allows async loading of resource with dependencies
     */
    class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager() = default;

        /**
         * @brief Async load of engine resource using provided resource name
         *
         * Allows to load game resource by its name. Resources are stored inside game
         * resource pak file. Resource manager automatically resolves resource path by its name.
         *
         * @note Each resource must have a resource meta info file (in .xml) format. This meta info
         *       file allows to get resource reflection data, required to load resource at runtime.
         *
         * @note If resource already loaded and cached in the engine,
         *       the reference to loaded instance is returned.
         *
         * @note If resource is already queued to be loaded, reference to loaded resource is returned.
         *
         * @note Pass callback function to be notified when resource loading is finished.
         *       If resource already cached, this function will be called immediately before function return.
         *
         * @param name Unique name of the resource to load
         * @param callback Callback to call on main thread when resource is loaded.
         *
         * @return Resource reference
         */
        Async<ref_ptr<Resource>> load_async(const StringId& name, ResourceCallback callback = ResourceCallback());

        /**
         * @brief Sync load of the engine resource using provided resource name
         *
         * Allows to load game resource by its name. Resources are stored inside game
         * resource pak file. Resource manager automatically resolves resource path by its name.
         *
         * @note Each resource must have a resource meta info file (in .xml) format. This meta info
         *       file allows to get resource reflection data, required to load resource at runtime.
         *
         * @note If resource already loaded and cached in the engine,
         *       the reference to loaded instance is returned.
         *
         * @note Sync resource loading is a simple and straightforward approach to work with
         *       resources. But blocks current thread and takes extra processing time in case of
         *       sync load of a large amount of resources. Consider using `load_async` method.
         *
         * @param name Unique name of the resource to load
         *
         * @return Resource reference
         */
        ref_ptr<Resource> load(const StringId& name);

        /** @brief Find a resource by name if it is already cached */
        ref_ptr<Resource> find(const StringId& name);

        /** @brief Add specific format resource loader */
        void add_loader(std::shared_ptr<ResourceLoader> loader);

        /** @brief Add additional pak for resources loading */
        void add_pak(std::shared_ptr<ResourcePak> pak);

        /**
         * @brief Clear from a cache only unused resource
         *
         * This is a costly operation, which traverses all cached
         * resources in a resource system and evicts those entries,
         * which are not used by the engine at this time.
         *
         * @note This operation allows to free some used memory and resources
         *       at cost of traversal plus potential loading of resource,
         *       if they requested in future.
         *
         * @note Call this operation with regular intervals in couple of frames
         *       or on scene changes or large streaming chunks updates.
         */
        void gc();

        /**
         * @brief Evicts all loaded resources from a cache
         *
         * Clear entirely cache of loaded resources. Any new resource loading
         * operation will require resource loading from a disk.
         *
         * @note Clearing cache does not free memory of currently used resources
         *       in the engine due to strong memory references.
         */
        void clear();

    private:
        /**
         * @class LoadState
         * @brief Tracks loading state of a single resource
         */
        class LoadState {
        public:
            fast_vector<ref_ptr<Resource>>          deps_res;
            fast_vector<AsyncOp<ref_ptr<Resource>>> deps_ops;
            AsyncOp<ref_ptr<Resource>>              async_op;
            ref_ptr<Task>                           task;
        };

        bool       load_meta(const StringId& name, ResourceMeta& resource_meta, std::shared_ptr<ResourceLoader>& loader);
        LoadState* load_internal(const StringId& name, ResourceMeta& resource_meta, const std::shared_ptr<ResourceLoader>& loader);

    private:
        fast_vector<std::shared_ptr<ResourcePak>>           m_paks;
        fast_map<StringId, ref_ptr<Resource>>               m_resources;
        fast_map<StringId, LoadState>                       m_loading;
        fast_map<StringId, std::shared_ptr<ResourceLoader>> m_loaders;

        mutable std::recursive_mutex m_mutex;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_RESOURCE_MANAGER_HPP
