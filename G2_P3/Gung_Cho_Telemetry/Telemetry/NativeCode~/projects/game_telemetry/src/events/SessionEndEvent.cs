namespace game_telemetry
{
    /// <summary>
    /// Event used to store data when the session end
    /// </summary>
    [System.Serializable]
    class SessionEndEvent : TelemetryEvent
    {
        public SessionEndEvent(EventType type) : base(type) { }
    }
}