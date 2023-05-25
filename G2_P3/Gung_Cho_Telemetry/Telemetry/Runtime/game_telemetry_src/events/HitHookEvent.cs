using Newtonsoft.Json;

namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the player hits the hook
    /// </summary>
    /// <param name="PosHookX">X axis' position of the hook</param>
    /// <param name="PosHookY">Y axis' position of the hook</param>
    /// <param name="AccelerationX">X axis' direction of the player's acceleration</param>
    /// <param name="AccelerationY">Y axis' direction of the player's acceleration</param>
    [System.Serializable]
    public class HitHookEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)] public float PosHookX { get; private set; }
        [JsonProperty(Order = 5)] public float PosHookY { get; private set; }
        [JsonProperty(Order = 6)] public float AccelerationX { get; private set; }
        [JsonProperty(Order = 7)] public float AccelerationY { get; private set; }

        public HitHookEvent(EventType type, float posHookX, float posHookY, float accelerationX, float accelerationY) : base(type)
        {
            PosHookX = posHookX;
            PosHookY = posHookY;
            AccelerationX = accelerationX;
            AccelerationY = accelerationY;
        }
    }
}
