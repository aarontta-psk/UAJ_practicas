using System.Threading;

namespace game_telemetry
{
    /// <summary>
    /// Quick Main to test telemetry functionality
    /// </summary>
    public class Program
    {
        static void Main(string[] args)
        {
            Telemetry.Init("./telemetry_data/", "TelemetrySystem", 69);

            Telemetry.Instance.TrackEvent(new ExitLevelEvent(TelemetryEvent.EventType.EXIT_LEVEL, 123));
            Thread.Sleep(2000 * 2);
            Telemetry.Instance.TrackEvent(new ExitLevelEvent(TelemetryEvent.EventType.NONE, 76));

            Telemetry.Release();
        }
    }
}
