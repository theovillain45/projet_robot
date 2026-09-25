#include "machine_etat.h"
#include "mouv_function.h"
#include "ADC.h"
#include <msp430.h>



void action_avancer(void) { avancer();}
void action_arret(void) { robot_arret();}

volatile int val_distance2 = 0;

Event get_event(){
    
    ADC_Demarrer_conversion(3);
    val_distance2 = 4 + ((int)(ADC_Lire_resultat() * 26 / 1024));
    if(val_distance2 >= 10 ){
        return OBSTACLE;}
    else if (val_distance2 < 10 )
    {
    return PAS_OBSTACLE;}
}


//  void action_action_1(void)
//  { 
//      avancer();
//      __delay_cycles(2000000);
     

//      pivoter_droite();
//  }
//  void action_action_2(void)
//  { 
//      avancer1();
//  } 
//  void action_action_3(void) 
//  { 
//      avancer2();
//  }
//  void action_action_4(void)
//  {
//      avancer();
//      tour_360();
//  }
//  void action_action_5(void)
//  {
//      reculer();
//      tour_360();
//      reculer();
//      tour_360();
//  }
//  void action_tourne(void) 
//  { 
//      tour_180();
//  }

//  volatile int val_distance2 = 0;

//  Event get_event(){
    
//     ADC_Demarrer_conversion(3);
//      val_distance2 = 4 + ((int)(ADC_Lire_resultat() * 26 / 1024));
//      if(val_distance2 >= 10 ){
//         return OBSTACLE;
//      }
//      else if  (val_distance2 < 10 )
//      {
//         return PAS_OBSTACLE;
//      }
//  }