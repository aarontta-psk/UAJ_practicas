namespace game_telemetry
{
    public interface ISerializer
    {
        public string Serialize(TelemetryEvent t_event);
        public string Extension();
    }
}