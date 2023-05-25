using Newtonsoft.Json;

namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the player starts a new level
    /// </summary>
    /// <param name="CurrentLevel">Level the player starts playing</param>
    [System.Serializable]
    public class StartLevelEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)] public int CurrentLevel { get; private set; }

        public StartLevelEvent(EventType type, int currentLevel) : base(type)
        {
            CurrentLevel = currentLevel;
        }
    }
}