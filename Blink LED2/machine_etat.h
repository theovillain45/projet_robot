typedef void (*Action)(void);
 
typedef enum { MARCHE, ARRET , PIVOTER, NB_ETATS } Etat;
 
typedef enum {
  OBSTACLE,
  PAS_OBSTACLE,
  NB_EVENTS
} Event;
 
typedef struct {
Etat etat_suivant;
Action action;
} Transition;
 
 
void action_avancer();
 
void action_arret();

void action_pivoter();
 
Event get_event();