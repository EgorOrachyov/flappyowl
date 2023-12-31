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

#include "scene_packed.hpp"

#include "core/class.hpp"
#include "core/engine.hpp"
#include "core/log.hpp"
#include "core/timer.hpp"
#include "debug/profiler.hpp"
#include "platform/file_system.hpp"
#include "resource/resource_manager.hpp"
#include "scene/scene_manager.hpp"

namespace wmoge {

    bool ScenePacked::load_from_import_options(const YamlTree& tree) {
        WG_AUTO_PROFILE_RESOURCE();

        if (!Resource::load_from_import_options(tree)) {
            return false;
        }

        auto params = tree["params"];

        std::string format;
        params["format"] >> format;

        std::string file;
        params["file"] >> file;

        assert(format == "text");

        if (format == "text") {
            std::vector<std::uint8_t> data;
            if (!Engine::instance()->file_system()->read_file(file, data)) {
                WG_LOG_ERROR("failed to read file " << file);
                return false;
            }

            m_scene_data_yaml.emplace(Yaml::parse(data));
            if (m_scene_data_yaml.value().empty()) {
                WG_LOG_ERROR("failed to parse file " << file);
                return false;
            }

            return true;
        }

        WG_LOG_ERROR("unsupported scene format " << format);
        return false;
    }
    void ScenePacked::copy_to(Resource& copy) {
        Resource::copy_to(copy);
        auto* scene_packed              = dynamic_cast<ScenePacked*>(&copy);
        scene_packed->m_scene_data_yaml = m_scene_data_yaml;
    }

    Async<ref_ptr<Scene>> ScenePacked::instantiate_async() {
        WG_AUTO_PROFILE_RESOURCE();

        assert(m_scene_data_yaml.has_value());

        if (!m_scene_data_yaml.has_value()) {
            WG_LOG_ERROR("cannot instantiate scene from no data");
            return Async<ref_ptr<Scene>>{};
        }

        auto* resource_manager = Engine::instance()->resource_manager();
        auto& file             = m_scene_data_yaml.value();
        auto  scene_async      = make_async_op<ref_ptr<Scene>>();
        auto  deps             = file["deps"];
        auto  scene_packed     = ref_ptr<ScenePacked>(this);

        std::vector<Async<ref_ptr<Resource>>> deps_loading;

        for (auto it = deps.first_child(); it.valid(); it = it.next_sibling()) {
            auto res       = Yaml::read_sid(it);
            auto res_async = resource_manager->load_async(res);

            if (res_async.is_null()) {
                WG_LOG_ERROR("failed to obtain async load for dep " << res);
                return Async<ref_ptr<Scene>>{};
            }

            deps_loading.push_back(std::move(res_async));
        }

        auto scene_task = make_ref<Task>(get_name(), [scene_async, scene_packed](auto&) {
            WG_AUTO_PROFILE_RESOURCE();

            Timer timer;

            timer.start();

            auto* scene_manager = Engine::instance()->scene_manager();
            auto  scene         = scene_manager->make_scene(scene_packed->get_name());

            if (!scene->m_root->on_load_from_yaml(scene_packed->m_scene_data_yaml.value()["tree"])) {
                WG_LOG_ERROR("failed to instantiate scene " << scene_packed->get_name() << " from text (yaml) file");
                scene_async->set_failed();
                return 0;
            }

            timer.stop();

            WG_LOG_INFO("instantiate scene " << scene_packed->get_name() << ", time: " << timer.get_elapsed_sec() << " sec");
            scene_async->set_result(std::move(scene));
            return 0;
        });

        scene_task->add_on_completion([scene_async](AsyncStatus status, std::optional<int>&) {
            if (status == AsyncStatus::Failed) {
                scene_async->set_failed();
            }
        });

        WG_LOG_INFO("total deps to pre-load " << deps_loading.size() << " for " << get_name());

        scene_task->set_to_wait_total(int(deps_loading.size()));

        for (auto& dep : deps_loading) {
            dep.add_dependency(scene_task.as<AsyncStateBase>());
        }

        return Async<ref_ptr<Scene>>(scene_async);
    }
    ref_ptr<Scene> ScenePacked::instantiate() {
        WG_AUTO_PROFILE_RESOURCE();

        auto async = instantiate_async();
        async.wait_completed();
        return async.is_failed() ? ref_ptr<Scene>{} : async.result();
    }

    void ScenePacked::register_class() {
        auto* cls = Class::register_class<ScenePacked>();
    }

}// namespace wmoge