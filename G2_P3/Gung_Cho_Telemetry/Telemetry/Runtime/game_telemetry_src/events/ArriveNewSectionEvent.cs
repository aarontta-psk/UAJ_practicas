
namespace game_telemetry
{
    public class ArriveNewSectionEvent: TelemetryEvent
    {
        //ID DE SECCION
        public int section_ID;

        public ArriveNewSectionEvent(EventType type, int section_IDAux) : base(type)
        {
            section_ID = section_IDAux;
        }
    }
}
