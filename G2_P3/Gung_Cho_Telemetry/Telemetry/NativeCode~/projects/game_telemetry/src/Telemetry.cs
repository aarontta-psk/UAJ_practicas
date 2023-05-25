using System.Threading;
using System.Collections.Generic;
using System.Collections.Concurrent;

namespace game_telemetry
{
    public class Telemetry
    {
        private static Telemetry? instance;

        private const int ThreadDelay = 1500; // in ms
        private Thread telemetryThread;
        private bool runningThread;

        private List<Persistence> persistences;
        private ConcurrentQueue<TelemetryEvent> eventQueue;

        private long sessionID;
        public long SessionID { get => sessionID; private set { sessionID = value; } }

        private string gameName;
        public string GameName { get => gameName; private set { gameName = value; } }

        private string directory;
        public string Directory { get => directory; private set { directory = value; } }

        private Telemetry() { }

        public static Telemetry Instance => instance;

        public static bool Init(string directory_, string gameName_, long sessionId_)
        {
            if (instance != null)
            {
                System.Console.WriteLine("Ya has inicializado la instancia.");
                return false;
            }

            instance = new Telemetry();
            instance.TelemetrySetup(directory_, gameName_, sessionId_);
            return true;
        }

        public static void Release()
        {
            instance.TelemetryStop();
            instance = null;
        }

        public void TrackEvent(TelemetryEvent t_event)
        {
            eventQueue.Enqueue(t_event);
        }

        private void Run()
        {
            while (runningThread)
            {
                Persist();
                Thread.Sleep(ThreadDelay);
            }
            Persist();
        }

        private void Persist()
        {
            TelemetryEvent? t_event;
            while (eventQueue.TryDequeue(out t_event))
            {
                foreach (Persistence persistence in persistences)
                    persistence.Save(t_event);
            }
        }

        private void TelemetrySetup(string directory_, string gameName_, long sessionId_)
        {
            Directory = directory_;
            GameName = gameName_;
            SessionID = sessionId_;

            eventQueue = new ConcurrentQueue<TelemetryEvent>();
            eventQueue.Enqueue(new SessionStartEvent(TelemetryEvent.EventType.SESSION_START));

            persistences = new List<Persistence>();
            persistences.Add(new FilePersistence(new JsonSerializer()));
            persistences.Add(new FilePersistence(new CsvSerializer()));
            persistences.Add(new FilePersistence(new BinarySerializer()));

            runningThread = true;
            telemetryThread = new Thread(Run);
            telemetryThread.Start();
        }

        private void TelemetryStop()
        {
            runningThread = false;
            eventQueue.Enqueue(new SessionEndEvent(TelemetryEvent.EventType.SESSION_END));
            telemetryThread.Join();
        }
    }
}