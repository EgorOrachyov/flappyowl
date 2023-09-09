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

#ifndef GAME_ENGINE_TUTORIAL_VK_WINDOW_HPP
#define GAME_ENGINE_TUTORIAL_VK_WINDOW_HPP

#include "core/fast_map.hpp"
#include "core/fast_vector.hpp"
#include "event/event_listener.hpp"
#include "gfx/vulkan/vk_defs.hpp"
#include "gfx/vulkan/vk_texture.hpp"

#include <array>
#include <memory>
#include <string>

namespace wmoge {

    /**
     * @class VKSwapChainSupportInfo
     * @brief Info used to select physical device and configure swap chain
     */
    struct VKSwapChainSupportInfo {
        VkSurfaceCapabilitiesKHR        capabilities{};
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR>   present_modes;
        bool                            support_presentation = false;
    };

    /**
     * @class VKWindow
     * @brief Wrapper for a vulkan surface and platform window presentation
     */
    class VKWindow : public RefCnt {
    public:
        VKWindow(ref_ptr<Window> window, VkSurfaceKHR surface, class VKDriver& driver);
        ~VKWindow() override;

        void init();

        void acquire_next();
        void get_support_info(VkPhysicalDevice device, uint32_t prs_family, VKSwapChainSupportInfo& info) const;

        const fast_vector<ref_ptr<VKTexture>>& color() const { return m_color_targets; }
        const ref_ptr<VKTexture>&              depth_stencil() const { return m_depth_stencil_target; }
        VkSurfaceKHR                           surface_khr() const { return m_surface; }
        VkSwapchainKHR                         swapchain() const { return m_swapchain; }
        VkSemaphore                            semaphore() const { return m_image_available[m_image_available_semaphore]; }

        int      version() const { return m_version; }
        int      width() const { return m_extent.width; }
        int      height() const { return m_extent.height; }
        uint32_t current() const { return m_current; }

    private:
        void create_image_semaphores();
        void subscribe();
        void select_properties();
        void create_swapchain();
        void release_swapchain();
        void recreate_swapchain();

    private:
        VkSurfaceKHR                    m_surface;
        VkSurfaceFormatKHR              m_surface_format;
        VkSurfaceCapabilitiesKHR        m_capabilities{};
        VkSwapchainKHR                  m_swapchain = VK_NULL_HANDLE;
        VkExtent2D                      m_extent{};
        VkExtent2D                      m_requested_extent{};
        VkPresentModeKHR                m_vsync       = VK_PRESENT_MODE_MAX_ENUM_KHR;
        VkPresentModeKHR                m_performance = VK_PRESENT_MODE_MAX_ENUM_KHR;
        fast_vector<ref_ptr<VKTexture>> m_color_targets;
        ref_ptr<VKTexture>              m_depth_stencil_target;

        ref_ptr<Window>        m_window;
        ref_ptr<EventListener> m_window_event;

        std::array<VkSemaphore, GfxLimits::FRAMES_IN_FLIGHT> m_image_available{};

        uint32_t m_current                   = 0;
        int      m_version                   = -1;
        int      m_image_available_semaphore = 0;
        bool     m_use_vsync                 = true;

        class VKDriver& m_driver;
    };

    /**
     * @class VKWindowManager
     * @brief Manager for vk windows
     */
    class VKWindowManager {
    public:
        VKWindowManager(const VKInitInfo& init_info, class VKDriver& driver);
        ref_ptr<VKWindow> get_or_create(const ref_ptr<Window>& window);

    private:
        fast_map<StringId, ref_ptr<VKWindow>>                               m_windows;
        std::function<VkResult(VkInstance, ref_ptr<Window>, VkSurfaceKHR&)> m_factory;
        class VKDriver&                                                     m_driver;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_VK_WINDOW_HPP
