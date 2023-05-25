using Newtonsoft.Json;

namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the player reachs a new zone
    /// </summary>
    /// <param name="ZoneID">ID of the new zone</param>
    [System.Serializable]
    public class ArriveNewZoneEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)] public int ZoneID { get; private set; }

        public ArriveNewZoneEvent(EventType type, int zoneID) : base(type)
        {
            ZoneID = zoneID;
        }
    }
}