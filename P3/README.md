
# Documento de diseño de telemetría:

https://docs.google.com/document/d/1jXWNDBsTnRgbYLDq4J6koX9-YJfLB20WUw7e8dS9A3M/edit?usp=share_link

# Instrumentalizacion:
Se han cambiado los siguientes scripts:

 - Telemetry.Init() 
 Clase GameManager, lineas  43-47 codigo condicional para build y editor.
   
  
 - Telemetry.Release() -
Clase GameManager, linea  254.
   

 - Telemetry.TrackEvent()

	 - ExitLevelEvent
Clase GameManager, linea  156 y 253

	-	DeathEvent
	Clase GameManager, linea  94 y Clase MuertePorCaida, linea  19

	-	StartLevelEvent
	Clase GameManager, linea  161

	-	EndLevelEvent
	Clase GameManager, linea  174

	-	DeathEvent
	Clase GameManager, linea  94

	-	LevelResetEvent
	Clase Timer, linea  85

	-	ArriveNewZoneEvent
	Clase Checkpoint, linea  24

	-	StartLevelEvent
	Clase FinalDeNivel, linea  30

	-	ReceiveDamageEvent
	 Clase DanhoAlJugadorObstaculos, linea  15 Y Clase DanhoAlJugador, linea  14

	-	ThrowHookEvent
	 Clase CrearGancho, linea  75

	-	HitHookEvent
	Clase Gancho, linea  65

	-	LandingEvent
	Clase Suelo, linea  26

# Ejemplo de prueba
En la carpeta Gung_Cho_Telemetry_Data_Example hay un ejemplo que incluye todos los eventos que admite el tracker en las 3 serializaciones disponibles: Binario, Json y Csv