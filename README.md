# Projet Robot Groupe 5
### Equipe : Théo Villain, Marys Miassi, Djrado Zounmenou, Sadikh Thiam, Antoine, Aya Jouay 

L'objectif de ce projet est de passer l'étape de l'homologation ainsi que de développer un programme pour que notre robot puisse effectuer une "danse".

Le robot qui a été choisi est le robot "fast".

## 1 - Programme pour être homologué
Voici les conditions d'homologation d'un robot pour l'évaluation finale :
#### • Un robot au choix parmi les deux sera homologué.
#### • 1.30m à parcourir, avec une précision de ± 5cm.
#### • Un obstacle sera présenté aléatoirement (après les 10 premiers cm et avant les 10 derniers 
cm).
‣ Le robot doit s’arrêter à entre 5 et 15cm de l’obstacle.
‣ Il devra reprendre sa marche une fois l’obstacle retiré.
#### • Durée maximale: 10 secondes
‣ Le compteur sera mis en pause lors de la présentation de l’obstacle.
#### • Aucune des deux roues du robot ne doit traverser la ligne centrale 
### 1.1 - Fonctionnalitées
Nous avons donc développé un robot qui puisse répondre aux different prérequis. Premièrement, le robot est capable de s'arreter au bout de un mètre et trente centimètres.
<br></br>
De plus, Le robot est capable de s'arreter avant un obstacle, qui est detecté par un capteur infra rouge. Une fois l'obstacle enlevé, le robot reprend son chemin jusqu'a faire la distance souhaité.

Le robot affiche plusieurs valeurs, tel que la la distance d'un obstacle, etc...

### 1.2 - Structure du code
Nous avons structuré le programme de la manière suivante : 
- Un fichier de configuration
- Un fichier pour les fonctions de mouvement
- Un fichier pour la machine d'etat
- Le fichier principal "main.c"

## 2 - Programme pour danser
Le deuxieme programme a pour objectif de nous faire participer au concours de danse. Nous avons pour cela respecté les prerequis : 
- Passage une à une des équipes
- Plateau de 2m x 2m
- Durée maximale: 90 secondes
- 1 à 2 robots par équipe
- Le robot devra être capable « d’allumer ses phares » (LEDs de la MSP430, PAS de la carte d’extension) en fonction de la luminosité ambiante
### 2.1 Fonctionnalitées
Notre robot est capable de danser de la façon suivante : 
Il avance droit, et lorsqu'il rencontre un obstacle, il va tourner sur lui même avant de partir dans une direction aleatoire. L'objectif étant de se deplacer d'une manière fluide
### 2.2 Structure du code
Le code est structuré de la même manière que le programme précédent, avec un changement dans la table de transition.
Si dans la version homologué, nous avons la table suivante : 

````
  Transition table_transition[NB_ETATS][NB_EVENTS] = {
    [MARCHE] = {
      [OBSTACLE] = {ARRET, action_arret},
      [PAS_OBSTACLE] = {MARCHE, action_avancer}
      },
    [ARRET] = {
      [OBSTACLE] = { ARRET, action_arret},
      [PAS_OBSTACLE] = {MARCHE, action_avancer}
    }
    };
````
Nous avons desormais la table suivante : 
````
  Transition table_transition[NB_ETATS][NB_EVENTS] = {
    [MARCHE] = {
      [OBSTACLE] = {ARRET, action_pivoter},
      [PAS_OBSTACLE] = {MARCHE, action_avancer}
      },
    [ARRET] = {
      [OBSTACLE] = { ARRET, action_pivoter},
      [PAS_OBSTACLE] = {MARCHE, action_avancer}
    }
  }
````

