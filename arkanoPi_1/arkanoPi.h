#ifndef _ARKANOPI_H_
#define _ARKANOPI_H_

#include "systemLib.h"
#include "kbhit.h" // para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas
#include "fsm.h"
#include "tmr.h"
#include "teclado_TL04.h"
#include "arkanoPiLib.h"
#include "ledDisplay.h"

typedef struct {
	tipo_arkanoPi arkanoPi;
	// Aqui podrian añadirse otros juegos...
	// tipo_otroJuego1 otroJuego1;
	// tipo_otroJuego2 otroJuego2;
	// ...
} TipoSistema;

//------------------------------------------------------
// FUNCIONES DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------
int CompruebaBotonPulsado (fsm_t* this);
int CompruebaMovimientoIzquierda(fsm_t* this);
int CompruebaMovimientoDerecha(fsm_t* this);
int CompruebaMovimientoArriba(fsm_t* this);
int CompruebaMovimientoAbajo(fsm_t* this);
int CompruebaTimeoutActualizacionJuego (fsm_t* this);
int CompruebaFinalJuego(fsm_t* this);
int CompruebaDificultadFacil ( fsm_t* this);
int CompruebaDificultadMedia ( fsm_t* this);
int CompruebaDificultadDificil ( fsm_t* this);
int CompruebaDificultadIncremental ( fsm_t* this);
int CompruebaDificultadFacil ( fsm_t* this);
int CompruebaBotonDificultad ( fsm_t* this);
int CompruebaPausarJuego ( fsm_t* this);
int CompruebaReanudarJuego ( fsm_t* this);

//------------------------------------------------------
// FUNCIONES DE ACCION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------
void InicializaJuego (fsm_t* this);
void MuevePalaIzquierda (fsm_t* this);
void MuevePalaDerecha (fsm_t* this);
void MuevePalaArriba (fsm_t* this);
void MuevePalaAbajo (fsm_t* this);
void ActualizarJuego (fsm_t* this);
void FinalJuego (fsm_t* this);
void ReseteaJuego (fsm_t* this);
void ActualizarDificultadFacil (fsm_t* this);
void ActualizarDificultadMedia (fsm_t* this);
void ActualizarDificultadDificil (fsm_t* this);
void ActualizarDificultadIncremental (fsm_t* this);
void ActualizarBotonDificultad (fsm_t* this);
void PausarJuego (fsm_t* this);
void ReanudarJuego (fsm_t* this);

//------------------------------------------------------
// FUNCIONES DE CONFIGURACION/INICIALIZACION
//------------------------------------------------------
int ConfiguraInicializaSistema (TipoSistema *p_sistema);

//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------
void tmr_actualizacion_juego_isr(union sigval value);

//------------------------------------------------------
// FUNCIONES LIGADAS A THREADS ADICIONALES
//------------------------------------------------------
PI_THREAD(thread_explora_teclado_PC);

#endif /* ARKANOPI_H_ */
