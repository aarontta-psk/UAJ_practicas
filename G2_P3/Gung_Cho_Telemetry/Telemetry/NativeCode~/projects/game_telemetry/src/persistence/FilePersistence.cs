using System.IO;

namespace game_telemetry
{
    class FilePersistence : Persistence
    {
        string fileName;

        public FilePersistence(ISerializer serializer_) : base(serializer_)
        {
            if (!Directory.Exists(Telemetry.Instance.Directory))
                Directory.CreateDirectory(Telemetry.Instance.Directory);
            fileName = Telemetry.Instance.Directory + Telemetry.Instance.GameName + "_" + Telemetry.Instance.SessionID.ToString() + serializer.Extension();
        }

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
