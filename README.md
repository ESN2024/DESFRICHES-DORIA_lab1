# Objectif:
L'objectif du TP est de d'implémenter un chenillard sur une architecture SoC FPGA en utilisant la carte DE10 Lite.

# Intro:
On veut pouvoir lancer le chenillard lors de l'appui sur un bouton poussoir, et en régler la vitesse en utilisant 4 switchs.

Le programme va utiliser deux GPIOs en mode interruption. Un pour le bouton poussoir, et l'autre pour les switchs.