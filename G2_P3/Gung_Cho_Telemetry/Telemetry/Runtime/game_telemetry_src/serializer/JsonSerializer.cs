using Newtonsoft.Json;

namespace game_telemetry
{
    /// <summary>
    /// Serializer in JSON format
    /// </summary>
    public class JsonSerializer : ISerializer
    {
        /// <summary>
        /// Serializes the parent attributes first and the child attributes second.
        /// </summary>
        public string Serialize(TelemetryEvent t_event)
        {
            JsonSerializerSettings jsonSerializerSettings = new JsonSerializerSettings();
            jsonSerializerSettings.Formatting = Formatting.Indented;
            return JsonConvert.SerializeObject(t_event, jsonSerializerSettings);
        }

        public string Extension()
        {
            return ".json";
        }
    }
}