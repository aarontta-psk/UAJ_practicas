# **Sistema de telemetría**

## **Autores**
- Sam Blázquez Martín
- Diego Castillo Sánchez
- Aarón Nauzet Moreno Sosa
- Alberto Muñoz Fernñandez
- Iago Quintas Diz

## **Objetivos y preguntas de investigación**

### Objetivo:
* **Determinar si la dificultad está equilibrada**

### Preguntas de Investigación:
* ¿El jugador avanza adecuadamente en cada sección de cada nivel?
* ¿El jugador consigue pasar cada nivel con el tiempo establecido?
* ¿Los jugadores aciertan los ganchos al usarlos?

## **Métricas**
* **¿El jugador avanza adecuadamente en cada sección de cada nivel?**
	* Número medio de muertes por caída en cada sección
	* Número medio de muertes por pérdidas de vida en cada sección
	* Media de tiempo en pasarse cada sección
* **¿El jugador consigue pasar cada nivel con el tiempo establecido?**
	* Porcentaje de veces que se acaba el nivel con tiempo con respecto al número de intentos
	* Tiempo medio que sobra a los usuarios al acabar cada nivel
	* Número medio de veces que se reinicia cada nivel por falta de tiempo
* **¿Los jugadores aciertan los ganchos al usarlos?**
	* Número medio de usos efectivos del gancho (uso efectivo implica avanzar en el eje Y tras usarlo)
	* Porcentaje de ganchos acertados

## **Eventos**

Con carácter general, todos los eventos contendrán los **siguientes campos**:
* Tipo del evento (enum)
* ID de la sesión
* Marca temporal

Los **eventos mínimos** a recoger son:
* **Inicio de sesión**
* **Fin de sesión**
* **Inicio de nivel**
	* Nivel actual
* **Final de nivel**
	* Nivel actual

Los **eventos concretos** que se van recoger y descripción:
* **Lanzar gancho**
	* Posición jugador (X e Y)
	* Posición ratón (X e Y)
	* Cargas gancho (antes de usarlo)
* **Acertar gancho**
	* Posición gancho (X e Y)
	* Aceleración (X e Y)
* **Aterrizaje**
	* Posición jugador (X e Y)
* **Llegar a nueva sección**
	* ID de la sección
* **Muerte**
	* Posición jugador (X e Y) 
	* Tipo de muerte (caída o daño)
	* ID de sección
* **Recibir daño**
	* Posición jugador (X e Y) 
	* Tipo de enemigo o elemento que ha causado el daño
* **Reinicio de nivel**
	* Posición jugador (X e Y) [antes de reiniciar]
	* Nivel en el que está
* **Salir del nivel**
	* Nivel

Los **eventos que aplicaremos por métrica** serán:
* **Número medio de muertes por caída en cada sección**
	* Muerte
		* Usamos el evento de muerte para identificar las veces que se muere por caída y localizar puntos inesperadamente altos de muerte por caída para los usuarios. 
		* Se calcula como la media de muerte por caída de todos los jugadores en cada sección. Cada muerte por caída se obtiene de contar los eventos de muerte que indican que son de este tipo en sus atributos. La posición del jugador se guarda en caso de querer además visualizar la métrica con un mapa de calor.
* **Número medio de muertes por pérdidas de vida en cada sección**
	* Muerte
	* Recibir daño
		* Usamos el evento de muerte para identificar cuantas veces  se muere un jugador por pérdidas de vida, y el evento de recibir daño para localizar puntos en los que los usuarios puedan estar perdiendo demasiadas vidas, así como el elemento del nivel que está ocasionando esta situación, y si la pérdida de vidas hasta la muerte sucede en un periodo de tiempo demasiado corto.
		* Se calcula de la misma forma que el anterior, pero contando los marcados con el atributo de daño por pérdida de vida.
* **Media de tiempo en pasarse cada sección**
	* Llegar a nueva zona
	* Avance del jugador
	* Salir del nivel
		* Comparar el tiempo transcurrido entre los eventos de llegar a una nueva zona y la siguiente para discernir qué zonas ocupan más tiempo a los usuarios, y estudiar con los eventos de avance del jugador el progreso de posiciones a lo largo del tiempo para destacar puntos que hayan podido demorar en exceso a los usuarios.
		* Se calcula como la media de tiempos de todos los jugadores en cada sección. Cada tiempo en cada sección se obtiene con la resta entre cada evento de fin de sección y su evento inmediatamente anterior de comienzo de sección con misma id de sección. En caso de que el jugador abandone el nivel, se descarta el tiempo.
* **Porcentaje de veces que se acaba el nivel con tiempo sobrante con respecto al número de intentos**
	* Inicio de nivel
	* Fin de nivel
	* Reinicio de nivel
		* Recoger el número de eventos de reinicio de un nivel entre los eventos de inicio de nivel y fin de nivel, para comparar cuantos intentos le han requerido a los usuarios superar un nivel. 
		* Se calcula contando el número de veces que se termina el nivel sobrando el tiempo (número de eventos fin de nivel) y las veces que el tiempo se agota (número de eventos reinicio de nivel). Se suman ambas y se calcula el porcentaje, y luego se calcula la media de todos los porcentajes entre todas las sesiones.
* **Tiempo medio que sobra a los usuarios al acabar cada nivel**
	* Inicio de nivel
	* Fin de nivel
		* Recoger la diferencia de tiempo entre los eventos de inicio del nivel y fin de nivel.
* **Número medio de veces que se reinicia cada nivel por falta de tiempo**
	* Reinicio de nivel
	* Avance del jugador
		* Recoger el número de veces que el jugador se queda sin tiempo antes de pasarse el nivel para estudiar junto con los eventos de progreso del jugador, si el tiempo está ajustado lo suficiente como para que los jugadores completen los niveles.
* **Número medio de veces que los usuarios reciben daño por contacto enemigo**
	* Recibir daño
		* Recoger el número de veces que el jugador recibe daño de forma directa por un enemigo.
* **Número medio de veces que los usuarios caen a una posición menor o igual a la original tras haber utilizado un gancho**
	* Lanzar gancho
	* Posición tras gancho
		* Se comparan las posiciones del jugador en el evento de lanzar gancho y tras el evento de posición tras gancho, y se determina si el jugador ha sido capaz de progresar el nivel y la segunda posición es más alta que la primera.
* **Porcentaje de ganchos acertados**
	* Lanzar gancho
	* Acertar gancho
		* Se recoge cada uso con el gancho, el objetivo de este evento es el estudio de que el jugador esté haciendo un uso productivo de las cargas de sus ganchos.

# **Instrumentalizacion**
Se han cambiado los siguientes archivos:

- **Telemetry.Init()**
	- Clase GameManager, lineas  43-47 codigo condicional para build y editor.
   
  
- **Telemetry.Release()**
	- Clase GameManager, linea  254.
   

- **Telemetry.TrackEvent()**
	- **ExitLevelEvent**
		- Clase GameManager, linea  156 y 253
	- **DeathEvent**
		- Clase *GameManager*, linea 94
		- Clase *MuertePorCaida*, linea 19
	- **StartLevelEvent**
		- Clase *GameManager*, linea 161
	- **EndLevelEvent**
		- Clase *GameManager*, linea 174
	- **DeathEvent**
		- Clase *GameManager*, linea 94
	- **LevelResetEvent**
		- Clase *Timer*, linea 85
	- **ArriveNewZoneEvent**
		- Clase *Checkpoint*, linea 24
	- **StartLevelEvent**
		- Clase *FinalDeNivel*, linea 30
	- **ReceiveDamageEvent**
		- Clase *DanhoAlJugadorObstaculos*, linea 15
		- Clase *DanhoAlJugador*, linea 14
	- **ThrowHookEvent**
		- Clase *CrearGancho*, linea 75
	- **HitHookEvent**
		- Clase *Gancho*, linea 65
	- **LandingEvent**
		- Clase *Suelo*, linea 26

# Estructura de proyecto

* **Gung_Cho_Build:** Build del juego, genera trazas en la carpeta *'Gung_Cho_Data/telemetry_data/'*
* **Gung_Cho_Telemetry:** Proyecto de Unity, dónde está la **instrumentalización**. En la carpeta *'Telemetry'* está el código del **sistema de telemetría**.
* **Gung_Cho_Telemetry_Data_Example:** Ejemplos de trazas generadas. 

## Partes Opcionales
* Serialización y persistencia en una hebra independiente de la del videojuego.
* Añadir al menos otro medio de serialización, configurable desde código **[CSV, Binario]**.