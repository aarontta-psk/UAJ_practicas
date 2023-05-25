namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the session starts
    /// </summary>
    [System.Serializable]
    public class SessionStartEvent : TelemetryEvent
    {
        public SessionStartEvent(EventType type) : base(type) { }
    }
}