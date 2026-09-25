#include "mouv_function.h"
#include <msp430.h>

void avancer()
{
    TA1CCR1= percent_control(30);
    TA1CCR2= percent_control(32);
    P2OUT &= ~BIT1;
    P2OUT |= BIT5;
}

void avancer1()
{
    TA1CCR1= percent_control(70);
    TA1CCR2= percent_control(35);
    P2OUT &= ~BIT1;
    P2OUT |= BIT5;
    __delay_cycles(7000000);
    robot_arret();
}

void avancer2()
{
    TA1CCR1= percent_control(35);
    TA1CCR2= percent_control(70);
    P2OUT &= ~BIT1;
    P2OUT |= BIT5;
    __delay_cycles(7000000);
    robot_arret();
     __delay_cycles(500000);
    pivoter_droite();
    __delay_cycles(500000);
}

void reculer()
{
    TA1CCR1= percent_control(30);
    TA1CCR2= percent_control(32);
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
    TA1CCR1= percent_control(40);
    TA1CCR2= percent_control(42);
    P2OUT |= BIT1;
    P2OUT |= BIT5;
    __delay_cycles(2000000);
    robot_arret();

}
void tour_180()
{
    TA1CCR1= percent_control(40);
    TA1CCR2= percent_control(42);
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