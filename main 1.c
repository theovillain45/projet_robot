#include <msp430.h>
#include "config.h"
#include "mouv_function.h"
#include "ADC.h"
#include "machine_etat.h"
 
 
 
volatile int compt_front_1=0;
volatile int compt_front_2=0;
volatile int compt_second=0;
volatile int is_mving=1;
 
volatile int val_distance=0;
volatile int droite=77;
 
 
#pragma vector=TIMER0_A1_VECTOR //voir diaporama seance precedente
__interrupt void ma_fnc_timer(void)
{
      if ((TA0CTL & TAIFG) == TAIFG)
      {
        ADC_Demarrer_conversion(0);
        val_distance = 4 + ((int)(ADC_Lire_resultat() * 26 / 1024));
 
        Aff_valeur(convert_Hex_Dec(val_distance * 100 + droite));
        Aff_Points(BIT4 | BIT5);
        __delay_cycles(5000);
      }
      TA0CTL &= ~TAIFG; //RAZ TAIFG
}
 
 #pragma vector=PORT2_VECTOR
 __interrupt void compt_front(void)
{
   if((P2IFG & BIT0)==BIT0)
   {
     compt_front_1++;
     P2IES ^= BIT0;
     P2IFG &= ~BIT0;
   }
 
   if((P2IFG & BIT3)==BIT3)
   {
     compt_front_2++;
     P2IES ^= BIT3;
     P2IFG &= ~BIT3;
   }
}
 
int stop_1_30_m()
{
    if(compt_front_1>=220)
    {
       robot_arret();
       return 0;
    }
    else {
      return 1;
    }
}
 
 
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
 
  Aff_Init();
  ADC_init();
  BCSCTL1= CALBC1_1MHZ;      
  DCOCTL= CALDCO_1MHZ;
 
  config_register_pwm();
 
  config_timer0();
 
  config_octo();
 
  TA1CCR0 = 2500;
 
 
  // partie table de transition
 
  Etat etat = MARCHE;
  Event event;
  Transition trs;
  Transition table_transition[NB_ETATS][NB_EVENTS] = {
    [MARCHE] = {
      [OBSTACLE] = {ARRET, action_arret},
      [PAS_OBSTACLE] = {MARCHE, action_avancer}
      },
    [ARRET] = {
      [OBSTACLE] = { ARRET, action_arret},
      [PAS_OBSTACLE] = {MARCHE, action_avancer}
    }
    };
 
  //avancer();
 
  __enable_interrupt();
  while(stop_1_30_m()){
    event = get_event();
    trs = table_transition[etat][event];
    trs.action();
    etat = trs.etat_suivant;
    //__delay_cycles(500000);
    //stop_1_m();
  }
 
}