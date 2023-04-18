using game_telemetry;
using UnityEngine;

//Comportamiento de los checkpoints

public class CheckPoint : MonoBehaviour
{
    [SerializeField] float tiempoAdicional = 0; //tiempo adicional que se añade al llegar al checkpoint
    Transform posicionJugador; //referencia del jugador
    [SerializeField] int zone_id = 0;

    void Start()
    {
        //guardamos una referencia a la cámara
        posicionJugador = Camera.main.transform;
    }

    void Update()
    {
        //si se ha llegado a la posición del checkpoint
        if (posicionJugador.position.y > transform.position.y)
        {
            GameManager.instance.setLevelSection(zone_id);
            Telemetry.Instance.TrackEvent(new ArriveNewZoneEvent(TelemetryEvent.EventType.ARRIVE_NEW_ZONE, zone_id));

            //se guarda como el nuevo checkpoint
            GameManager.instance.CheckPoint(transform.position, tiempoAdicional);
            Destroy(gameObject); //destruimos el checkpoint
        }
    }
}
