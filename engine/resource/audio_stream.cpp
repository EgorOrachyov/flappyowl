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

#include "audio_stream.hpp"

#include "core/class.hpp"

namespace wmoge {

    bool AudioStream::load_from_import_options(const YamlTree& tree) {
        return Resource::load_from_import_options(tree);
    }
    void AudioStream::copy_to(Resource& copy) {
        Resource::copy_to(copy);
        auto* audio_stream              = dynamic_cast<AudioStream*>(&copy);
        audio_stream->m_length          = m_length;
        audio_stream->m_samples_rate    = m_samples_rate;
        audio_stream->m_bits_per_sample = m_bits_per_sample;
        audio_stream->m_num_samples     = m_num_samples;
        audio_stream->m_num_channels    = m_num_channels;
    }

    float AudioStream::get_length() const {
        return m_length;
    }
    int AudioStream::get_samples_rate() const {
        return m_samples_rate;
    }
    int AudioStream::get_bits_per_sample() const {
        return m_bits_per_sample;
    }
    int AudioStream::get_num_samples() const {
        return m_num_samples;
    }
    int AudioStream::get_num_channels() const {
        return m_num_channels;
    }
    bool AudioStream::is_stereo() const {
        return m_num_channels == 2;
    }
    bool AudioStream::is_mono() const {
        return m_num_channels == 1;
    }

    void AudioStream::register_class() {
        auto* cls = Class::register_class<AudioStream>();
    }

}// namespace wmoge