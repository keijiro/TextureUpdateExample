#include <cstdint>
#include "Unity/IUnityRenderingExtensions.h"

namespace
{
    // Callback for texture update events
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API TextureUpdateCallback(int eventID, void* data)
    {
        auto event = static_cast<UnityRenderingExtEventType>(eventID);

        if (event == kUnityRenderingExtEventUpdateTextureBegin)
        {
            // UpdateTextureBegin: Generate and return texture image data.
            auto params = reinterpret_cast<UnityRenderingExtTextureUpdateParams*>(data);
            auto offs = params->userData;

            uint32_t* img = new uint32_t[params->width * params->height];
            for (auto i = 0u; i < params->width * params->height; i++) img[i] = i * 149 + offs;

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
