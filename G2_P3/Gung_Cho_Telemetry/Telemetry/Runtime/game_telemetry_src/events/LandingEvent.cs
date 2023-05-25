using Newtonsoft.Json;

namespace game_telemetry
{
    [System.Serializable]
    public class LandingEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)]
        public float PosPlayerX { get; private set; }
        [JsonProperty(Order = 5)]
        public float PosPlayerY { get; private set; }

        public LandingEvent(EventType type, float posPlayerX, float posPlayerY) : base(type)
        {
            PosPlayerX = posPlayerX;
            PosPlayerY = posPlayerY;
        }
    }
}
