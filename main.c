#include <msp430.h>
#include "config.h"
#include "mouv_function.h"
#include "ADC.h"
#include "Afficheur.h"
#include "machine_etat.h"



 
volatile int compt_front_1=0;
volatile int compt_front_2=0;
volatile int compt_second=0;
volatile int is_mving=1;

volatile int val_distance=0;
volatile int droite=89;

volatile int a, b;

#pragma vector=TIMER0_A1_VECTOR //voir diaporama seance precedente
__interrupt void ma_fnc_timer(void)
{
      if ((TA0CTL & TAIFG) == TAIFG)
      {
        ADC_Demarrer_conversion(3);
        val_distance = 4 + ((int)(ADC_Lire_resultat() * 26 / 1024));
        droite = 89 - compt_second;
        Aff_valeur(convert_Hex_Dec(val_distance * 100 + droite));
        Aff_Points(BIT4 | BIT5);

        compt_second++;
        stop_danse();
      }
      TA0CTL &= ~TAIFG; //RAZ TAIFG
}

// #pragma vector=TIMER1_A1_VECTOR //voir diaporama seance precedente
// __interrupt void lumi(void)
// {
//       if ((TA1CTL & TAIFG) == TAIFG)
//       {
//         ADC_Demarrer_conversion(2);
//         a = ADC_Lire_resultat();
//         b = convert_Hex_Dec(a);

//         allum_phare(a);
//       }
//       TA1CTL &= ~TAIFG; //RAZ TAIFG
// }
 
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

void stop_1_m_30()
{
    if(compt_front_1>=234)
    {
       robot_arret();
       
    }
}

void stop_danse()
{
     if(compt_second>=89)
     {
      robot_arret();
     }
}

void allum_phare(int n){
 
  if(n<=512){
      P1OUT  |= BIT0;
      P1OUT  |= BIT6;
  }
  else {
 
      P1OUT  &= ~BIT0;
      P1OUT  &= ~BIT6;
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

  //config_led();

  TA1CCR0 = 2500;
  

  // homologation
  // Etat etat = MARCHE;
  // Event event;
  // Transition trs;
  // Transition table_transition[NB_ETATS][NB_EVENTS] = {
  //   [MARCHE] = {
  //     [OBSTACLE] = {ARRET, action_arret},
  //     [PAS_OBSTACLE] = {MARCHE, action_avancer}
  //     },
  //   [ARRET] = {
  //     [OBSTACLE] = { ARRET, action_arret},
  //     [PAS_OBSTACLE] = {MARCHE, action_avancer}
  //   }
  //   };

  // danse

  Etat etat = ETAT_1;
  Event event;
  Transition trs;
  Transition table_transition[NB_ETATS][NB_EVENTS] = {
    [ETAT_1] = {
      [OBSTACLE] = {ETAT_2, action_tourne},
      [PAS_OBSTACLE] = {ETAT_2, action_action_1}
      },
    [ETAT_2] = {
      [OBSTACLE] = { ETAT_3, action_tourne},
      [PAS_OBSTACLE] = {ETAT_3, action_action_2}
    },
    [ETAT_3] = {
      [OBSTACLE] = { ETAT_4, action_tourne},
      [PAS_OBSTACLE] = {ETAT_4, action_action_3}
    },
    [ETAT_4] = {
      [OBSTACLE] = { ETAT_5, action_tourne},
      [PAS_OBSTACLE] = {ETAT_5, action_action_4}
    },
    [ETAT_5] = {
      [OBSTACLE] = { ETAT_1, action_tourne},
      [PAS_OBSTACLE] = {ETAT_1, action_action_5}
    },
    };

 
  //avancer();
  

  __enable_interrupt();
  // while(compt_front_1<234){

  //  //homologation
  //   event = get_event();
  //   trs = table_transition[etat][event];
  //   trs.action();
  //   etat = trs.etat_suivant;

  // }
  //   robot_arret();

// danse
while(compt_second<89){

    event = get_event();
    trs = table_transition[etat][event];
    trs.action();
    etat = trs.etat_suivant;

  }
    robot_arret();
}