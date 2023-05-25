using Newtonsoft.Json;

namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the player exits the level through the menu or when you close the game
    /// </summary>
    /// <param name="Level">Current level exited</param>
    [System.Serializable]
    public class ExitLevelEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)] public int Level { get; private set; }

        public ExitLevelEvent(EventType type, int level) : base(type)
        {
            Level = level;
        }
    }
}