namespace game_telemetry
{
    [System.Serializable]
    public class SessionStartEvent : TelemetryEvent
    {
        public SessionStartEvent(EventType type) : base(type)
        {
        }
    }
}
