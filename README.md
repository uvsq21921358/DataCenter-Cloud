# TER

Travail Etude et Recherche

Objectif du projet

La consommation énergétique des data center est un problème crucial. Une des
solutions proposées consiste à arrêter des serveurs pour qu’ils consomment moins et à
les réveiller quand le nombre de jobs augmente. On choisit deux seuils : D pour arrêter
des serveurs et U pour les allumer. On compare le nombre de jobs dans le data center à
ces deux seuils pour allumer et éteindre. Les seuils ont une influence sur la
consommation d’énergie, le délai moyen et le taux de perte (quand il y a trop de jobs, le
contrôle les refuse).
A l’aide du logiciel Xborne (développé au laboratoire DAVID) nous avons modélisé le
système pour un couple de seuils donnés. Xborne permet également de résoudre très
vite le modèle.
Le but du projet est d’étudier expérimentalement la façon de trouver de bons seuils pour
avoir un compromis entre la consommation d’énergie et les performance du data center.
Le travail consiste à
1. Comprendre les modèles d’une politique à seuil, de la consommation énergétique
et des performances
2. Modifier le code (c’est du C) pour pouvoir inclure de nouvelles possibilités sur les
temps d’allumage des serveurs. Cela représente une vingtaine de lignes de code.
3. Collecter les résultats pour les valeurs de U et D avant de les analyser et de
chercher une politique optimale de seuil. On pourra réfléchir à l’utilisation d’un
workflow scientifique ou à des tables dans une BD accessibles par R.
4. Présenter graphiquement les compromis entre performance et énergie.

# Manuel Technique
   
Le code lancgener.c possède plusieurs fonctionnalités à savoir:

    1) excecute 03 programmes respectivement generMarkov, gthLD, rewardComponentMit modele Mitrani avec les 
    arguments necessaire pour chaque programme.

    2) genere un fichier nommé fichieUD qui contient toutes les valeurs U D utilisées par les progragrames

    3) genere un fichier nommé fichierReward qui contient tout les resultats des differents fichiers Matrice.resultats 
    generer par le programme rewardComponentMit.
    

Pour le fonctionnement de lancgener Il faut que les programmes generMarkov, gthLD, rewardComponentMit du modèle Mitrani et 
lancgener soit dans le meme dossier. Le programme lancegener exécute gernerMarkov avec tous les couples possibles entre 1 
et Buffersize du programme generMarkov. Alors une fois modifier dans generMarkov il faut aussi modifier la valeur de la variable globale MaxU dans le progragramme lancgener.

# Compilation et execution du projet

    compiler : gcc -o lancgener lancgener.c
    executer : ./lancgener
    
# Reference au modele Mitrani
Isi Mitrani. Service center trade-offs between customer impatience and power consumption.
Elsevier Performance Evaluation (2011) 68 : 1222-1231, July 2011.

