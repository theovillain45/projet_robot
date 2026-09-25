#include "mouv_function.h"
#include <msp430.h>

void avancer()
{
    TA1CCR1= percent_control(20);
    TA1CCR2= percent_control(22);
    P2OUT &= ~BIT1;
    P2OUT |= BIT5;
}

void avancer1()
{
    TA1CCR1= percent_control(30);
    TA1CCR2= percent_control(15);
    P2OUT &= ~BIT1;
    P2OUT |= BIT5;
    __delay_cycles(1000000);
    robot_arret();
}

void avancer2()
{
    TA1CCR1= percent_control(15);
    TA1CCR2= percent_control(30);
    P2OUT &= ~BIT1;
    P2OUT |= BIT5;
    __delay_cycles(1000000);
    robot_arret();
    pivoter_droite();
}

void reculer()
{
    TA1CCR1= percent_control(20);
    TA1CCR2= percent_control(22);
    P2OUT |= BIT1;
    P2OUT &= ~BIT5;
}

void pivoter_droite()
{
   P2OUT &= ~BIT1;
   P2OUT &= ~BIT5;
   __delay_cycles(100000);
   robot_arret();
}

void pivoter_gauche()
{
    P2OUT |= BIT1;
    P2OUT |= BIT5;
     __delay_cycles(100000);
    robot_arret();
}
void tour_360()
{
    TA1CCR1= percent_control(20);
    TA1CCR2= percent_control(22);
    P2OUT |= BIT1;
    P2OUT |= BIT5;
    __delay_cycles(400000);
    robot_arret();
}
void tour_180()
{
    TA1CCR1= percent_control(20);
    TA1CCR2= percent_control(22);
    P2OUT |= BIT1;
    P2OUT |= BIT5;
     __delay_cycles(200000);
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