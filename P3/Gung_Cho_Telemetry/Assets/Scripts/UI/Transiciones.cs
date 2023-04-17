using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;
using game_telemetry;

public class Transiciones : MonoBehaviour
{
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
        ////Telemetry.Init("Gung_Cho'", UnityEngine.Analytics.AnalyticsSessionInfo.sessionId);
        //Telemetry.Instance.TrackEvent(new ExitLevelEvent(TelemetryEvent.EventType.EXIT_LEVEL, 76));
        //Telemetry.Instance.TrackEvent(new ExitLevelEvent(TelemetryEvent.EventType.EXIT_LEVEL, 123));
        //Telemetry.Instance.TrackEvent(new LandingEvent(TelemetryEvent.EventType.LANDING_EVENT, 2, 3));
        ////Telemetry.Release();

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
