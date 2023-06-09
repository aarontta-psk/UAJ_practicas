﻿using UnityEngine;
using game_telemetry;

//Comportamiento del daño que se le hace al jugador (enemigos, obstáculos)

public class DanhoAlJugadorObstaculos : MonoBehaviour
{
    void OnCollisionEnter2D(Collision2D other)
    {
        VidaJugador vida = other.gameObject.GetComponent<VidaJugador>(); //comprobamos si detecta a una entidad con vida (jugador)
        KnockBack kb = other.gameObject.GetComponent<KnockBack>(); //comprobamos si detecta a una entidad con vida (jugador)

        if (vida != null && kb != null) //si detecta al jugador
        {
            Telemetry.Instance.TrackEvent(new ReceiveDamageEvent(TelemetryEvent.EventType.RECEIVE_DMG, transform.position.x, transform.position.y, ReceiveDamageEvent.DamageType.OBSTACLE));
            vida.EliminaVidaObstaculos(); //llamamos al metodo de quitar vida del jugador    
            kb.Knockback(other.contacts[0].point);
        }
    }
}