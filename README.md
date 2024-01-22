# Objectif
L'objectif du TP est de d'implémenter un chenillard sur une architecture SoC FPGA en utilisant la carte DE10 Lite.

# Intro
On veut pouvoir lancer le chenillard lors de l'appui sur un bouton poussoir, et en régler la vitesse en utilisant 4 switchs.

Le programme va utiliser deux GPIOs en mode interruption. Un pour le bouton poussoir, et l'autre pour les switchs.
Les Leds seront alors définies en sorties, et les sources d'inerruptions en entrées

# Création d'une structure NIOSII standard
## Schéma du système
![schema_systeme-1](https://github.com/ESN2024/DESFRICHES-DORIA_lab1/assets/152646071/59d1c49f-49ec-428a-9c86-a87eaae9fc5e)


## Modèle QSYS sur platform designer
![qsys-1](https://github.com/ESN2024/DESFRICHES-DORIA_lab1/assets/152646071/ef97dbaf-9808-48ef-bf81-142e98cf2f28)


### Explication
Sur QPlatform designer la démarche à suivre est la celle ci-dessous:
- Ajouter un processeur NIOS II pour l'exécutions des programmes en c
- Ajouter une mémoire RAM de 40Ko pour supporter les codes sources et leurs variables
- Ajouter une liaison JTAG UART notemment pour avoir accès au moniteur série
- Ajouter les PIO_0; PIO_1; PIO_2, qui nous permettront d'utiliser les entrées sorties lorsqu'elles seront connectées aux bons périphériques du FPGA (cf Pin Planner)

## Quartus

Une fois que le modèle QSYS est généré, il faut faire l'analyse sur Quartus pour ensuite associer les Leds, PB et switchs, au PIOs définis sur le modèle QSYS.

## Pin Planner
![pin_planner-1](https://github.com/ESN2024/DESFRICHES-DORIA_lab1/assets/152646071/18b209f4-a726-4495-83e9-4a5966475dd7)


### Explication
Chaque périphérique a un nom précis que l'on trouve sur le datasheet de la carte DE10-Lite. Il suffit alors d'associer les éléments à leur nom correspondant.

# Terminal de commande NIOSII
La compilation du projet QSYS va générer un fichier "nomQSYS.sopcinfo" à partir duquel on va fabriquer le dossier BSP.
Ensuite, on génère un makefile et on le place dans APP. Celui ci prendra en entrée le fichier source, et construira le fichier exécutable .elf en sortie.

# Fichier source
Distinguons bien les différentes parties de ce code:
- ***irqhandler_bp_key1*** est la routine d'interrupion qui a pour rôle d'allumer les Leds à la suite pour réliser le chenillard, lors de l'appui sur le bouton poussoir. A la fin de l'exécution, l'interrupt flag est réinitialisé et on sort de la routine.
- ***irqhandler_switchs*** est la routine d'interruption qui prend en compte la combinaison binaire que forment les switchs. Le délai d'attente entre l'allumage de deux leds va alors être divisé par cette combinaison lors d'un nouvel appui sur le BP.
- ***main()*** fontion principale dans laquelle on autorise les interruptions en réinitialisant leur flag notemment.

-   *IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_2_BASE, 0x0F);* cette ligne permet de configurer un masque sur le PIO en utilisant uniquement les 4 premiers switchs
-   *IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0x0F);* cette ligne nous permet de configurer l'envoi d'une interruption lors d'un changement d'état d'un switch.
-   *alt_irq_register()* cette fonction permet d'inscrire les routines d'interruptions dans le gestionnaire d'interruption

# Conclusion
Ce TP est un bon moyen de comprendre la conception conjointe, en alliant processeur et entrées/sorties du FPGA. La prochaine étape lors du TP suivant sera de faire concorder un script c avec un fichier VHDL pour permettre au NIOSII de communiquer avec le une fonction du FPGA.
