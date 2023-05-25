using Newtonsoft.Json;

namespace game_telemetry
{
    [System.Serializable]
    public class ArriveNewZoneEvent : TelemetryEvent
    {
        [JsonProperty(Order = 4)]
        public int ZoneID { get; private set; }

        public ArriveNewZoneEvent(EventType type, int zoneID) : base(type)
        {
            ZoneID = zoneID;
        }
    }
}
