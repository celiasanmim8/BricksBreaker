#include "arkanoPi.h"



int flags = 0;



TipoSistema sistema;



// Declaracion del objeto teclado

TipoTeclado teclado = {

           .columnas = {

                       // A completar por el alumno...

                       // ...

           },

           .filas = {

                       // A completar por el alumno...

                       // ...

           },

           .rutinas_ISR = {

                       // A completar por el alumno...

                       // ...

           },



           // A completar por el alumno...

           // ...

};



// Declaracion del objeto display

TipoLedDisplay led_display = {

           .pines_control_columnas = {

        		 GPIO_LED_DISPLAY_COL_1,

				 GPIO_LED_DISPLAY_COL_2,

				 GPIO_LED_DISPLAY_COL_3,

           },

           .filas = {

        		   GPIO_LED_DISPLAY_ROW_1,

				   GPIO_LED_DISPLAY_ROW_2,

				   GPIO_LED_DISPLAY_ROW_3,

				   GPIO_LED_DISPLAY_ROW_4,

				   GPIO_LED_DISPLAY_ROW_5,

				   GPIO_LED_DISPLAY_ROW_6,

				   GPIO_LED_DISPLAY_ROW_7,

           },

           // A completar por el alumno...

           // ...

};



//------------------------------------------------------



//------------------------------------------------------



// int ConfiguracionSistema (TipoSistema *p_sistema): procedimiento de configuracion

// e inicializacion del sistema.

// Realizará, entra otras, todas las operaciones necesarias para:

// configurar el uso de posibles librerías (e.g. Wiring Pi),

// configurar las interrupciones externas asociadas a los pines GPIO,

// configurar las interrupciones periódicas y sus correspondientes temporizadores,

// la inicializacion de los diferentes elementos de los que consta nuestro sistema,

// crear, si fuese necesario, los threads adicionales que pueda requerir el sistema

// como el thread de exploración del teclado del PC

int ConfiguraInicializaSistema (TipoSistema *p_sistema) {



           int result = 0;

           wiringPiSetupGpio ();


           p_sistema -> arkanoPi.p_pantalla = ( & led_display.pantalla);

           p_sistema -> arkanoPi.tmr_actualizacion_juego = tmr_new ( tmr_actualizacion_juego_isr );



           // Lanzamos thread para exploracion del teclado convencional del PC

           //result = piThreadCreate (thread_explora_teclado_PC);


           InicializaTeclado ( & teclado );

           InicializaLedDisplay ( & led_display );



           return result;

}



//------------------------------------------------------

// FUNCIONES LIGADAS A THREADS ADICIONALES

//------------------------------------------------------



PI_THREAD (thread_explora_teclado_PC) {

           int teclaPulsada;



           while(1) {

                       delay(10); // Wiring Pi function: pauses program execution for at least 10 ms



                       piLock (STD_IO_BUFFER_KEY);



                       if(kbhit()) {

                                  teclaPulsada = kbread();



                                  switch(teclaPulsada) {

                                             case 'a': //modificado

                                                         piLock (SYSTEM_FLAGS_KEY);

                                                         flags |= FLAG_MOV_IZQUIERDA;

                                                         piUnlock (SYSTEM_FLAGS_KEY);

                                                         break;



                                             case 'd': //modificado

                                                         piLock (SYSTEM_FLAGS_KEY);

                                                         flags |=FLAG_MOV_DERECHA;

                                                         piUnlock (SYSTEM_FLAGS_KEY);

                                                         break;



                                             case 'c': //modificado

                                                         piLock (SYSTEM_FLAGS_KEY);

                                                         flags |=FLAG_TIMER_JUEGO;

                                                         piUnlock (SYSTEM_FLAGS_KEY);

                                                         break;



                                             case 's':

                                                         printf("Tecla S pulsada!\n");

                                                         fflush(stdout);

                                                         break;



                                             case 'q':

                                                         exit(0);

                                                         break;



                                             default:

                                                         printf("INVALID KEY!!!\n");

                                                         break;

                                  }

                       }



                       piUnlock (STD_IO_BUFFER_KEY);

           }

}



// wait until next_activation (absolute time)

void delay_until (unsigned int next) {

           unsigned int now = millis();

           if (next > now) {

                       delay (next - now);

           }

}



int main () {


           unsigned int next;


           // Maquina de estados: lista de transiciones

           // {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }

           //hemos añadido dos estados: el estado que nos va a permitir elegir la dificultad del juego
           	   //y el estado que nos permite detener y reanudar el juego

           fsm_trans_t arkanoPi[] = {

        		   	   { WAIT_DIFICULTAD, CompruebaDificultadFacil, WAIT_START, ActualizarDificultadFacil },

        		   	   { WAIT_DIFICULTAD, CompruebaDificultadMedia, WAIT_START, ActualizarDificultadMedia },

        		   	   { WAIT_DIFICULTAD, CompruebaDificultadDificil, WAIT_START, ActualizarDificultadDificil },

					   { WAIT_DIFICULTAD, CompruebaDificultadIncremental, WAIT_START, ActualizarDificultadIncremental },

					   { WAIT_PUSH, CompruebaBotonDificultad, WAIT_PUSH, ActualizarBotonDificultad },

                       { WAIT_START, CompruebaBotonPulsado, WAIT_PUSH, InicializaJuego },

					   { WAIT_PUSH, CompruebaPausarJuego, WAIT_PAUSAR, PausarJuego },

					   { WAIT_PAUSAR, CompruebaReanudarJuego, WAIT_PUSH, ReanudarJuego},

                       { WAIT_PUSH, CompruebaTimeoutActualizacionJuego, WAIT_PUSH, ActualizarJuego },

                       { WAIT_PUSH, CompruebaMovimientoIzquierda, WAIT_PUSH, MuevePalaIzquierda },

                       { WAIT_PUSH, CompruebaMovimientoDerecha, WAIT_PUSH, MuevePalaDerecha },

					   { WAIT_PUSH, CompruebaMovimientoArriba, WAIT_PUSH, MuevePalaArriba },

					   { WAIT_PUSH, CompruebaMovimientoAbajo, WAIT_PUSH, MuevePalaAbajo },

                       { WAIT_PUSH, CompruebaFinalJuego, WAIT_END, FinalJuego },

                       { WAIT_END,  CompruebaBotonPulsado, WAIT_START, ReseteaJuego },

					   {-1, NULL, -1, NULL },

           };



           // Configuracion e incializacion del sistema




           ConfiguraInicializaSistema ( & sistema );





           fsm_t* arkanoPi_fsm = fsm_new ( WAIT_DIFICULTAD, arkanoPi, & sistema.arkanoPi );


           fsm_t* teclado_fsm = fsm_new ( TECLADO_ESPERA_COLUMNA, fsm_trans_excitacion_columnas, & (teclado) );


           fsm_t* tecla_fsm = fsm_new (TECLADO_ESPERA_TECLA, fsm_trans_deteccion_pulsaciones, & (teclado) );


           fsm_t* led_fsm = fsm_new ( DISPLAY_ESPERA_COLUMNA, fsm_trans_excitacion_display, & (led_display) );



           //sistema.arkanoPi.p_pantalla = &(led_display.pantalla);




           next = millis();

           //explicamos el funcionamiento del juego: cómo se mueve la pala y cómo se para juego.
           	   //tambien damos a escoger la velocidad que el usuario quiera
           printf ("\n");

                               	printf ("\n¡¡BIENVENIDO!! Este es el funcionamiento del juego:");

                               	printf ("\nTecla A : Pala izquierda");

                               	printf ("\nTecla F : Pala derecha");

                               	printf ("\nTecla E: Pala arriba");

                               	printf ("\nTecla D: Pala abajo");

                               	printf ("\nTecla B : Cambiar velocidad");

                               	printf ("\nTecla 1: Parar juego definitivamente");

                               	printf ("\nY ahora para empezar esccoja la dificultad...");

                               	printf ("\nTecla 3: Modo Facil");

                               	printf ("\nTecla 4: Modo Medio");

                           		printf ("\nTecla 5: Modo Dificil");

                           		printf ("\nTecla 6: Modo Incremental");

                           		printf ("\nY pulse la tecla C para iniciar el juego");

                           		fflush(stdout);

           printf ("\n");



           while (1) {

                       fsm_fire (arkanoPi_fsm);


                       fsm_fire (teclado_fsm);


                       fsm_fire (tecla_fsm);


                       fsm_fire (led_fsm);


                       next += CLK_MS;


                       delay_until (next);

           }


           fsm_destroy (arkanoPi_fsm);

           fsm_destroy (teclado_fsm);

           fsm_destroy (tecla_fsm);

           fsm_destroy (led_fsm);





}



