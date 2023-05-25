using Newtonsoft.Json;

namespace game_telemetry
{
    [System.Serializable]
    public class ExitLevelEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)]
        public int Level { get; private set; }

        public ExitLevelEvent(EventType type, int level) : base(type)
        {
            Level = level;
        }
    }
}