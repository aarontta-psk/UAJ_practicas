using Newtonsoft.Json;

namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the player throw the hook
    /// </summary>
    /// <param name="PosPlayerX">X axis' position of the player</param>
    /// <param name="PosPlayerY">Y axis' position of the player</param>
    /// <param name="PosMouseX">X axis' position of the mouse</param>
    /// <param name="PosMouseY">Y axis' position of the mouse</param>
    /// <param name="NumHooks">Remaining hooks before use</param>
    [System.Serializable]
    public class ThrowHookEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)] public float PosPlayerX { get; private set; }
        [JsonProperty(Order = 5)] public float PosPlayerY { get; private set; }
        [JsonProperty(Order = 6)] public float PosMouseX { get; private set; }
        [JsonProperty(Order = 7)] public float PosMouseY { get; private set; }
        [JsonProperty(Order = 8)] public int NumHooks { get; private set; }

        public ThrowHookEvent(EventType type, float posPlayerX, float posPlayerY, float posMouseX, float posMouseY, int numHooks) : base(type)
        {
            PosPlayerX = posPlayerX;
            PosPlayerY = posPlayerY;
            PosMouseX = posMouseX;
            PosMouseY = posMouseY;
            NumHooks = numHooks;
        }
    }
}