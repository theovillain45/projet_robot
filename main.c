#include <msp430.h>
#include "config.h"
#include "mouv_function.h"


 
volatile int compt_front_1=0;
volatile int compt_front_2=0;
volatile int compt_second=0;
volatile int is_mving=1;

#pragma vector=TIMER0_A1_VECTOR //voir diaporama seance precedente
__interrupt void ma_fnc_timer(void)
{
      if ((TA0CTL & TAIFG) == TAIFG)
      {
        if(is_mving !=0)
        {
           TA1CCR1= percent_control(20);
           TA1CCR2= percent_control(22);
        }
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

void stop_1_m()
{
    if(compt_front_1>=180)
    {
       robot_arret();
       
    }
}
 
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
 
  BCSCTL1= CALBC1_1MHZ;      
  DCOCTL= CALDCO_1MHZ;
 
  config_register_pwm();
  
  config_timer0();
 
  config_octo();

  TA1CCR0 = 2500; 
  TA1CCR1= percent_control(20);
  TA1CCR2= percent_control(22);
 
  avancer();
 
  __enable_interrupt();
  while(1)
  {
    stop_1_m();
  } 
 
}