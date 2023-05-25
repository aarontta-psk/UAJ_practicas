using Newtonsoft.Json;

namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the player dies
    /// </summary>
    /// <param name="PosPlayerX">X axis' position of the player</param>
    /// <param name="PosPlayerY">Y axis' position of the player</param>
    /// <param name="Death">Cause of death</param>
    /// <param name="ZoneID">ID of the new zone</param>
    [System.Serializable]
    public class DeathEvent : TelemetryEvent
    {
        /// <summary>
        /// Declares type of death, between falling and receiving damage
        /// </summary>
        public enum DeathType { FELL, DAMAGE };

        [JsonProperty(Order = 4)] public DeathType Death { get; private set; }
        [JsonProperty(Order = 5)] public float PosPlayerX { get; private set; }
        [JsonProperty(Order = 6)] public float PosPlayerY { get; private set; }
        [JsonProperty(Order = 7)] public int ZoneID { get; private set; }

        public DeathEvent(EventType type, float posPlayerX, float posPlayerY, DeathType death, int zoneID) : base(type)
        {
            Death = death;
            PosPlayerX = posPlayerX;
            PosPlayerY = posPlayerY;
            ZoneID = zoneID;
        }
    }
}
