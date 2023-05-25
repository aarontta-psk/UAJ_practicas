using Newtonsoft.Json;

namespace game_telemetry
{
    public class JsonSerializer : ISerializer
    {
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