#include <msp430.h>

main(){

// initialisations des pins utilisés
  P2SEL &= ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5);
  P2SEL2 &= ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5);

// mets en sortie le port 2, sortie de pwm pour le moteur A
  //les sorties
  P2DIR |= (BIT2 | BIT1 | BIT4 | BIT5);
  // les entrées
  P2DIR &= ~(BIT0 | BIT3);



  while (1) {
      P2OUT |= BIT5;
      P2OUT &= ~BIT1;
  }



}

