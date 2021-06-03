TextureUpdateExample
====================

![gif](https://i.imgur.com/VqHhCcx.gif)

*Old-school plasma effect generated by C++ code*

This is an example that shows how to use the [CustomTextureUpdate] callback
that allows native plugins to update contents of textures in a thread safe and
platform agnostic way.

[CustomTextureUpdate]:
  https://docs.unity3d.com/ScriptReference/Rendering.CommandBuffer.IssuePluginCustomTextureUpdate.html

How to implement the CustomTextureUpdate callback
-------------------------------------------------

The callback function should be implemented with the following signature:

```c
void TextureUpdateCallback(int eventID, void *data)
{
  UnityRenderingExtTextureUpdateParamsV2 *params = data;
}
```

The type of the event will be given to `eventID`, and the attributes of the
target texture will be given with `UnityRenderingExtTextureUpdateParamsV2`
struct carried by the `data` pointer.

The possible values of `eventID` are defined in `UnityRenderingExtEventType`;
Only `kUnityRenderingExtEventUpdateTextureBeginV2` and
`kUnityRenderingExtEventUpdateTextureEndV2` are relevant to the texture update
callback.

### `kUnityRenderingExtEventUpdateTextureBeginV2` event

This event is invoked right before updating the texture. You can give raw image
data via the `texData` pointer in the parameter struct.

```c
if (eventID == kUnityRenderingExtEventUpdateTextureBeginV2)
{
  uint8_t *img = malloc(params->width * params->height * 4);

  // Fill image data here.

  params->texData = img;
}
```

You can also give `nullptr` to `texData` when you don't like to update the
texture in this frame.

### `kUnityRenderingExtEventUpdateTextureEndV2` event

This event is invoked right after updating the texture. You can safely release
resources used to update the texture.

```c
if (event == kUnityRenderingExtEventUpdateTextureEndV2)
{
  free(params->texData);
}
```

### Interface function

You have to implement an interface function that is used to retrieve the
pointer of the callback function.

```
UnityRenderingEventAndData UNITY_INTERFACE_EXPORT GetTextureUpdateCallback()
{
  return TextureUpdateCallback;
}
```

For further details of the plugin implementation, please see the
[example source code](https://github.com/keijiro/TextureUpdateExample/blob/master/Plugin/Plasma.c)
contained in this repository.

How to update texture from C# script
------------------------------------

In order to request texture update from a C# script, you can use
`IssuePluginCustomTextureUpdateV2` with a `CommandBuffer`. The pointer to the
callback function and a reference to a texture object should be given to the
command. You can also give a single `uint` value to the command that can be
used as user data to the callback.

```
[DllImport("DllName")] static extern IntPtr GetTextureUpdateCallback();

var callback = GetTextureUpdateCallback();
m_CommandBuffer.IssuePluginCustomTextureUpdateV2(callback, texture, userData);
Graphics.ExecuteCommandBuffer(m_CommandBuffer);
```
