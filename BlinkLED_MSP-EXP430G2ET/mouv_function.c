#include "mouv_function.h"
#include <msp430.h>

void avancer()
{
    TA1CCR1= percent_control(20);
    TA1CCR2= percent_control(22);
    P2OUT &= ~BIT1;
    P2OUT |= BIT5;
}

void reculer()
{
    P2OUT |= BIT1;
    P2OUT &= ~BIT5;
}

void pivoter_droite()
{
   P2OUT &= ~BIT1;
   P2OUT &= ~BIT5;
   __delay_cycles(500000);
   robot_arret();
}

void pivoter_gauche()
{
    P2OUT |= BIT1;
    P2OUT |= BIT5;
     __delay_cycles(500000);
    robot_arret();
}

void robot_arret()
{
     TA1CCR1=0;
     TA1CCR2=0;
}

void robot_slow_arret()
{
    int i = 0;
    for(i=0;i<5;i++)
    {
        TA1CCR1=TA1CCR1-10;
        TA1CCR2=TA1CCR2-10;
        __delay_cycles(100000);
    }
}

int percent_control(int percent)
{
  return (int)(percent*(TA1CCR0/100));
}