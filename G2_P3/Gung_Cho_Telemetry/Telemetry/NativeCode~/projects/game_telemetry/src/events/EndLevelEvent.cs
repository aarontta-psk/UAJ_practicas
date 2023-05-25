using Newtonsoft.Json;

namespace game_telemetry
{
    [System.Serializable]
    public class EndLevelEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)]
        public int CurrentLevel { get; private set; }

        public EndLevelEvent(EventType type, int currentLevel) : base(type)
        {
            CurrentLevel = currentLevel;
        }
    }
}
