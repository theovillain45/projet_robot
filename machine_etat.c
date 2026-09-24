#include "machine_etat.h"
#include "mouv_function.h"
#include "ADC.h"
#include <msp430.h>
 
#define NB_ETATS (2)
#define NB_EVENTS (2)
 
typedef void (*Action)(void);
 
void action_avancer(void) { avancer();}
void action_arret(void) { robot_arret();}
 
volatile int val_distance2 = 0;
 
Event get_event(){
   
    ADC_Demarrer_conversion(0);
    val_distance2 = 4 + ((int)(ADC_Lire_resultat() * 26 / 1024));
    if(val_distance2 >= 10 ){
        return OBSTACLE;
    }
    else if (val_distance2 < 10 )
    {
    return PAS_OBSTACLE;}
}