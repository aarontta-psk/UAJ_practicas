using UnityEngine;
using game_telemetry;

//Comportamiento de la DeathZone (hija de la cámara)

public class MuertePorCaida : MonoBehaviour
{
    [SerializeField] AudioSource aud = null;

    void OnTriggerEnter2D(Collider2D collision) //cuando alguna entidad entre al "trigger" 
    {
        if (collision.gameObject.GetComponent<Transform>().position.y > transform.position.y)
        {
            Estados jugador = collision.gameObject.GetComponent<Estados>(); //comprobamos si es el jugador

            if (jugador != null && jugador.Estado() != estado.Muerte) //en caso de que lo fuera
            {
                jugador.CambioEstado(estado.Muerte); //cambiamos su estado a Muerte
                Telemetry.Instance.TrackEvent(new DeathEvent(TelemetryEvent.EventType.DEATH, transform.position.x, transform.position.y, DeathEvent.DeathType.FELL, GameManager.instance.getCurrentLevel()));
                aud.Play();
                GameManager.instance.Muerte();
            }
        }
    }
}
