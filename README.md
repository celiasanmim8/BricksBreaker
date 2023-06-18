# BricksBreaker
>Clásico juego de destruir los ladrillos con una pelota.
- Desarrollo basado en herramientas y sistemas de microcontroladores, una raspberry pi, que permite realizar un caso real de diseño de un juego que consiste en controlar una pequeña pala con su pelota que rebota en ladrillos y al ser tocados desaparecen.  Una vez desaparecidos todos los ladrillos, el jugador es el ganador.  Por otro lado, el caso opuesto sería cuando la pelota lo logra alcanzar la pala y desaparece por la parte inferior de la pantalla.

- A modo de manual de usuario:
  - Inicializar el proyecto, donde se desplegará un menú sencillo dando la bienvenida y con un breve esquema de las teclas que se deben pulsar y además los niveles de dificultad que se quiere aventurar.
  - Una vez estudiadas las posiciones de las teclas, elegir el nivel de dificultad deseado, y una vez seleccionado, el juego se iniciará pulsando C, donde ya se pondrá en marcha el juego para su diversión. 
  - Finalmente, cuando el jugador ha perdido, o se ha rendido, aparecerá un menú en pantalla con el mensaje de “Ha obtenido x puntos en la partida” que será igual al número de ladrillos derribados.
 - Teclas:
   - Movimiento: en la pantalla misma nos explican a que pertenece cada una. Si se pulsa la tecla A, la pala se moverá hacia la izquierda, para ir al sentido contrario, es decir, hacia la derecha debemos pulsar la tecla F. El movimiento de la pala para que también sea vertical, pulsando la E irá hacia arriba y la D hacia abajo.
   - Stop-Play: permiten parar y reanudar el juego cuando se desee. Para la opción de parar es necesario pulsar el 1, y para su opuesto, la continuación, el 2. Estas acciones abrirán un menú de juego pausado.
 - Extisten 3 niveles de dificultad que van en concordancia con la velocidad de la pelota: fácil, media, difícil e incremental
    - Si se pulsa el 3, se elige el nivel más fácil, el de menor velocidad.
    - El 5 es para nivel difícil.
    - El 6 para incrementar la velocidad de la pelota cada vez que se destruya un ladrillo.
    - La tecla B salta de una velocidad a otra, es decir, dependiendo de la dificultad inicial escogida, va a ir a la siguiente, de modo fácil a difícil y vuelve a fácil y viceversa.
