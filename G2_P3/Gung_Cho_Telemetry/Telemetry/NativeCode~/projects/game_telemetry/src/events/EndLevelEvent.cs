using Newtonsoft.Json;

namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the player finishes the level
    /// </summary>
    /// <param name="CurrentLevel">Current level finished</param>
    [System.Serializable]
    public class EndLevelEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)] public int CurrentLevel { get; private set; }

        public EndLevelEvent(EventType type, int currentLevel) : base(type)
        {
            CurrentLevel = currentLevel;
        }
    }
}