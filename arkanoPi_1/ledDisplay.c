#include "ledDisplay.h"



tipo_pantalla pantalla_inicial = {

           .matriz = {

           {0,0,0,0,0,0,0,0},

           {0,1,1,0,1,0,0,0},

           {0,1,1,0,0,1,0,0},

           {0,0,0,0,0,1,0,0},

           {0,0,0,0,0,1,0,0},

           {0,1,1,0,0,1,0,0},

           {0,1,1,0,1,0,0,0},

           }

};



tipo_pantalla pantalla_final = {

           .matriz = {

           {0,0,0,0,0,0,0,0},

           {0,0,1,0,0,1,0,0},

           {0,1,1,0,1,0,0,0},

           {0,0,0,0,1,0,0,0},

           {0,0,0,0,1,0,0,0},

           {0,1,1,0,1,0,0,0},

           {0,0,1,0,0,1,0,0},

           }

};



// Maquina de estados: lista de transiciones

// {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }

fsm_trans_t fsm_trans_excitacion_display[] = {

           { DISPLAY_ESPERA_COLUMNA, CompruebaTimeoutColumnaDisplay, DISPLAY_ESPERA_COLUMNA, ActualizaExcitacionDisplay },

           {-1, NULL, -1, NULL },

};



//------------------------------------------------------

// PROCEDIMIENTOS DE INICIALIZACION DE LOS OBJETOS ESPECIFICOS

//------------------------------------------------------



void InicializaLedDisplay (TipoLedDisplay *led_display) {

           pinMode (GPIO_LED_DISPLAY_COL_1, OUTPUT);

           pinMode (GPIO_LED_DISPLAY_COL_2, OUTPUT);

           pinMode (GPIO_LED_DISPLAY_COL_3, OUTPUT);

           pinMode (GPIO_LED_DISPLAY_ROW_1, OUTPUT);

           pinMode (GPIO_LED_DISPLAY_ROW_2, OUTPUT);

           pinMode (GPIO_LED_DISPLAY_ROW_3, OUTPUT);

           pinMode (GPIO_LED_DISPLAY_ROW_4, OUTPUT);

           pinMode (GPIO_LED_DISPLAY_ROW_5, OUTPUT);

           pinMode (GPIO_LED_DISPLAY_ROW_6, OUTPUT);

           pinMode (GPIO_LED_DISPLAY_ROW_7, OUTPUT);

           ApagaFilas (led_display);


           digitalWrite (GPIO_LED_DISPLAY_COL_1, LOW);

           digitalWrite (GPIO_LED_DISPLAY_COL_2, LOW);

           digitalWrite (GPIO_LED_DISPLAY_COL_3, LOW);




           led_display -> flags = 0;

           led_display -> p_columna = 0;



           led_display -> tmr_refresco_display = tmr_new (timer_refresco_display_isr);

           tmr_startms ((tmr_t*)(led_display -> tmr_refresco_display), TIMEOUT_COLUMNA_DISPLAY);

}



//------------------------------------------------------

// OTROS PROCEDIMIENTOS PROPIOS DE LA LIBRERIA

//------------------------------------------------------



void ApagaFilas (TipoLedDisplay *led_display){

           digitalWrite (GPIO_LED_DISPLAY_ROW_1, HIGH);

           digitalWrite (GPIO_LED_DISPLAY_ROW_2, HIGH);

           digitalWrite (GPIO_LED_DISPLAY_ROW_3, HIGH);

           digitalWrite (GPIO_LED_DISPLAY_ROW_4, HIGH);

           digitalWrite (GPIO_LED_DISPLAY_ROW_5, HIGH);

           digitalWrite (GPIO_LED_DISPLAY_ROW_6, HIGH);

           digitalWrite (GPIO_LED_DISPLAY_ROW_7, HIGH);

}



void ExcitaColumnas(int columna) {



           switch(columna) {

           	   	   	   case 0:

                             	 digitalWrite (GPIO_LED_DISPLAY_COL_1, LOW);

                                 digitalWrite (GPIO_LED_DISPLAY_COL_2, LOW);

                                 digitalWrite (GPIO_LED_DISPLAY_COL_3, LOW);

                                 break;

           	   	   	   case 1:

                                  digitalWrite (GPIO_LED_DISPLAY_COL_1, HIGH);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_2, LOW);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_3, LOW);

                                  break;



                       case 2:

                                  digitalWrite (GPIO_LED_DISPLAY_COL_1, LOW);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_2, HIGH);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_3, LOW);

                                  break;



                       case 3:

                                  digitalWrite (GPIO_LED_DISPLAY_COL_1, HIGH);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_2, HIGH);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_3, LOW);

                                  break;



                       case 4:

                                  digitalWrite (GPIO_LED_DISPLAY_COL_1, LOW);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_2, LOW);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_3, HIGH);

                                  break;



                       case 5:

                                  digitalWrite (GPIO_LED_DISPLAY_COL_1, HIGH);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_2, LOW);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_3, HIGH);

                                  break;



                       case 6:

                                  digitalWrite (GPIO_LED_DISPLAY_COL_1, LOW);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_2, HIGH);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_3, HIGH);

                                  break;



                       case 7:

                                  digitalWrite (GPIO_LED_DISPLAY_COL_1, HIGH);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_2, HIGH);

                                  digitalWrite (GPIO_LED_DISPLAY_COL_3, HIGH);

                                  break;



                       default:

                                  break;

           }



           //tmr_startms(led_display.tmr_refresco_display, TIMEOUT_COLUMNA_DISPLAY);

}



void ActualizaLedDisplay (TipoLedDisplay *led_display) {

			ApagaFilas ( led_display );

			ExcitaColumnas ( led_display -> p_columna );

			for ( int i = 0; i < NUM_FILAS_DISPLAY; i++ ){

				if ( led_display -> pantalla.matriz[i] [led_display -> p_columna] > 0 )

					digitalWrite ( led_display -> filas [i], LOW );
		}



}



void PintaPantallaPorTerminal (tipo_pantalla *p_pantalla) {

          // int i=0, j=0;



//         printf("\n[PANTALLA]\n");
//
//           fflush(stdout);
//
//           for(j=0;j<NUM_FILAS_DISPLAY;j++) {
//
//                       for(i=0;i<NUM_COLUMNAS_DISPLAY;i++) {
//
//                                  printf("%d", p_pantalla->matriz[i][j]);
//
//                                  fflush(stdout);
//
//                       }
//
//                       printf("\n");
//
//                       fflush(stdout);
//
//           }
//
//           fflush(stdout);

}



//------------------------------------------------------

// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS

//------------------------------------------------------



int CompruebaTimeoutColumnaDisplay (fsm_t* this) {

           int result = 0;

           TipoLedDisplay *p_ledDisplay;

           p_ledDisplay = (TipoLedDisplay*)(this->user_data);



           piLock (MATRIX_KEY);

           result = p_ledDisplay -> flags & TIMEOUT_COLUMNA_DISPLAY;

           piUnlock (MATRIX_KEY);

           return result;

}



//------------------------------------------------------

// FUNCIONES DE SALIDA O DE ACCION DE LA MAQUINA DE ESTADOS

//------------------------------------------------------



void ActualizaExcitacionDisplay (fsm_t* this) {

           TipoLedDisplay *p_ledDisplay;

           p_ledDisplay = (TipoLedDisplay*)(this->user_data);

           piLock (MATRIX_KEY);

           p_ledDisplay -> flags &= ~FLAG_TIMEOUT_COLUMNA_DISPLAY;


           p_ledDisplay -> p_columna++;

           if (p_ledDisplay -> p_columna > NUM_COLUMNAS_DISPLAY-1){

                       p_ledDisplay -> p_columna = 0;

           }


           ActualizaLedDisplay (p_ledDisplay);

           piUnlock (MATRIX_KEY);

           tmr_startms ((tmr_t*)(p_ledDisplay -> tmr_refresco_display), TIMEOUT_COLUMNA_DISPLAY);

}



//------------------------------------------------------

// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES

//------------------------------------------------------



void timer_refresco_display_isr (union sigval value) {

           piLock (MATRIX_KEY);

           led_display.flags |= FLAG_TIMEOUT_COLUMNA_DISPLAY;

           piUnlock (MATRIX_KEY);

}

