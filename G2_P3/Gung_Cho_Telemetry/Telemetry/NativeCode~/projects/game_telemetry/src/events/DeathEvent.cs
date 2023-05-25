using Newtonsoft.Json;

namespace game_telemetry
{
    [System.Serializable]
    public class DeathEvent : TelemetryEvent
    {
        public enum DeathType { FELL, DAMAGE };

        [JsonProperty(Order = 4)]
        public DeathType Death { get; private set; }
        [JsonProperty(Order = 5)]
        public int PosPlayerX { get; private set; }
        [JsonProperty(Order = 6)]
        public int PosPlayerY { get; private set; }
        [JsonProperty(Order = 7)]
        public int ZoneID { get; private set; }

        public DeathEvent(EventType type, int posPlayerX, int posPlayerY, DeathType death, int zoneID) : base(type)
        {
            Death = death;
            PosPlayerX = posPlayerX;
            PosPlayerY = posPlayerY;
            ZoneID = zoneID;
        }
    }
}
