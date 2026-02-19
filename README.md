# 🦾 OBRAS - Bras Robotisé à Détection de Couleurs Automatisée

## 📌 Présentation du Projet
[cite_start]Réalisé dans le cadre de ma 2ème année de classes préparatoires intégrées à l'**EIDIA (Université Euro-Méditerranéenne de Fès)**[cite: 59, 66], le projet **OBRAS** consiste en la conception et la programmation d'un bras robotisé intelligent. 

[cite_start]L'objectif est d'automatiser le tri d'objets : le système détecte la couleur d'un élément via un capteur optique, le saisit, puis le dépose dans un bac de stockage correspondant[cite: 79, 102]. Ce projet démontre des compétences en **électronique embarquée**, **programmation C/C++ (Arduino)** et **mécatronique**.

## 🛠️ Caractéristiques Techniques
* [cite_start]**Contrôleur Central** : Arduino MEGA[cite: 80].
* [cite_start]**Capteur de Vision** : TCS3200 (Module de reconnaissance de couleurs par fréquence)[cite: 83].
* [cite_start]**Actionneurs** : 5 Servomoteurs pilotant les axes du bras et la pince de préhension[cite: 132].
* [cite_start]**IHM (Interface Homme-Machine)** : Système de diagnostic par LEDs (Bleu, Jaune, Rouge) pour confirmer la détection en temps réel[cite: 100, 119].
* [cite_start]**Matériaux** : Structure conçue en plexiglas et carton (épaisseur 3mm) pour allier légèreté et robustesse[cite: 100, 123].


## 📸 Galerie du Prototype
Le prototype a été entièrement conçu et assemblé manuellement, utilisant une structure hybride en carton et plexiglas pour tester les algorithmes de tri.

| Vue d'ensemble du système | Focus sur la Pince et Capteur |
|:---:|:---:|
| ![Vue d'ensemble](images/vue_ensemble.jpeg) | ![Pince](images/pince_robotique.jpeg) |
| *Intégration de l'Arduino MEGA et du banc de tri* | *Détail du capteur TCS3200 et des servomoteurs de la pince* |

### Détails du Montage
* [cite_start]**Détection Optique** : Utilisation du capteur TCS3200 avec un éclairage LED intégré pour une lecture précise des fréquences RGB[cite: 83, 87].
![Capteur de couleur](images/capteur_couleur.jpeg)

* [cite_start]**Électronique Embarquée** : Câblage structuré sur breadboard incluant la gestion de l'alimentation des 5 servomoteurs et du bus de données[cite: 80, 85].
![Câblage](images/cablage_electronique.jpeg)

* [cite_start]**Structure et Mécanique** : Conception du bras articulé permettant une amplitude de mouvement nécessaire au balayage des zones de tri[cite: 88, 89].
![Structure](images/structure_bras.jpeg)

* [cite_start]**Zone de Tri Final** : Compartiments colorés (Jaune, Bleu, Rouge) pour la validation visuelle du succès de l'algorithme de classement[cite: 107, 108].
![Tri final](images/tri_final.jpeg)


## 🧠 Algorithme et Logique Embarquée
[cite_start]Le logiciel, développé en langage **C sur Arduino IDE**, repose sur une architecture modulaire pour optimiser l'utilisation de la mémoire[cite: 81, 82].

1.  [cite_start]**Phase de Calibration** : Analyse des fréquences RGB (Red, Green, Blue) via le capteur TCS3200[cite: 105, 115].
2.  [cite_start]**Traitement du Signal** : Comparaison des données reçues avec des seuils (thresholds) prédéfinis pour identifier la couleur exacte[cite: 132].
3.  [cite_start]**Cinématique du Bras** : Déclenchement d'une séquence de mouvements fluides (`moveBlock`) pour la saisie et le tri[cite: 132].
4.  [cite_start]**Gestion de la Sûreté** : Retour à une position de veille (`moveServoStart`) après chaque cycle[cite: 132].

## 📁 Structure du Dépôt
* `/src` : Contient le code source principal (`detector3.ino`).
* `/docs` : Documentation technique et rapport de projet.
* `/images` : Photographies du prototype physique et des tests.

## 🚀 Compétences Valorisées
* **Développement Embarqué** : Programmation bas niveau, gestion des interruptions et des timers.
* **Intégration Hardware** : Câblage de capteurs industriels et gestion de la puissance (servomoteurs).
* [cite_start]**Méthodologie Projet** : De l'établissement du plan d'action aux phases de tests unitaires et d'intégration[cite: 109, 125].

---
*Projet réalisé par **Vanelle Stéphanie MANGOUA DJOUSSEU** dans le cadre de mon cursus ingénieur.*