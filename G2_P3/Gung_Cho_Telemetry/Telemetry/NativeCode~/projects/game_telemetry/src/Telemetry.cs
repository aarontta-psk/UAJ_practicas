using System.Threading;
using System.Collections.Generic;
using System.Collections.Concurrent;

namespace game_telemetry
{
    /// <summary>
    /// Defines all the behaviour of the telemetry tracker
    /// </summary>
    public class Telemetry
    {
        private static Telemetry? instance;

        /// <summary>
        /// Telemetry thread variables
        /// </summary>
        private const int ThreadDelay = 1500; // in ms
        private Thread telemetryThread;
        private bool runningThread;

        private List<Persistence> persistences;
        private ConcurrentQueue<TelemetryEvent> eventQueue;

        /// <summary>
        /// Session ID to be used across the telemetry
        /// </summary>
        private long sessionID;
        public long SessionID { get => sessionID; private set { sessionID = value; } }

        /// <summary>
        /// Game name to be used across the telemetry
        /// </summary>
        private string gameName;
        public string GameName { get => gameName; private set { gameName = value; } }

        /// <summary>
        /// Directory to be used across the telemetry
        /// </summary>
        private string directory;
        public string Directory { get => directory; private set { directory = value; } }

        private Telemetry() { }

        public static Telemetry Instance => instance;

        /// <summary>
        /// Initializes explicitly the telemetry instance.
        /// If it's not called, Telemetry.Instance will return null.
        /// </summary>
        /// <param name="directory_">Directory path to store the data files</param>
        /// <param name="gameName_">Game name used to be used across the telemetry</param>
        /// <param name="sessionId_">Session ID to be used across the telemetry</param>
        /// <returns>true if correctly initialized</returns>
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

        /// <summary>
        /// Releases the telemetry instance.
        /// Requires previous call to the Init() function.
        /// </summary>
        public static void Release()
        {
            instance.TelemetryStop();
            instance = null;
        }

        /// <summary>
        /// Stores the event to track
        /// </summary>
        /// <param name="t_event"></param>
        public void TrackEvent(TelemetryEvent t_event)
        {
            eventQueue.Enqueue(t_event);
        }

        /// <summary>
        /// Telemetry thread
        /// </summary>
        private void Run()
        {
            while (runningThread)
            {
                Persist();
                Thread.Sleep(ThreadDelay);
            }
            Persist();
        }

        /// <summary>
        /// Persists to all the persistences in the telemetry.
        /// </summary>
        private void Persist()
        {
            TelemetryEvent? t_event;
            while (eventQueue.TryDequeue(out t_event))
            {
                foreach (Persistence persistence in persistences)
                    persistence.Save(t_event);
            }
        }

        /// <summary>
        /// Private method to start the instance
        /// </summary>
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

        /// <summary>
        /// Private method to stop the instance
        /// </summary>
        private void TelemetryStop()
        {
            runningThread = false;
            eventQueue.Enqueue(new SessionEndEvent(TelemetryEvent.EventType.SESSION_END));
            telemetryThread.Join();
        }
    }
}