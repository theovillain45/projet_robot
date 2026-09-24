#include "machine_etat.h"
#include "mouv_function.h"
#include "ADC.h"
#include <msp430.h>
 
#define NB_ETATS (3)
#define NB_EVENTS (2)
 
typedef void (*Action)(void);
 
void action_avancer(void) { avancer();}
void action_arret(void) { robot_arret();}
void action_pivoter(void) {pivoter_gauche_5fois();}
 
volatile int val_distance2 = 0;
 
Event get_event(){
   
    ADC_Demarrer_conversion(0);
    val_distance2 = 4 + ((int)(ADC_Lire_resultat() * 26 / 1024));
    if(val_distance2 >= 15 ){
        return OBSTACLE;
    }
    else if (val_distance2 < 15 )
    {
    return PAS_OBSTACLE;}
}