using UnityEngine;
using UnityEngine.Rendering;

public class Test : MonoBehaviour
{
    Texture2D _texture;
    CommandBuffer _command;

#if UNITY_2018_3_OR_NEWER

#if PLATFORM_IOS
    [System.Runtime.InteropServices.DllImport("__Internal")]
#else
    [System.Runtime.InteropServices.DllImport("Plasma")]
#endif
    static extern System.IntPtr GetTextureUpdateCallbackV2();

#else

#if PLATFORM_IOS
    [System.Runtime.InteropServices.DllImport("__Internal")]
#else
    [System.Runtime.InteropServices.DllImport("Plasma")]
#endif
    static extern System.IntPtr GetTextureUpdateCallback();

#endif

    void Start()
    {
        _command = new CommandBuffer();
        _texture = new Texture2D(64, 64, TextureFormat.RGBA32, false);
        _texture.wrapMode = TextureWrapMode.Clamp;

        // Set the texture to the renderer with using a property block.
        var prop = new MaterialPropertyBlock();
        prop.SetTexture("_MainTex", _texture);
        GetComponent<Renderer>().SetPropertyBlock(prop);
    }

    void OnDestroy()
    {
        _command.Dispose();
        Destroy(_texture);
    }

    void Update()
    {
        // Request texture update via the command buffer.
#if UNITY_2018_3_OR_NEWER
        _command.IssuePluginCustomTextureUpdateV2(
            GetTextureUpdateCallbackV2(), _texture, (uint)(Time.time * 60)
        );
#else
        _command.IssuePluginCustomTextureUpdate(
            GetTextureUpdateCallback(), _texture, (uint)(Time.time * 60)
        );
#endif
        Graphics.ExecuteCommandBuffer(_command);
        _command.Clear();

        // Rotation
        transform.eulerAngles = new Vector3(10, 20, 30) * Time.time;
    }
}
