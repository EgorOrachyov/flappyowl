# declare static engine library
add_library(engine STATIC
        engine.hpp
        audio/audio_bus.hpp
        audio/audio_defs.hpp
        audio/audio_engine.hpp
        audio/audio_playback.hpp
        audio/openal/al_bus.cpp
        audio/openal/al_bus.hpp
        audio/openal/al_defs.cpp
        audio/openal/al_defs.hpp
        audio/openal/al_engine.cpp
        audio/openal/al_engine.hpp
        audio/openal/al_playback.cpp
        audio/openal/al_playback.hpp
        core/async.hpp
        core/callback_queue.cpp
        core/callback_queue.hpp
        core/class.cpp
        core/class.hpp
        core/cmd_line.cpp
        core/cmd_line.hpp
        core/crc32.cpp
        core/crc32.hpp
        core/data.cpp
        core/data.hpp
        core/engine.cpp
        core/engine.hpp
        core/fast_map.hpp
        core/fast_set.hpp
        core/fast_vector.hpp
        core/layer.hpp
        core/log.cpp
        core/log.hpp
        core/mask.hpp
        core/object.cpp
        core/object.hpp
        core/random.cpp
        core/random.hpp
        core/ref.cpp
        core/ref.hpp
        core/string_id.cpp
        core/string_id.hpp
        core/string_utf.cpp
        core/string_utf.hpp
        core/string_utils.cpp
        core/string_utils.hpp
        core/task.cpp
        core/task.hpp
        core/task_manager.cpp
        core/task_manager.hpp
        core/timer.cpp
        core/timer.hpp
        core/var.cpp
        core/var.hpp
        event/event.cpp
        event/event.hpp
        event/event_listener.cpp
        event/event_listener.hpp
        event/event_manager.cpp
        event/event_manager.hpp
        event/event_action.cpp
        event/event_action.hpp
        event/event_input.cpp
        event/event_input.hpp
        event/event_script.cpp
        event/event_script.hpp
        event/event_token.cpp
        event/event_token.hpp
        event/event_window.cpp
        event/event_window.hpp
        event/event_resource.cpp
        event/event_resource.hpp
        event/register_classes_event.cpp
        event/register_classes_event.hpp
        gameplay/action_manager.cpp
        gameplay/action_manager.hpp
        gameplay/action_map.cpp
        gameplay/action_map.hpp
        gameplay/game_token_manager.cpp
        gameplay/game_token_manager.hpp
        gfx/gfx_buffers.hpp
        gfx/gfx_defs.hpp
        gfx/gfx_driver.hpp
        gfx/gfx_pipeline.cpp
        gfx/gfx_pipeline.hpp
        gfx/gfx_render_pass.hpp
        gfx/gfx_resource.hpp
        gfx/gfx_sampler.cpp
        gfx/gfx_sampler.hpp
        gfx/gfx_shader.cpp
        gfx/gfx_shader.hpp
        gfx/gfx_texture.hpp
        gfx/gfx_vert_format.cpp
        gfx/gfx_vert_format.hpp
        gfx/vulkan/vk_buffers.cpp
        gfx/vulkan/vk_buffers.hpp
        gfx/vulkan/vk_defs.cpp
        gfx/vulkan/vk_defs.hpp
        gfx/vulkan/vk_desc_manager.cpp
        gfx/vulkan/vk_desc_manager.hpp
        gfx/vulkan/vk_driver.cpp
        gfx/vulkan/vk_driver.hpp
        gfx/vulkan/vk_mem_manager.cpp
        gfx/vulkan/vk_mem_manager.hpp
        gfx/vulkan/vk_pipeline.cpp
        gfx/vulkan/vk_pipeline.hpp
        gfx/vulkan/vk_queues.cpp
        gfx/vulkan/vk_queues.hpp
        gfx/vulkan/vk_render_pass.cpp
        gfx/vulkan/vk_render_pass.hpp
        gfx/vulkan/vk_resource.hpp
        gfx/vulkan/vk_sampler.cpp
        gfx/vulkan/vk_sampler.hpp
        gfx/vulkan/vk_shader.cpp
        gfx/vulkan/vk_shader.hpp
        gfx/vulkan/vk_texture.cpp
        gfx/vulkan/vk_texture.hpp
        gfx/vulkan/vk_vert_format.cpp
        gfx/vulkan/vk_vert_format.hpp
        gfx/vulkan/vk_window.cpp
        gfx/vulkan/vk_window.hpp
        io/archive.cpp
        io/archive.hpp
        io/archive_file.cpp
        io/archive_file.hpp
        io/archive_memory.cpp
        io/archive_memory.hpp
        io/compression.cpp
        io/compression.hpp
        io/yaml.cpp
        io/yaml.hpp
        math/aabb.hpp
        math/color.cpp
        math/color.hpp
        math/mat.hpp
        math/math_utils.cpp
        math/math_utils.hpp
        math/math_utils2d.hpp
        math/math_utils3d.hpp
        math/plane.hpp
        math/quat.hpp
        math/transform.hpp
        math/vec.hpp
        pfx/pfx_component.cpp
        pfx/pfx_component.hpp
        pfx/pfx_component_runtime.cpp
        pfx/pfx_component_runtime.hpp
        pfx/pfx_emitter.cpp
        pfx/pfx_emitter.hpp
        pfx/pfx_feature.hpp
        pfx/pfx_manager.cpp
        pfx/pfx_manager.hpp
        pfx/pfx_storage.cpp
        pfx/pfx_storage.hpp
        pfx/features/pfx_feature_color.cpp
        pfx/features/pfx_feature_color.hpp
        pfx/features/pfx_feature_lifetime.cpp
        pfx/features/pfx_feature_lifetime.hpp
        pfx/features/pfx_feature_movement.cpp
        pfx/features/pfx_feature_movement.hpp
        pfx/features/pfx_feature_size.cpp
        pfx/features/pfx_feature_size.hpp
        pfx/features/pfx_feature_sprite.cpp
        pfx/features/pfx_feature_sprite.hpp
        pfx/features/pfx_feature_velocity.cpp
        pfx/features/pfx_feature_velocity.hpp
        platform/application.cpp
        platform/application.hpp
        platform/file_system.cpp
        platform/file_system.hpp
        platform/input.hpp
        platform/input_defs.hpp
        platform/input_devices.hpp
        platform/window.hpp
        platform/window_manager.hpp
        platform/glfw/glfw_input.cpp
        platform/glfw/glfw_input.hpp
        platform/glfw/glfw_input_defs.hpp
        platform/glfw/glfw_input_devices.cpp
        platform/glfw/glfw_input_devices.hpp
        platform/glfw/glfw_window.cpp
        platform/glfw/glfw_window.hpp
        platform/glfw/glfw_window_manager.cpp
        platform/glfw/glfw_window_manager.hpp
        render/aux_draw_manager.cpp
        render/aux_draw_manager.hpp
        render/canvas.cpp
        render/canvas.hpp
        render/render_camera.cpp
        render/render_camera.hpp
        render/render_command.cpp
        render/render_command.hpp
        render/render_engine.cpp
        render/render_engine.hpp
        render/render_pipeline.cpp
        render/render_pipeline.hpp
        render/render_view.cpp
        render/render_view.hpp
        render/shader_builder.cpp
        render/shader_builder.hpp
        render/shader_cache.cpp
        render/shader_cache.hpp
        render/shader_variant.cpp
        render/shader_variant.hpp
        resource/audio_stream.cpp
        resource/audio_stream.hpp
        resource/audio_stream_wav.cpp
        resource/audio_stream_wav.hpp
        resource/font.cpp
        resource/font.hpp
        resource/config_file.cpp
        resource/config_file.hpp
        resource/image.cpp
        resource/image.hpp
        resource/material.cpp
        resource/material.hpp
        resource/material_shader.cpp
        resource/material_shader.hpp
        resource/mesh.cpp
        resource/mesh.hpp
        resource/pfx_effect.cpp
        resource/pfx_effect.hpp
        resource/resource.cpp
        resource/resource.hpp
        resource/resource_loader.hpp
        resource/resource_manager.cpp
        resource/resource_manager.hpp
        resource/resource_meta.hpp
        resource/resource_pak.hpp
        resource/scene_packed.cpp
        resource/scene_packed.hpp
        resource/script.cpp
        resource/script.hpp
        resource/shader.cpp
        resource/shader.hpp
        resource/sprite.cpp
        resource/sprite.hpp
        resource/text_file.cpp
        resource/text_file.hpp
        resource/texture.cpp
        resource/texture.hpp
        resource/register_classes_resource.cpp
        resource/register_classes_resource.hpp
        resource/loaders/resource_loader_assimp.cpp
        resource/loaders/resource_loader_assimp.hpp
        resource/loaders/resource_loader_default.cpp
        resource/loaders/resource_loader_default.hpp
        resource/paks/resource_pak_fs.cpp
        resource/paks/resource_pak_fs.hpp
        scene/scene.cpp
        scene/scene.hpp
        scene/scene_container.hpp
        scene/scene_component.cpp
        scene/scene_component.hpp
        scene/scene_manager.cpp
        scene/scene_manager.hpp
        scene/scene_object.cpp
        scene/scene_object.hpp
        scene/scene_system.hpp
        scene/register_classes_scene.cpp
        scene/register_classes_scene.hpp
        systems/system_render_2d.cpp
        systems/system_render_2d.hpp
        systems/system_script.cpp
        systems/system_script.hpp
        scripting/script_instance.hpp
        scripting/script_native.cpp
        scripting/script_native.hpp
        scripting/script_system.hpp
        scripting/lua/lua_defs.cpp
        scripting/lua/lua_defs.hpp
        scripting/lua/lua_event_script.cpp
        scripting/lua/lua_event_script.hpp
        scripting/lua/lua_script_instance.cpp
        scripting/lua/lua_script_instance.hpp
        scripting/lua/lua_script.cpp
        scripting/lua/lua_script.hpp
        scripting/lua/lua_script_system.cpp
        scripting/lua/lua_script_system.hpp
        scripting/lua/lua_type_traits.cpp
        scripting/lua/lua_type_traits.hpp
        scripting/lua_bindings/lua_bindings.hpp
        scripting/lua_bindings/lua_bindings_components.cpp
        scripting/lua_bindings/lua_bindings_components.hpp
        scripting/lua_bindings/lua_bindings_core.cpp
        scripting/lua_bindings/lua_bindings_core.hpp
        scripting/lua_bindings/lua_bindings_event.cpp
        scripting/lua_bindings/lua_bindings_event.hpp
        scripting/lua_bindings/lua_bindings_gameplay.cpp
        scripting/lua_bindings/lua_bindings_gameplay.hpp
        scripting/lua_bindings/lua_bindings_math.cpp
        scripting/lua_bindings/lua_bindings_math.hpp
        scripting/lua_bindings/lua_bindings_platform.cpp
        scripting/lua_bindings/lua_bindings_platform.hpp
        scripting/lua_bindings/lua_bindings_resource.cpp
        scripting/lua_bindings/lua_bindings_resource.hpp
        scripting/lua_bindings/lua_bindings_scene.cpp
        scripting/lua_bindings/lua_bindings_scene.hpp
        components/audio_listener_2d.cpp
        components/audio_listener_2d.hpp
        components/audio_source_2d.cpp
        components/audio_source_2d.hpp
        components/camera_2d.cpp
        components/camera_2d.hpp
        components/canvas_item.cpp
        components/canvas_item.hpp
        components/canvas_layer.cpp
        components/canvas_layer.hpp
        components/canvas_text.cpp
        components/canvas_text.hpp
        components/particles_2d.cpp
        components/particles_2d.hpp
        components/script_component.cpp
        components/script_component.hpp
        components/spatial_2d.cpp
        components/spatial_2d.hpp
        components/sprite_instance.cpp
        components/sprite_instance.hpp
        components/tag.cpp
        components/tag.hpp
        components/register_classes_components.cpp
        components/register_classes_components.hpp
        debug/console.cpp
        debug/console.hpp
        debug/profiler.cpp
        debug/profiler.hpp
        debug/debug_layer.cpp
        debug/debug_layer.hpp
        main/main.cpp
        main/main.hpp)

# specify public include path, so user can reference engine files by modules names
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/)

# engine dependencies, which are also visible to the engine users
target_link_libraries(engine PUBLIC cxxopts)
target_link_libraries(engine PUBLIC tinyxml2)
target_link_libraries(engine PUBLIC ryml)
target_link_libraries(engine PUBLIC magic_enum)
target_link_libraries(engine PUBLIC robin_hood)
target_link_libraries(engine PUBLIC svector)

# engine dependencies, private
target_link_libraries(engine PRIVATE glfw)
target_link_libraries(engine PRIVATE whereami)
target_link_libraries(engine PRIVATE stbimage)
target_link_libraries(engine PRIVATE freetype)
target_link_libraries(engine PRIVATE lz4)
target_link_libraries(engine PRIVATE assimp)

# audio dependencies, private
target_link_libraries(engine PRIVATE OpenAL)
target_link_libraries(engine PRIVATE audio_file)

# lua scripting dependencies, private
target_link_libraries(engine PRIVATE lua_static)
target_link_libraries(engine PRIVATE LuaBridge)

# vulkan rendering backend related dependencies, private
target_link_libraries(engine PRIVATE volk)
target_link_libraries(engine PRIVATE vma)
target_link_libraries(engine PRIVATE glslang)
target_link_libraries(engine PRIVATE SPIRV)

# generic functions to setup target
wmoge_target_defs(engine)