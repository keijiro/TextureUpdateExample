using UnityEngine;
using UnityEngine.Rendering;

public class Test : MonoBehaviour
{
    Texture2D _texture;
    CommandBuffer _command;

    [System.Runtime.InteropServices.DllImport("Noise")]
    static extern System.IntPtr GetTextureUpdateCallback();

    void Start()
    {
        _command = new CommandBuffer();
        _texture = new Texture2D(256, 256, TextureFormat.RGBA32, false);

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
        _command.IssuePluginCustomTextureUpdate(
            GetTextureUpdateCallback(), _texture, (uint)(Time.time * 30000)
        );
        Graphics.ExecuteCommandBuffer(_command);
        _command.Clear();

        // Rotation
        transform.eulerAngles = new Vector3(10, 20, 30) * Time.time;
    }
}
