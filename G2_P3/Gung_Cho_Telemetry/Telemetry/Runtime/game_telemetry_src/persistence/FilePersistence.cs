using System.IO;

namespace game_telemetry
{
    /// <summary>
    /// Persistence the events to a file on disk
    /// </summary>
    class FilePersistence : Persistence
    {
        string fileName;

        /// <summary>
        /// Saves a file path to be created in the telemetry folder (GameName_SessionID.[json/csv/bin])
        /// </summary>
        public FilePersistence(ISerializer serializer_) : base(serializer_)
        {
            if (!Directory.Exists(Telemetry.Instance.Directory))
                Directory.CreateDirectory(Telemetry.Instance.Directory);
            fileName = Telemetry.Instance.Directory + Telemetry.Instance.GameName + "_" + Telemetry.Instance.SessionID.ToString() + serializer.Extension();
        }

        /// <summary>
        /// Writes the given event in the previously saved file path
        /// </summary>
        public override void Save(TelemetryEvent t_event)
        {
            using (StreamWriter streamWriter = new StreamWriter(fileName, true))
            {
                string serialisedEvent = serializer.Serialize(t_event);
                streamWriter.WriteLine(serialisedEvent);
            }
        }
    }
}