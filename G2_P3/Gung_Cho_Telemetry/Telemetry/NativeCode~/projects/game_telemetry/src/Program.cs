using System.Threading;

namespace game_telemetry
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Telemetry.Init("TelemetrySystem", 69);

            Telemetry.Instance.TrackEvent(new ExitLevelEvent(TelemetryEvent.EventType.DEFAULT, 76));
            Telemetry.Instance.TrackEvent(new ExitLevelEvent(TelemetryEvent.EventType.EXIT_LEVEL, 123));
            //Telemetry.Instance.TrackEvent(new LandingEvent(TelemetryEvent.EventType.DEFAULT, 2, 3));

            Thread.Sleep(5000 * 2);
            Telemetry.Instance.TrackEvent(new ExitLevelEvent(TelemetryEvent.EventType.DEFAULT, 76));

            Telemetry.Release();
        }
    }
}
