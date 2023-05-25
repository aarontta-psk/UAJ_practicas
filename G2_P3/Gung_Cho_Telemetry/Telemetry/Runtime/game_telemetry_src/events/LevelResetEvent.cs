using Newtonsoft.Json;

namespace game_telemetry
{
    [System.Serializable]
    public class LevelResetEvent : TelemetryEvent
    {
        //Posicion ANTES del reinicio
        [JsonProperty(Order = 4)]
        public float PosPlayerX { get; private set; }
        [JsonProperty(Order = 5)]
        public float PosPlayerY { get; private set; }
        [JsonProperty(Order = 6)]
        public int CurrentLevel { get; private set; }

        public LevelResetEvent(EventType type, float posPlayerX, float posPlayerY, int currentLevel) : base(type)
        {
            PosPlayerX = posPlayerX;
            PosPlayerY = posPlayerY;
            CurrentLevel = currentLevel;
        }
    }
}