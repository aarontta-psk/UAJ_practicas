## Que es
Ianium es un entorno de pruebas...
## API
Soporta varios tipos de instruccion;

 - Click(x,y)
 - AssertButton(int id, int estado) 
    - Estado puede tener valores { PRESSED = 0, HOLD = 1, RELEASED = 2 }.
 - AssertToggle(int id, int estado)
    - Estado puede tener valores {ON = distinto de 0, OFF = 0}
 - AssertSlider(int id, int valor)
    - Valor puede tener valores decimales [0,1]
   
## Requesitos
