#include <msp430.h>
 
int compt_timer=0;
 
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_ISR(void) {

  
  if ((TA1CTL & TAIFG) == TAIFG) {
    compt_timer++;
    TA1CTL &= ~(TAIFG);
  }
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
 
void pwm_moteur_A(int n)
{
     TA1CCR2=n;
}
 
void pwm_moteur_B(int n)
{
     TA1CCR1=n;
}
 
 void robot_arret(int n)
 {
    if(compt_timer<n)
    {
       pwm_moteur_A(0);
 
       pwm_moteur_B(0);
    }
   
 }
 
int main(void)
{
  int pwm_grad=1000;
 
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
  TA1CCTL2 |= OUTMOD_7;
  TA1CCTL1 |= OUTMOD_7;
 
  // activation mode de sortie n°7
  TA1CCR0 = 5000;  
  __enable_interrupt();
    pwm_moteur_A(pwm_grad);
 
    pwm_moteur_B(pwm_grad);
 
    sens_moteur_A(1);
 
    sens_moteur_B(1);
 
  //robot_arret(10);
  while(1);
 
}