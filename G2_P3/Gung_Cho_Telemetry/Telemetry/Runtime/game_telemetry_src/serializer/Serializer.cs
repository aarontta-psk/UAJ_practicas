namespace game_telemetry
{
    /// <summary>
    /// Strategy that defines serialization methods to be used in the persistence
    /// </summary>
    public interface ISerializer
    {
        /// <summary>
        /// Serializes an event in a given format 
        /// </summary>
        /// <param name="t_event">Event to be serialized. Always an inherited class of TelemetryEvent</param>
        public string Serialize(TelemetryEvent t_event);
        /// <summary>
        /// Defines the extension of the file. Depends on the serializaion format used.
        /// </summary>
        public string Extension();
    }
}