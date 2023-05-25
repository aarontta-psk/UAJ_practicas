namespace game_telemetry
{
    public abstract class Persistence
    {
        protected ISerializer serializer;

        protected Persistence(ISerializer serializer_)
        {
            serializer = serializer_;
        }

        public abstract void Save(TelemetryEvent t_event);
    }
}
