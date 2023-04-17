using UnityEngine;
using game_telemetry;

//Comportamiento del daño que se le hace al jugador (enemigos, obstáculos)

public class DanhoAlJugador : MonoBehaviour
{
    void OnTriggerEnter2D (Collider2D other)
    {
        VidaJugador vida = other.gameObject.GetComponent<VidaJugador>(); //comprobamos si detecta a una entidad con vida (jugador)

        if (vida != null) //si detecta al jugador
        {
            Telemetry.Instance.TrackEvent(new ReceiveDamageEvent(TelemetryEvent.EventType.RECEIVE_DMG, (int)transform.position.x, (int)transform.position.y, ReceiveDamageEvent.DamageType.ENEMY));
            vida.EliminaVidaJugador(); //llamamos al metodo de quitar vida del jugador    
        }
    }
}
