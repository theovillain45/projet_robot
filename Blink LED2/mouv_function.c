#include "mouv_function.h"
#include <msp430.h>
volatile int i;

int permille_control(int percent)
{
  return (int)(percent*(TA1CCR0/1000));
}

void avancer()
{
    TA1CCR1= permille_control(400);
    TA1CCR2= permille_control(450);
    P2OUT &= ~BIT1;
    P2OUT |= BIT5;
}

void reculer()
{
    TA1CCR1= permille_control(200);
    TA1CCR2= permille_control(225);
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

void pivoter_gauche_5fois()
{
    P2OUT |= BIT1;
    P2OUT |= BIT5;
    __delay_cycles(2000000);
    robot_arret();
}

void robot_arret()
{
    TA1CCR1=0;
    TA1CCR2=0;
    P2OUT &= ~BIT1;
    P2OUT |= BIT5;
}

void robot_slow_arret()
{
    for(i=0;i<5;i++)
    {
        TA1CCR1=TA1CCR1-10;
        TA1CCR2=TA1CCR2-10;
        __delay_cycles(10000);
    }
}
void stop_n_second(int s,int n)
{
   if(s>=n)
   {
    robot_arret();
   }
}

