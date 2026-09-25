
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


//  typedef void (*Action)(void);

//  typedef enum { ETAT_1, ETAT_2,ETAT_3,ETAT_4,ETAT_5,NB_ETATS } Etat;

// typedef enum {
//    OBSTACLE,
//   PAS_OBSTACLE,
//   NB_EVENTS
//  } Event;

// typedef struct {
//  Etat etat_suivant;
//  Action action;
//  } Transition;


//  void action_action_1(void);

//  void action_action_2(void);

//  void action_action_3(void);

//  void action_action_4(void);

//  void action_action_5(void);

//  void action_tourne(void);

//  Event get_event();