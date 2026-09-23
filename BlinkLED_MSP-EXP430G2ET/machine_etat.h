
typedef void (*Action)(void);

typedef enum { MARCHE, ARRET , NB_ETATS } Etat;

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

Event get_event();