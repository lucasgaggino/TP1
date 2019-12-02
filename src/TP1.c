/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * Date: 2016-04-26
 */

/*==================[inclusions]=============================================*/


#include "TP1.h"       // <= sAPI header


/*==================[macros and definitions]=================================*/
#define COMPILAR_CODIGO_BLINKY (1)
#define COMPILAR_CODIGO_SWITCH_LEDS (2)
#define COMPILAR_CODIGO_TICKHOOK (3)
#define COMPILAR_CODIGO_C_DEBUGGER (4)
#define COMPILAR_CODIGO_PUNTO_6 (5)


#define COMPILAR_CODIGO (COMPILAR_CODIGO_BLINKY)


#define TICKRATE_MS 1
#define LED_TOGGLE_MS 1000
/*==================[internal data declaration]==============================*/
unsigned int delayer=0;
/*==================[internal functions declaration]=========================*/



void myTickHook( void *ptr ){
	if(delayer==9){
	 // modificacion para disminuir la frecuencia 10 vecs
		static bool_t ledState = OFF;
		gpioMap_t led = (gpioMap_t)ptr;


		if( ledState ){
			ledState = OFF;
		}
		else{
			ledState = ON;
		}
		gpioWrite( led, ledState );
		delayer=0;
	}
	else{delayer++;}

 }

int medirT(){
	int i=10;
	int t=0;
	int T=0;
	while(!gpioRead(FASE)){

	}
	tickWrite(0);
	while(gpioRead(FASE)){

	}
	while(i){
		if(!gpioRead(FASE)){
			i=tickRead();

		}
	}
}

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/





int main(void){

   /* ------------- INICIALIZACIONES ------------- */
#if COMPILAR_CODIGO==COMPILAR_CODIGO_BLINKY

   /* Inicializar la placa */
   boardConfig();
   gpioConfig( TRIAC, GPIO_OUTPUT );
   gpioConfig( CW, GPIO_OUTPUT );
   gpioConfig( CCW, GPIO_OUTPUT );
   gpioConfig( DE, GPIO_OUTPUT );
   gpioConfig( TACO, GPIO_INPUT );
   gpioConfig( FASE, GPIO_INPUT );

   tickInit(TICKRATE_MS);
   /* ------------- REPETIR POR SIEMPRE ------------- */
   uint64_t tickCounter;
   while(1) {
	   tickWrite(0);
	   tickCounter = tickRead();
	   delay(1);
	   tickCounter = tickRead();
	   delay(1);



   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

#elif COMPILAR_CODIGO==COMPILAR_CODIGO_SWITCH_LEDS

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */


   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   gpioConfig( GPIO0, GPIO_INPUT );

   gpioConfig( GPIO1, GPIO_OUTPUT );

   /* Variable para almacenar el valor de tecla leido */
   bool_t valor;

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      valor = !gpioRead( TEC1 );
      gpioWrite( LEDB, valor );

      valor = !gpioRead( TEC2 );
      gpioWrite( LED1, valor );

      valor = !gpioRead( TEC3 );
      gpioWrite( LED2, valor );

      valor = !gpioRead( TEC4 );
      gpioWrite( LED3, valor );

      valor = !gpioRead( GPIO0 );
      gpioWrite( GPIO1, valor );

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
 }
#elif COMPILAR_CODIGO == COMPILAR_CODIGO_TICKHOOK


 /* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */


    /* ------------- INICIALIZACIONES ------------- */

    /* Inicializar la placa */
    boardConfig();


    tickConfig( TICKRATE_MS );


    tickCallbackSet( myTickHook, (void*)LEDR );
    delay(LED_TOGGLE_MS);


    while(1) {

       tickCallbackSet( myTickHook, (void*)LEDG );
       delay(LED_TOGGLE_MS);

       tickCallbackSet( myTickHook, (void*)LEDB );
       delay(LED_TOGGLE_MS);
       tickCallbackSet( myTickHook, (void*)LED1 );
       delay(LED_TOGGLE_MS);
       tickCallbackSet( myTickHook, (void*)LED2 );
       delay(LED_TOGGLE_MS);
       tickCallbackSet( myTickHook, (void*)LED3 );
       delay(LED_TOGGLE_MS);
       tickCallbackSet( myTickHook, (void*)LEDR );
       delay(LED_TOGGLE_MS);
    }

    return 0 ;
 }
#elif COMPILAR_CODIGO == COMPILAR_CODIGO_C_DEBUGGER
 /* Inicializar la placa */
 boardConfig();
 /* Inicializar UART_USB a 115200 baudios */
 uartConfig( UART_USB, 115200 );

 uartWriteString( UART_USB, "DEBUG c/sAPI\r\n" );

 /* ------------- REPETIR POR SIEMPRE ------------- */
 while(1) {

    /* Prendo el led azul */
    gpioWrite( LEDB, ON );
    uartWriteString( UART_USB, "LED Toggle\r\n" ); //digo que prendi el led
    delay(500);

    /* Apago el led azul */
    gpioWrite( LEDB, OFF );
    uartWriteString( UART_USB, "LED Toggle\n" ); //digo que apague el led
    delay(500);

 }



 return 0 ;
 }

#elif COMPILAR_CODIGO==COMPILAR_CODIGO_PUNTO_6


   boardConfig();

   gpioConfig( GPIO0, GPIO_INPUT );

   gpioConfig( GPIO1, GPIO_OUTPUT );

   /* Variable para almacenar el valor de tecla leido */


   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      if(!gpioRead( TEC1 )){
    	  gpioWrite( LEDB, ON );
    	  delay(500);
    	  gpioWrite( LEDB, OFF );

    	  gpioWrite( LED1, ON );
      	  delay(500);
      	  gpioWrite( LED1, OFF );

      	  gpioWrite( LED2, ON );
      	  delay(500);
      	  gpioWrite( LED2, OFF );

      	  gpioWrite( LED3, ON );
      	  delay(500);
      	  gpioWrite( LED3, OFF );

      }

   }


   return 0 ;
 }
#endif


