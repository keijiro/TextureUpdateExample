#include <cstdint>
#include <cmath>
#include "IUnityRenderingExtensions.h"

namespace
{
    // Old school plasma effect
    uint32_t Plasma(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t frame)
    {
        auto px = (float)x / width;
        auto py = (float)y / height;
        auto time = frame / 60.0f;

        auto l = std::sinf(px * std::sinf(time * 1.3f) + std::sinf(py * 4 + time) * std::sinf(time));

        auto r = (uint32_t)(std::sinf(l *  6) * 127 + 127);
        auto g = (uint32_t)(std::sinf(l *  7) * 127 + 127);
        auto b = (uint32_t)(std::sinf(l * 10) * 127 + 127);

        return r + (g << 8) + (b << 16) + 0xff000000;
    }

    // Callback for texture update events
    void TextureUpdateCallback(int eventID, void* data)
    {
        auto event = static_cast<UnityRenderingExtEventType>(eventID);

        if (event == kUnityRenderingExtEventUpdateTextureBegin)
        {
            // UpdateTextureBegin: Generate and return texture image data.
            auto params = reinterpret_cast<UnityRenderingExtTextureUpdateParams*>(data);
            auto frame = params->userData;

            uint32_t* img = new uint32_t[params->width * params->height];
            for (auto y = 0u; y < params->height; y++)
                for (auto x = 0u; x < params->width; x++)
                    img[y * params->width + x] = Plasma(x, y, params->width, params->height, frame);

            params->texData = img;
        }
        else if (event == kUnityRenderingExtEventUpdateTextureEnd)
        {
            // UpdateTextureEnd: Free up the temporary memory.
            auto params = reinterpret_cast<UnityRenderingExtTextureUpdateParams*>(data);
            delete[] reinterpret_cast<uint32_t*>(params->texData);
        }
    }
}

extern "C" UnityRenderingEventAndData UNITY_INTERFACE_EXPORT GetTextureUpdateCallback()
{
    return TextureUpdateCallback;
}

namespace
{
    // Callback for texture update events
    void TextureUpdateCallbackV2(int eventID, void* data)
    {
        auto event = static_cast<UnityRenderingExtEventType>(eventID);

        if (event == kUnityRenderingExtEventUpdateTextureBeginV2)
        {
            // UpdateTextureBegin: Generate and return texture image data.
            auto params = reinterpret_cast<UnityRenderingExtTextureUpdateParamsV2*>(data);
            auto frame = params->userData;

            uint32_t* img = new uint32_t[params->width * params->height];
            for (auto y = 0u; y < params->height; y++)
                for (auto x = 0u; x < params->width; x++)
                    img[y * params->width + x] = Plasma(x, y, params->width, params->height, frame);

            params->texData = img;
        }
        else if (event == kUnityRenderingExtEventUpdateTextureEndV2)
        {
            // UpdateTextureEnd: Free up the temporary memory.
            auto params = reinterpret_cast<UnityRenderingExtTextureUpdateParamsV2*>(data);
            delete[] reinterpret_cast<uint32_t*>(params->texData);
        }
    }
}

extern "C" UnityRenderingEventAndData UNITY_INTERFACE_EXPORT GetTextureUpdateCallbackV2()
{
    return TextureUpdateCallbackV2;
}
