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

#ifndef GAME_ENGINE_TUTORIAL_AUDIO_PLAYBACK_HPP
#define GAME_ENGINE_TUTORIAL_AUDIO_PLAYBACK_HPP

#include "core/ref.hpp"
#include "core/string_id.hpp"
#include "math/vec.hpp"
#include "resource/audio_stream.hpp"

namespace wmoge {

    /**
     * @class AudioPlayback
     * @brief An instance of audio stream for playing sound
     */
    class AudioPlayback : public RefCnt {
    public:
        ~AudioPlayback() override = default;

        virtual void play()                        = 0;
        virtual void stop()                        = 0;
        virtual void pause()                       = 0;
        virtual void resume()                      = 0;
        virtual void set_position(Vec3f value)     = 0;
        virtual void set_velocity(Vec3f value)     = 0;
        virtual void set_direction(Vec3f value)    = 0;
        virtual void set_pitch_scale(float value)  = 0;
        virtual void set_gain(float value)         = 0;
        virtual void set_min_gain(float value)     = 0;
        virtual void set_max_gain(float value)     = 0;
        virtual void set_max_distance(float value) = 0;
        virtual void set_loop(bool value)          = 0;

        const ref_ptr<AudioStream>& get_stream() const { return m_stream; }
        const StringId&             get_name() const { return m_name; }
        const StringId&             get_bus_name() const { return m_bus_name; }

    protected:
        ref_ptr<AudioStream> m_stream;
        StringId             m_name;
        StringId             m_bus_name;
    };

}// namespace wmoge

#endif//GAME_ENGINE_TUTORIAL_AUDIO_PLAYBACK_HPP
