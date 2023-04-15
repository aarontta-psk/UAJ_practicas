using System;
using System.Collections;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.SceneManagement;


public class Transiciones : MonoBehaviour
{
    [DllImport("game_telemetry.dll")]
    public static extern void telemetry_initialization();

    [DllImport("game_telemetry.dll")]
    public static extern int telemetry_track_event();

    [DllImport("game_telemetry.dll")]
    public static extern void telemetry_release();

    static public Transiciones instance = null;
    Animator transitions = null;
    bool noRepetir = true;

    void Awake()
    {
        if (instance == null)
        {
            instance = this;
            DontDestroyOnLoad(gameObject);
        }
        else Destroy(gameObject);
    }
    void Start()
    {
        telemetry_initialization();
        Debug.Log(telemetry_track_event());
        telemetry_release();

        transitions = GetComponentInChildren<Animator>();
    }

    public void MakeTransition(int indice)
    {
        if (noRepetir)
        {
            noRepetir = false;
            StartCoroutine(Transicion(indice));
        }
    }

    private IEnumerator Transicion(int indice)
    {
        transitions.SetTrigger("Salida");
        yield return new WaitForSeconds(0.9f);
        noRepetir = true;
        SceneManager.LoadScene(indice);
    }
}
