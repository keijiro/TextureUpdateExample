#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "Unity/IUnityRenderingExtensions.h"

// Old school plasma effect
uint32_t Plasma(int x, int y, int width, int height, unsigned int frame)
{
    float px = (float)x / width;
    float py = (float)y / height;
    float time = frame / 60.0f;

    float l = sinf(px * sinf(time * 1.3f) + sinf(py * 4 + time) * sinf(time));

    uint32_t r = sinf(l *  6) * 127 + 127;
    uint32_t g = sinf(l *  7) * 127 + 127;
    uint32_t b = sinf(l * 10) * 127 + 127;

    return r + (g << 8) + (b << 16) + 0xff000000u;
}

// Callback for texture update events
void TextureUpdateCallback(int eventID, void* data)
{
    if (eventID == kUnityRenderingExtEventUpdateTextureBeginV2)
    {
        // UpdateTextureBegin: Generate and return texture image data.
        UnityRenderingExtTextureUpdateParamsV2* params = data;
        unsigned int frame = params->userData;

        uint32_t* img = malloc(params->width * params->height * 4);
        for (int y = 0; y < params->height; y++)
            for (int x = 0; x < params->width; x++)
                img[y * params->width + x] = Plasma(x, y, params->width, params->height, frame);

        params->texData = img;
    }
    else if (eventID == kUnityRenderingExtEventUpdateTextureEndV2)
    {
        // UpdateTextureEnd: Free up the temporary memory.
        UnityRenderingExtTextureUpdateParamsV2* params = data;
        free(params->texData);
    }
}

UnityRenderingEventAndData UNITY_INTERFACE_EXPORT GetTextureUpdateCallback()
{
    return TextureUpdateCallback;
}
