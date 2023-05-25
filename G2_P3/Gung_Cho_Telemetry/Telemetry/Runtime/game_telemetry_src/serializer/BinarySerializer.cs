using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace game_telemetry
{
    public class BinarySerializer : ISerializer
    {
        public string Serialize(TelemetryEvent t_event)
        {
            string serialized;
            BinaryFormatter binaryFormatter = new BinaryFormatter();
            using (MemoryStream memoryStream = new MemoryStream())
            {
#pragma warning disable SYSLIB0011
                binaryFormatter.Serialize(memoryStream, t_event);
#pragma warning restore SYSLIB0011
                memoryStream.Position = 0;

                using (StreamReader streamReader = new StreamReader(memoryStream))
                {
                    serialized = streamReader.ReadToEnd();      
                }                 
            }

            return serialized;
        }

        public string Extension()
        {
            return ".bin";
        }
    }
}