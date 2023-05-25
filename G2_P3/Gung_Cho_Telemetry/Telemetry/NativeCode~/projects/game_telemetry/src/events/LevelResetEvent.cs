using Newtonsoft.Json;

namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the player dies because of the timer, and the level resets
    /// </summary>
    /// <param name="PosPlayerX">X axis' position of the player before reset</param>
    /// <param name="PosPlayerY">Y axis' position of the player before reset</param>
    /// <param name="CurrentLevel">Current level reset</param>
    [System.Serializable]
    public class LevelResetEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)] public float PosPlayerX { get; private set; }
        [JsonProperty(Order = 5)] public float PosPlayerY { get; private set; }
        [JsonProperty(Order = 6)] public int CurrentLevel { get; private set; }

        public LevelResetEvent(EventType type, float posPlayerX, float posPlayerY, int currentLevel) : base(type)
        {
            PosPlayerX = posPlayerX;
            PosPlayerY = posPlayerY;
            CurrentLevel = currentLevel;
        }
    }
}