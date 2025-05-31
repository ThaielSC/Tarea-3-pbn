# ICC3102 Programación de Bajo Nivel 2025-10: Tarea 3 

**Programación Orientada a Objetos** 
**Entrega**: viernes 30 de mayo a las 21:00 hrs. 

## 1. Introducción

En esta tarea se solicita desarrollar en C++ una aplicación por consola que simule una mazmorra al estilo The Legend of Zelda, enfocada exclusivamente en la exploración de mazmorras y el uso de habilidades especiales de Link. El juego debe funcionar por turnos, mostrar el estado del mapa en cada paso, manejar enemigos con patrones de movimiento y presentar una sala final con el jefe.

## 2. Objetivo

Desarrollar un programa en C++ orientado a objetos que:

* Cargue desde el archivo CSV "mazmorras.csv" el mapa de mazmorra principal ($N \times M$) y la sala del jefe ($I \times J$).
* Cargue desde el archivo CSV "enemigos.csv" la información de enemigos y jefe (coordenadas, patrón de movimiento, vida, daño, rango de ataque, frecuencia de ataque y patrones de movimiento).
* Permita al jugador (Link) moverse y girar, atacar y usar habilidades según la dirección a la que apunta.
* Gestione el turno de enemigos y jefe, mostrando estados especiales temporales.
* Termine el juego al derrotar al jefe y tocar la pieza de corazón o si Link muere.

Los detalles de estos requisitos se entregan a continuación.

## 3. Descripción de la Tarea

Su programa deberá utilizar correctamente los conceptos de la programación orientada a objetos y el poseer un buen funcionamiento de todas las mecánicas, según se especifica en los requisitos de este enunciado.

### 3.1. Estructura General Del Juego

* El mapa se representa con una matriz de caracteres cargada desde `mazmorra.csv`, en ella se encuentran todos los enemigos, cofres, puertas e incluso el punto de inicio del jugador (Link).
* La sala del jefe se representa con otra matriz cargada desde el mismo csv, con la misma nomenclatura.
* El archivo `mazmorra.csv` contiene una mazmorra en cada línea del archivo, con cada elemento separado por una coma sin espacios:
    Filas (eje Y), columnas (eje X), [mapa de caracteres de la mazmorra y sus elementos comenzando desde la esquina superior izquierda], filas sala del jefe, columnas sala del jefe, [mapa de caracteres de la sala del jefe y sus elementos].
* Aquí un ejemplo de una de las líneas que podría tener `mazmorra.csv` (para la leyenda con el significado de cada elemento, véase más adelante en este mismo enunciado):
    `10,10, ,X,X,X,X, ,X,X,X,X,L, ,-,-,-,-,-,C, ,X,X,X,X,X,X,P,X,X,X,X,X, , ,K,X,-,-, ,X,X,-,,-,X, ,X,X,,,,,,X,X,-,X,E,-,-,-,,-,X,X,X,X, ,-,X,X,X,X,X, ,X, ,C,X,X,X,Y,X,X,X,X,X,X,X,X,X,X,X,6,4,X,X,X,X,X,L,-,X,X, ,-,X,X, ,J,X,X,-,-,X,X,X,X,X` 
* El archivo `enemigos.csv`, por su parte, contiene los enemigos de cada mazmorra por línea, separados por comas y sin espacios. Nunca ocurrirá que dos enemigos estén en la misma posición o que alguno pueda moverse en una casilla ocupada por otro elemento.
    * Para cada enemigo: y enemigo, x enemigo, número de movimientos, [lista de coordenadas relativas a la coordenada de origen del enemigo, siempre termina en (0,0), pero también puede incluirlo entre medio], vida, daño, rango de ataque (rango cuadrado, si es 3, entonces es rango $3 \times 3$ con el enemigo como centro, si es 1 solo ataca si el jugador está a su lado) y frecuencia de ataque (en turnos).
    * Para el jefe: Nombre del jefe, y jefe, x jefe, número de movimientos, [lista de coordenadas relativas a la coordenada de origen del jefe, siempre termina en 0,0, pero puede incluirlo entre medio], vida, daño, rango de ataque (rango cuadrado, si es 3, entonces es rango $3 \times 3$ con el jefe como centro, si es 1 solo ataca si el jugador está a su lado) y frecuencia de ataque (en turnos).
    * Para enemigos en la sala del jefe (van después de los datos del jefe): y enemigo, x enemigo, número de movimientos, [lista de coordenadas relativas a la coordenada de origen del enemigo, siempre termina en (0,0), pero puede incluirlo entre medio], vida, daño, rango de ataque (rango cuadrado, si es 3, entonces es rango $3 \times 3$ con el enemigo como centro, si es 1 solo ataca si el jugador está a su lado) y frecuencia de ataque (en turnos).
* Aquí un ejemplo de cómo está compuesto el csv para la mazmorra anteriormente usada de ejemplo:
    `3,3,4,1,0,0,0,0,-1,0,0,20,10,3,3,7,3,6,0,1,0,2,0,3,0,2,0,1,0,0,20,25,3,3,lizalfo,3,2,4,1,0,1,-1,0,-1,0,0,110,10,3,3` 

### 3.2. Clases Propuestas

A continuación se propone una estructura de clases recomendada para realizar la tarea, pero no es obligación seguir la misma estructura:

* **Jugador** (`int x`, `int y`, `int vida`, `int daño`, `int rango`, `std::string habilidad`, `std::string direccion`, `bool recibiendoDaño`, `int llaves`, `int llavesJefe`, `int pasos`, `int cofresAbiertos`, `int puertasAbiertas`, `int EnemigosDerrotados`, `int numBombas`, `bool usandoHabilidad`, `bool atacando`, `bool enSalaJefe`, `bool haGanado`): Representa al héroe Link.
    * Por defecto tiene 100 de vida, 20 de daño, rango 1 y coordenadas de inicio equivalentes a las que se extraen desde el mapa de la mazmorra.
    * Gestiona un inventario ligero: Llaves, bombas (inicia con 3), cofres abiertos, etc..
    * La dirección a la que apunta determina el rango de sus habilidades.
    * Se deben crear métodos para gestionar las acciones principales, acceder y modificar sus atributos privados y tener acceso a otras clases como enemigos o la mazmorra según sea necesario.

* **Enemigo** (`int x`, `int y`, `int vida`, `int daño`, `int rango`, `int frecuenciaAtaque`, `std::vector<std::pair<int, int>> patronMovimiento`, `int pasoActual`, `bool atacando`, `int xOriginal`, `int yOriginal`, `bool recibiendoDaño`, `int turnosDesdeUltimoAtaque`): Representa a un enemigo básico de la mazmorra.
    * Por defecto sigue un patrón de movimiento predefinido que se repite en ciclos, siempre termina en la posición original, las coordenadas del patrón de movimiento se calculan tomando como origen las coordenadas originales del enemigo.
    * Se mueve hacia la posición siguiente en cada turno, al llegar a la última, vuelve a recorrer el patrón de movimiento.
    * Si ataca, o el jugador está en su rango de visión, no se mueve y se prepara para atacar.
    * O ataca o se mueve, la frecuencia de ataque se mide en número de turnos.
    * Se deben crear métodos para ejecutar sus acciones, acceder y modificar sus atributos.

* **Boss** (`int x`, `int y`, `int vida`, `int daño`, `int rango`, `int frecuenciaAtaque`, `std::string nombreJefe`, `std::vector<std::pair<int, int>> patronMovimiento`, `int pasoActual`, `bool atacando`, `int xOriginal`, `int yOriginal`, `bool recibiendoDaño`, `int turnosDesdeUltimoAtaque`): Representa al jefe de la sala especial dentro de la mazmorra.
    * Tiene un nombre identificador y un patrón de movimiento predefinido que siempre parte desde su posición original.
    * Su comportamiento es idéntico al de un enemigo común, pero con estadísticas superiores y un nombre.
    * Se mueve siguiendo un patrón cíclico, pero se detiene si va a atacar o si detecta al jugador en su rango.
    * Solo puede moverse o atacar en un mismo turno, respetando su frecuencia de ataque.
    * Se deben crear métodos para ejecutar sus acciones especiales, acceder o modificar sus atributos privados y coordinarse con la sala del jefe y la posición del jugador.

* **Mazmorra** (`int filas`, `int columnas`, `std::vector<std::vector<char>> mapa`, `std::vector<Enemigos> enemigos`): Representa una sala normal del juego con un mapa 2D. *(Note: `Enemigos` should likely be `Enemigo` as per class name conventions elsewhere)*
    * Cada celda del mapa contiene un carácter que representa el tipo de elemento (pared, suelo, puerta, etc.).
    * La mazmorra gestiona una lista de enemigos que pueden ser agregados o eliminados dinámicamente.
    * Se encarga de mostrar el mapa con los cambios de símbolos y actualizando la posición de los enemigos y el jugador.
    * Provee métodos para acceder y modificar elementos del mapa, obtener dimensiones, consultar enemigos y detectar si se trata de una sala especial (como la sala del jefe).
    * Se deben crear métodos para interactuar con el mapa, coordinar la lógica del combate y facilitar la gestión de enemigos u otros eventos internos.

* **SalaJefe** (`int filas`, `int columnas`, `std::vector<std::vector<char>> mapa`, `std::vector<Enemy> enemigos`, `Jefe jefe`, `std::pair<int, int> posicionEntradaJefe`): Representa una sala especial del juego estructuralmente idéntica a la clase Mazmorra, pero con funciones adicionales para gestionar el jefe final. *(Note: `Enemy` should likely be `Enemigo`)*
    * Contiene un mapa 2D, una lista de enemigos y un jefe (de la clase Jefe) con su lógica particular.
    * Además de los métodos típicos para mostrar/modificar el mapa y gestionar enemigos, permite acceder y modificar el jefe para manejarlo dinámicamente.

* **Otros** (): Contiene las funciones para cargar y parsear datos desde CSV.
    * Se encarga de almacenar los datos crudos que representan las mazmorras, los enemigos y los jefes del juego.
    * Permite guardar esta información y proporciona métodos para acceder a ella de forma estructurada.
    * No contiene lógica de juego ni manipulación directa de los elementos, solo actúa como repositorio de datos iniciales para organizar mejor las responsabilidades de cada clase.

* **Juego** (`std::string dungeonsPath`, `std::string enemiesPath`): Clase con el loop principal del juego.
    * Carga las mazmorras (Dungeon) y enemigos desde archivos CSV utilizando información cargada desde la clase Otros.
    * Permite al jugador elegir una mazmorra y una habilidad inicial antes de poder jugar, es decir, debe mostrar todas las mazmorras y los datos de sus enemigos al iniciar el programa.
    * El juego se gestiona turno a turno, procesando el mapa, los enemigos, al jugador y sus acciones.
    * Sus atributos clave son:
        * `dungeons`: Vector con los datos brutos de todas las mazmorras.
        * `enemies`: Vector con los datos brutos de los enemigos.
        * `mazmorra` y `sala.Jefe`: Instancias dinámicas para representar cada tipo de sala. *(Note: `sala.Jefe` might be a typo in PDF, perhaps `salaJefe`)*
        * `usandoSalaJefe`: Flag que permite distinguir si el jugador está en la sala del jefe o no.
        * `link`: El jugador.
        * `seleccionMazmorra`: Índice de la mazmorra actual seleccionada, también sirve para coordinar los enemigos de la mazmorra.

Finalmente se proporcionan los detalles sobre las habilidades del jugador:

1.  **Salto**: Mueve a Link dos casillas en línea recta en la dirección apuntada. No atraviesa muros; si hay un obstáculo a dos casillas, no se mueve y "pierde el turno".
2.  **Escudo**: Bloquea un ataque que provenga desde la dirección opuesta a la apuntada.
3.  **Arco**: Dispara una flecha que golpea en una zona cuadrada de $5 \times 5$ situada, solo afecta a las casillas visibles en la dirección apuntada por el jugador. Cada enemigo alcanzado recibe 10 puntos de daño. No llega a los enemigos si hay un obstáculo en el camino.
4.  **Bomba**: Permite romper un muro adyacente en la dirección apuntada, por simplicidad, se activa al instante en la casilla del jugador. También puede causar 100 puntos de daño en las ocho casillas circundantes (radio $3 \times 3$ alrededor de Link) si hay un enemigo en la casilla directamente adyacente. No se puede usar más de 3 veces por mazmorra.
5.  **Gancho**: Permite mover a Link hacia la casilla anterior de un muro 'X' o cofre 'C'/'K' en línea recta, si encuentra un enemigo le hace 5 de daño y no mueve a Link.

* Modo de uso de una habilidad:
    1.  El jugador selecciona la habilidad para la mazmorra seleccionada.
    2.  Al presionar 'Z', invoca el método correspondiente a la habilidad.
    3.  El efecto se aplica sobre el mapa y las entidades involucradas.
    4.  Se actualiza el icono de Link (cambiar 'L' por 'Z' durante el turno donde usó la habilidad.

### 3.3. Nomenclatura Del Mapa

*(Note: The full list of map symbols provided on page 6 of the PDF is not entirely covered by explicit source tags in the input. Only symbols whose definitions are citable from the provided source blocks are listed below.)*

* 'Z': Link usando habilidad. (Contextually, 'L' would represent Link in a normal state).
* '$': Entidad (enemigo, jefe o Link) recibiendo daño. (This symbol has higher priority than 'A' if an enemy suffers damage and attacks in the same turn ).
* 'V': Pieza de corazón tras vencer al jefe.
* 'E': Representa un enemigo (derived from descriptions of enemies in CSV  and Mazmorra class [cite: 36, 38]).
* 'J': Representa al jefe (derived from descriptions of the boss in CSV  and SalaJefe class [cite: 42, 43]).
* 'X': Muro (Context from Bomba ability  and Gancho ability ).
* 'C', 'K': Cofres que pueden contener llaves (Context from Gancho ability  and Jugador inventory ). 'K' specifically is a cofre con llave del jefe.
* 'Y': Puerta del jefe (requiere llave del jefe).
* 'P': Puerta normal (requiere llave) (Context from Jugador inventory  and Mazmorra elements ).

### 3.4. Sistema De Turnos

* Cada acción del jugador (mover, girar, atacar, usar habilidad) consume un turno.
* En cada turno, todos los enemigos actualizan su posición o atacan tras transcurrir cierto número de turnos, según su frecuencia de ataque. Un enemigo no puede moverse si la siguiente casilla está ocupada por el jugador.
* El sistema de combate es sencillo, los enemigos sufren daño en el turno siguiente a la acción del jugador, y el jugador sufre daño si está dentro del rango de ataque de un enemigo y el número de turnos dentro de su rango de visión corresponde al turno de ataque de ese enemigo.
* El icono de daño '\$' posee mayor prioridad que cualquier otro, es decir, si un enemigo sufre daño en el mismo turno donde ataca, debe mostrarse '\$', no 'A'.
* Los íconos temporales en enemigos o el jugador, sólo duran 1 turno.
* Para entender mejor esto se proporcionará un ejecutable para probar lo que se espera que logre hacer el programa completo.

### 3.5. Movimiento Y Comandos

Los comandos del jugador se pueden leer con `std::cin` y leyendo únicamente el primer carácter ingresado.

* `w` = girar/mover arriba.
* `s` = girar/mover abajo.
* `a` = girar/mover izquierda.
* `d` = girar/mover derecha.
* `x` = atacar con la espada (a una casilla adelante, 10 de daño).
* `z` = usar habilidad especial.
* `c` = interactuar (abrir puertas o cofres una casilla adelante).
* `p` = salir del juego.
* Nota: si se presiona una dirección distinta a la actual, solo gira: moverse en una dirección distinta toma 2 turnos.

### 3.6. Condiciones De Victoria Y Detalles

* Para entrar en la sala del jefe (Y), Link debe tener la llave del jefe.
* Tras derrotar al jefe, aparece V; al tocarlo, el juego finaliza con victoria.
* Link muere si su vida llega a 0, en ese caso el juego termina y muestra las estadísticas finales.
* Por temas de balance, al derrotar a un enemigo este desaparece del mapa y Link recupera 20 de vida.
* Link no puede salir de los límites del mapa.

### 3.7. Mensaje De Salida

Al completar el juego (victoria o derrota), mostrar en consola:

* Cofres abiertos.
* Puertas abiertas.
* Enemigos derrotados.
* Pasos recorridos.

## 4. Recomendaciones

* Recuerde que su tarea será evaluada por funcionalidades. Esto tiene dos implicancias prácticas importantes: 1) más vale una tarea en que funcionan la mitad de las cosas que una que está a punto de funcionar pero no compila, y 2) antes de desesperarse o bloquearse, divida la tarea en funcionalidades e impleméntelas una a una de manera de ir asegurando puntaje.
* Comience el desarrollo con anticipación. Es muy probable que en el camino encuentre problemas que requieran tiempo para pensar o discutir con el profesor o los ayudantes.
* Se recomienda comenzar leyendo correctamente los archivos csv, luego crear las clases principales y enfocarse en el jugador y ciclo de juego. Dejar para el final las habilidades y el patrón de movimiento de los enemigos.

## 5. Consideraciones Generales Sobre La Evaluación

En cada ítem se reservará una parte del puntaje para el intento de la implementación, y otra enfocada en el funcionamiento durante la ejecución. Recuerde que está prohibido usar materia no vista en clases, salvo que se autorice explícitamente lo contrario. Esta tarea debe ser realizada en lenguaje C++, debe incluir los archivos .h y .cpp de cada clase necesaria, además del main.cpp e incluir un archivo Makefile para poder compilar toda la entrega. Su programa debe ser robusto frente a datos que no corresponden. Esto quiere decir que su programa no debe caerse en caso de que el usuario haga operaciones matemáticas no válidas (p.ej., jugadas inválidas, coordenadas inexistentes, etc.). Sin embargo, pueden asumir que el usuario será amigable, en el sentido de que cuando le soliciten un número este no ingresará letras, por ejemplo.

## 6. Desarrollo, Compilación y Entrega

Esta tarea puede ser resuelta en grupos de máximo 2 personas. El plazo para la entrega de la tarea vence impostergablemente el viernes 30 de mayo a las 21:00 hrs. Cuide sus tareas para que no sean copiadas parcial o íntegramente por otros. Todas las tareas entregadas serán comparadas por un sistema automático de detección de plagio. Cualquier sospecha de copia (de otras tareas o de internet) podrá ser denunciada, investigada y eventualmente penalizada de conformidad al Reglamento del Alumno.
Formato de entrega: Subir un solo archivo comprimido con todo el código fuente de su programa al módulo de tareas de la página del curso, con el nombre de archivo `"APELLIDO1-APELLIDO2-Tarea3.tar.gz"` el cual deberá contener los archivos de código fuente en C++ (archivos `.cpp` y `.hpp`) y el `Makefile`, reemplazando los apellidos según corresponda (ej. AONUMA-MIYAMOTO-Tarea3.tar.gz). Los archivos compilados no serán tomados en cuenta, si se llega a subir solo un archivo compilado, este será ignorado, y será evaluado con nota 1.

Junto a los archivos de código base, debe venir incluido un archivo `Makefile` el cual permita realizar la compilación de manera automática con el comando `make`, este debe incluir las siguientes flags:
`-Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self` 

Al compilar se debe generar un ejecutable llamado `"tarea3"`. Si este paso falla y se debe realizar la compilación de forma manual, o el ejecutable no se llama como se indica se procederá a descontar 1 punto de la nota obtenida. Aquellas tareas que no compilen con el comando `make` serán evaluadas con nota 1.

Su programa será evaluado con múltiples casos de prueba y deberá ser capaz de ejecutarlos todos de manera correcta. De fallar en algún caso de prueba serán descontados los puntos correspondientes a dicho caso.
