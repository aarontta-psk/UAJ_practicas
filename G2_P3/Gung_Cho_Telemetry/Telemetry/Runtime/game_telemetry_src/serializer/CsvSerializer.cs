using System.Text;
using System.Reflection;
using System.Linq;

namespace game_telemetry
{
    /// <summary>
    /// Serializer in CSV format
    /// </summary>
    public class CsvSerializer : ISerializer
    {
        /// <summary>
        /// Serializes the parent attributes first and the child attributes second.
        /// </summary>
        public string Serialize(TelemetryEvent t_event)
        {
            // This relays on the fact that we always get a child class of TelemetryEvent
            StringBuilder stringBuilder = new StringBuilder();
            foreach (PropertyInfo propertyInfo in t_event.GetType().BaseType.GetProperties())
                stringBuilder.AppendFormat("{0};", propertyInfo.GetValue(t_event, null));
            foreach (PropertyInfo propertyInfo in t_event.GetType().GetProperties().Where(property => property.DeclaringType == t_event.GetType()))
                stringBuilder.AppendFormat("{0};", propertyInfo.GetValue(t_event, null));
            return stringBuilder.ToString();
        }

        public string Extension()
        {
            return ".csv";
        }
    }
}