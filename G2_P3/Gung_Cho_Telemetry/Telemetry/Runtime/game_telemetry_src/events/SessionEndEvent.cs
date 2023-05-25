namespace game_telemetry
{
    [System.Serializable]
    class SessionEndEvent : TelemetryEvent
    {

        public SessionEndEvent(EventType type) : base(type)
        {
        }
    }
}
