#include <msp430.h>
#include "Afficheur.h"
#include "ADC.h"
 
 
volatile int compt_front_1=0;
volatile int compt_front_2=0;
volatile int compt_second=0;
volatile int is_mving=1;
int propor =1;
volatile int val_distance=0;
 
int percent_control(int percent)
{
  return (int)(percent*(TA1CCR0/100));
}
 
#pragma vector=TIMER0_A1_VECTOR //voir diaporama seance precedente
__interrupt void ma_fnc_timer(void)
{
      if ((TA0CTL & TAIFG) == TAIFG)
      {
        if(is_mving !=0)
        {
           TA1CCR1= percent_control(20); - (compt_front_1-compt_front_2)*propor;
           TA1CCR2= percent_control(20); + (compt_front_1-compt_front_2)*propor;
        }
         
      }
      TA0CTL &= ~TAIFG; //RAZ TAIFG
}
 
void config_octo()
{
    P2SEL &= ~ BIT0;
    P2SEL2 &= ~ BIT0;
    P2DIR &= ~ BIT0;
    P2IE |= BIT0;
    P2IES |= BIT0;
 
    P2SEL &= ~ BIT3;
    P2SEL2 &= ~ BIT3;
    P2DIR &= ~ BIT3;
    P2IE |= BIT3;
    P2IES |= BIT3;
}
 
 
void sens_moteur_A(int sens)
{
    if (sens==0)
    {
       P2OUT &= ~BIT1;
 
    }
    else P2OUT |= BIT1;
}
 
void sens_moteur_B(int sens)
{
    if (sens==1)
    {
       P2OUT &= ~BIT5;
 
    }
    else P2OUT |= BIT5;
}
 
 
 void robot_arret()
 {
     TA1CCR1=0;
     TA1CCR2=0;
     is_mving=0;
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
 
void stop_1_m()
{
    if(compt_front_1>=180)
    {
       robot_arret();
       
    }
}
 
void avancer(){
  TA1CCR1= percent_control(50);//Roue droite
  TA1CCR2= percent_control(50);//Roue gauche
 
  sens_moteur_A(0);
 
  sens_moteur_B(0);
}
 
void tourner_droite(){
 
    sens_moteur_A(0);
    sens_moteur_B(1);
 
}
 
 #define NB_ETATS (2)
#define NB_EVENTS (2)

typedef void (*Action)(void);

typedef enum { MARCHE, ARRET } Etat;

typedef enum {
  OBSTACLE,
  PAS_OBSTACLE,
} Event;

// typedef struct {
//   Etat etat_suivant, Action action
// } Transition;

// Transition table_transition[NB_ETATS][NB_EVENTS] = {
//   [MARCHE] = {
//     [OBSTACLE] = {ARRET, action_arret},
//     [PAS_OBSTACLE] = {MARCHE, action_marcher}
//   },
//   [ARRET] = {
//     [OBSTACLE] = { ARRET, action_pas_bouger},
//     [PAS_OBSTACLE] = {MARCHE, action_marcher}
//   }
// }

 
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
 
  BCSCTL1= CALBC1_1MHZ;      
  DCOCTL= CALDCO_1MHZ;
 
  P2SEL &= ~(BIT0 | BIT1 | BIT3 | BIT5);  // Select I/O function for red LED
  P2SEL2 &= ~(BIT0 | BIT1  |BIT3 | BIT5);
 
  P2DIR |= (BIT1 | BIT5);           // bit 0 port 1 en sortie
  P1DIR &= ~(BIT0 | BIT3);
 
     
  P2DIR |= (BIT2 | BIT4);            
  P2SEL |= (BIT2 | BIT4);            
  P2SEL2 &= ~(BIT2 | BIT4);
 
  TA1CTL = 0| TASSEL_2 | MC_1 | ID_0;  // source SMCLK pour TimerA , mode comptage Up
  TA1CCTL1 |= OUTMOD_7;
  TA1CCTL2 |= OUTMOD_7;
 
 
  // parametrage timer0
  TA0CTL = 0|(TASSEL_2 | ID_2); //source SMCLK, pas de predivision ID_0
  TA0CTL |= TAIE; //autorisation interruption TAIE
  TA0CCR0 = 62500; //voir texte
  TA0CTL |= MC_3;
 
  // activation mode de sortie n7
  TA1CCR0 = 2500;  
 
  config_octo();
 
  Aff_Init();
  ADC_init();
  __enable_interrupt();
 
  while(1){
  ADC_Demarrer_conversion(0);
  val_distance = 4 + ((int)(ADC_Lire_resultat() * 26 / 1024));
 
  Aff_valeur(convert_Hex_Dec(val_distance));
 
  __delay_cycles(500000);
 
  if (val_distance >= 10){
      robot_arret(10);
      //tourner_droite();
  }
  else{
    avancer();
  }
 
  stop_1_m();
}
 
 
}