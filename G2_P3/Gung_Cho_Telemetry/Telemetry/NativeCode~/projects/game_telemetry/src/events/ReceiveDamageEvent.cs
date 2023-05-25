using Newtonsoft.Json;

namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the player receives damage from an enemy or obstacle
    /// </summary>
    /// <param name="PosPlayerX">X axis' position of the player</param>
    /// <param name="PosPlayerY">Y axis' position of the player</param>
    /// <param name="DmgType">Types of damage</param>
    [System.Serializable]
    public class ReceiveDamageEvent : TelemetryEvent
    {
        /// <summary>
        /// Declares type of damage, between enemy or obstacle
        /// </summary>
        public enum DamageType { ENEMY, OBSTACLE }

        [JsonProperty(Order = 4)] public DamageType DmgType { get; private set; }
        [JsonProperty(Order = 5)] public float PosPlayerX { get; private set; }
        [JsonProperty(Order = 6)] public float PosPlayerY { get; private set; }

        public ReceiveDamageEvent(EventType type, float posPlayerX, float posPlayerY, DamageType dmgType) : base(type)
        {
            PosPlayerX = posPlayerX;
            PosPlayerY = posPlayerY;
            DmgType = dmgType;
        }
    }
}