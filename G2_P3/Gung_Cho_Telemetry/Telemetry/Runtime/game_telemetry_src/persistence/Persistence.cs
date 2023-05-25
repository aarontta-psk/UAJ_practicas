namespace game_telemetry
{
    /// <summary>
    /// Base class that defines the common behaviour of all types of persistence
    /// </summary>
    public abstract class Persistence
    {
        protected ISerializer serializer;

        /// <summary>
        /// Receives the serialization type
        /// </summary>
        /// <param name="serializer_">Serialization type</param>
        protected Persistence(ISerializer serializer_)
        {
            serializer = serializer_;
        }

        /// <summary>
        /// Persist the event sent, depending of the type of serialization assign.
        /// Method to be redefined by each type of persistence
        /// </summary>
        /// <param name="t_event">Event sent</param>
        public abstract void Save(TelemetryEvent t_event);
    }
}