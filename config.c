#include "config.h"
#include <msp430.h>
 
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
 
void config_register_pwm()
{
  P2SEL &= ~(BIT0 | BIT1 | BIT3 | BIT5);  // Select I/O function for red LED
  P2SEL2 &= ~(BIT0 | BIT1  |BIT3 | BIT5);
 
  P2DIR |= (BIT1 | BIT5);           // bit 0 port 1 en sortie
  P2DIR &= ~(BIT0 | BIT3);
 
     
  P2DIR |= (BIT2 | BIT4);            
  P2SEL |= (BIT2 | BIT4);            
  P2SEL2 &= ~(BIT2 | BIT4);
 
  TA1CTL = 0| TASSEL_2 | MC_1 | ID_0;  // source SMCLK pour TimerA , mode comptage Up
  TA1CCTL1 |= OUTMOD_7;
  TA1CCTL2 |= OUTMOD_7;
}
 
void config_timer0()
{
  // parametrage timer0
  TA0CTL = 0|(TASSEL_2 | ID_2); //source SMCLK, pas de predivision ID_0
  TA0CTL |= TAIE; //autorisation interruption TAIE
  TA0CCR0 = 62500; //voir texte
  TA0CTL |= MC_3;

}