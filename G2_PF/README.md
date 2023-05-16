## Que es
Ianium es una herramienta que facilita la realización de tests de unidad para una interfaz de usuario en SDL2. Proporcionando a los usuarios varias interfaces de código para la creación de elementos clásicos pertenecientes a una UI (como botones, sliders o toggles). Ianium es capaz de realizar una serie de tests a petición del usuario para asegurar su funcionamiento a través de la lectura de un script con terminación .ia escrito en un lenguaje concreto que será interpretado. Los elementos de la interfaz serán sometidos a las distintas pruebas dictadas en el archivo, y se generará un archivo de salida “.iaout” en el que estará explicado de manera detallada qué tests han terminado exitosamente y cuáles han encontrado algún tipo de error, estos últimos con detalles de qué test ha generado el error y por qué motivo.

Para más información sobre la estructura de clases a seguir, consultar el proyecto ejemplo "test_sdl" o [la memoria del proyecto](https://docs.google.com/document/d/1fGLfiWiWpbZlCSRJFyDYRxK_tCla1uQhhHJsEO_23l0/edit?usp=sharing)

## Compilación automatica
- Mover/copiar las carpetas *example/assets/* y *example/scripts/* a la carpeta *test_sdl/*, y luego ejecutar el archivo build.bat utilizando **Visual Studio 2022 Developer Command Prompt**. Abrir test_sdl.sln, y ejecutar una vez.
- En *example/output/* se puede ver un ejemplo de salida.

## API
Soporta varios tipos de instrucciones con formato nombreDeInstrucción parámetro1 parámetro2...:

 - click x y 
    - x,y son int que indican la posición en pantalla en formato de coordenadas SDL (la esquina superior izquierda es el 0,0)
 - clickElem tipoElemento id
    - tipoElemento es un int puede tener los valores {BUTTON = 0, TOGGLE = 1, SLIDER = 2}
    - id es el int especificado como id al crear un UIElement.
 - releaseClick x y
 - mouseMotion x y
 - assertButton id estado
    - estado puede tener valores { PRESSED = 0, HOLD = 1, RELEASED = 2 }.
 - assertToggle  id estado)
    - estado puede tener valores {ON = distinto de 0, OFF = 0}
 - assertSlider id valor
    - Valor puede tener valores decimales [0,1]
 - assertImageOnScreen imagePath
    - imagePath es un string de la imagen que se quiere buscar en pantalla
 - runFrames frames
    - frames es un int del número de frames que se quieren ejecutar. Típicamente con darle valor 1 sirve.

## Requisitos
- SDL tiene que ser inicializado previamente.
- Se debe inicializar Ianium, haciendo Ianium::Init
- Para ejecutar los tests, se debe llamar a Ianium::Instance()->runTests()
- runFrames debe llamarse cada vez que se quiere que se procese una instruccion. Si se quiere que en el mismo frame se ejecuten varios clicks por ejemplo, se llamara a click las veces necesarias, y luego a "runFrames 1" para reflejar estas acciones en la interfaz.
