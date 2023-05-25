using System.Text;
using System.Reflection;
using System.Linq;

namespace game_telemetry
{
    public class CsvSerializer : ISerializer
    {
        public string Serialize(TelemetryEvent t_event)
        {
            // this relays on the fact that we always obtain a child class of TelemetryEvent
            StringBuilder stringBuilder = new StringBuilder();
            foreach (PropertyInfo propertyInfo in t_event.GetType().BaseType.GetProperties())
                stringBuilder.AppendFormat("{0},", propertyInfo.GetValue(t_event, null));
            foreach (PropertyInfo propertyInfo in t_event.GetType().GetProperties().Where(property => property.DeclaringType == t_event.GetType()))
                stringBuilder.AppendFormat("{0},", propertyInfo.GetValue(t_event, null));
            return stringBuilder.ToString();
        }

        public string Extension()
        {
            return ".csv";
        }
    }
}