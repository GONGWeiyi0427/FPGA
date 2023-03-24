 # Rapport du TP FPGA
                                               
                                                 Weiyi GONG, Gr sesi
                                                 Zhuyu WEN, Gr syscom
* **Séance 1：1 ERE PARTIE – SYNTHESE VHDL SUR FPGA**
**I)Prise en main de la carte et des outils**
**1)Présentation de la carte Digilent Nexys
2)Création d’un projet avec le logiciel Vivado**
Pour les deux parties précédentes, nous avons suivi le sujet pas à pas.

**4)Testbench et simulation**

![](https://i.imgur.com/bTCDGwu.png)

Nous pouvons voir que l'image résultante correspond au sujet demandé:
LED(0)=SW0,LED(1)=SW1,LED(2)=SWO*SW1*SW2

**5)Implémentation sur la carte FPGA**
Et pour la partie 4) et 5), nous avons aussi suivi le sujet.Pour connecter la carte Basys 3,il faut changer le general-board-Basys3 dans le setting.

**II)Cas d’études – Synthèse VHDL
1)Compteurs Imbriqués**
Observation:

* ![](https://i.imgur.com/2NmMIC9.png)

Il décrite que chaque fois que nous appuyons sur le bouton_left, le compteur de 4bits augmentera progressivement d'un.Nous pouvons voir sur la carte que les quatre voyants de droite s'allumeront sous la forme 0001, 0010, 0011, 0100... à chaque appui.

* ![](https://i.imgur.com/53gPxp7.png)

Après la connexion, rien ne se passe sur la carte, si nous appuyons sur le bouton gauche, les quatre voyants LED sont allumés

Analyse

* ![](https://i.imgur.com/hlxlppq.png)

On obtient le Schematic comme au dessous:

![](https://i.imgur.com/TYlqxOq.png)

Il ne correspond au code VHDL de départ car le Clk et le Reset ne sont pas connectés dans le circuit.

* ![](https://i.imgur.com/4rp9rXY.png)

![](https://i.imgur.com/z8jhB8G.png)

Comme le problème on trouve dans le schématic,c'est clk et reset qui pose problème.Donc on vérifie le process(Clk,Reset) et on trouve que la taille du range de cpt est incorrecte.Donc on a changé d'abord le range du signal Cpt de 20000000 à 200000000 pour bien fonctioner le code,car le Cpt est équal à 70000000 ce qui devrait être inférieur au range du signal Cpt dans le code suivant.

correction et vérification

* ![](https://i.imgur.com/dWEE2EV.png)

Après la correction du code,nous pouvons voir que les 4 lumières LED à droite comptent automatiquement, en ajoutant une à chaque fois. Si nous appuyons et maintenons le bouton gauche enfoncé, les quatre voyants LED seront allumés.Ceci correspond au résultat qu'on attend précédent.
On obtient un nouveau schematic:

![](https://i.imgur.com/Waul1nk.png)



**2)Compteur d'Impulsions**
Observation

* ![](https://i.imgur.com/YNHCBov.png)

Le code VHDL décrite que si nous appuyons sur le bouton gauche, le compteur incrémente de un, et si nous appuyons sur le bouton du milieu, le compteur diminue de un.

* ![](https://i.imgur.com/X3od2AZ.png)

Ce testbench est pour tester le bouton_L toutes les 50ns entre 100ns et 350ns,et entre 700ns et 1550ns. Et il s'agit de tester le bouton_C toutes les 50ns entre 400ns et 500ns, et de tester le bouton_C une fois entre 500ns et 600ns.
Avant faire la simulation,il faut ajouter un clk dans le testbench.Sinon quand nous faisons la simulation,il y a des erreurs.

![](https://i.imgur.com/MltcRQ5.png)


Nous voyons que le schéma de simulation obtenu est cohérent avec ce que nous avons dit précédemment.

* ![](https://i.imgur.com/QEuIxnN.png)

Nous constatons que si nous appuyons sur le bouton gauche, le compteur incrémente de un, et si nous appuyons sur le bouton du milieu, le compteur diminue de un.Comme nous avons répondu pour la fonctionnalité décrite par le code impulse_count.vhd.

Analyse


![](https://i.imgur.com/q9o0phE.png)

Nous vérifions bien le target language est de VHDL.

* ![](https://i.imgur.com/zjPf9oG.png)

Le module UUT pré-synthèse:

![](https://i.imgur.com/0emoXqv.png =200x200)

Le module UUT post-synthèse:

![](https://i.imgur.com/TvjuUjT.png =200x300)

Nous voyons que après le synthèse,il y a plusieurs autres éléments dans le module UUT, tels que : Reset_IBUF, Sup_OBUF......

Mais pour le chronogramme,le comportement ne change pas,c'est la même que le chronogramme précédent:

![](https://i.imgur.com/7WNLzcV.png)



Correction et vérification

* ![](https://i.imgur.com/9dNpqig.png)

Pour fonctionner le compteur d'impulsion correctement,il faut ajouter deux variables q1,q2 pour enregistrer l'etat précédent du bouton.Ainsi,nous pouvons juger que le compteur peut compter avec précision chaque fois que le bouton a été poussé.
Après finir la modification du code,nous lancons la simulation schématique RTL et nous obtenons：

![](https://i.imgur.com/oNklyKO.png)

nous vérifions bien que le schéma correspond au code et il marche aussi sur la carte.

**3)Décodeur & Machine à Etats**
Observation

* ![](https://i.imgur.com/ZFEyZN1.png)

Ces codes doivent contrôler les quatre lumières LED pour qu'elles clignotent en même temps, et la taille du compteur peut contrôler la durée de l'intervalle de clignotement, plus le compteur est grand, plus l'intervalle de clignotement est long.

* ![](https://i.imgur.com/rWoV4WI.png)

![](https://i.imgur.com/rrKOKB6.png)

Nous mettons le fichier Top.vhd comme top level et nous connectons la carte.Nous appuyons 3 fois sur le bouton Left puis 1 fois sur le bouton Right et nous constatons que les 4 LEDs sont allumées mais ne clignotent pas.

* ![](https://i.imgur.com/LHFIOWZ.png) 

Nous voyons que après avoir tiré le Switch 0 vers le haut,les 4 LEDs sont éteintes.Après l'avoir remis vers le bas,les 4 LEDs sont allumées mais l'intensité lumineuse est plus faible qu'avant.

Analyse et Correction

* ![](https://i.imgur.com/WoVVko2.png)

Normalement, le problème est dans MAE.Lorsque nous avons vérifié le MAE, nous avons constaté qu'il manquait une étape dans chaque état.Cette étape est le cas où etat future revient à l'état actuel dans le cas de else.

Après modification de MAE, il n'y a pas de warning en synthèse et les LEDs sur la carte peuvent clignoter normalement.

![](https://i.imgur.com/vmui1SB.png)

* **Séance 2：2 EME PARTIE – CODESIGN MATERIEL/LOGICIEL**

**2)Spécification de la plate-forme matérielle**
Nous créerons un projet et ajoutons un IP (MicroBlaze) dans la fenêtre diagram. Nous cliquons sur Run Block Automation et il ajoute cinq modules distinctes automatiquement:
Clocking Wizard et Processor System Reset,Microblaze Debug Module,Microblaze Local Memory,AXI Interconnect,AXI Interrupt Controller.

Après nous ajoutons un nouveau IP--“led-switch”.Dans ce nouveau IP,le port 1 du bloc GPIO sera associé aux 4 interrupteurs à droite de la carte et le port 2 du bloc GPIO sera associé aux 16 LEDs.

Nous ajoutons une autre IP--“boutons”,il contient 1 port d’entrée de 3 bits et pouvant également interrompre le processeur. 

Après avoir cliqué sur Run Connection Automation, nous configurons les 5 périphériques: Périphérique boutons, Périphérique clk_wiz_1, Périphérique led_switch et Périphérique rst_clk_wiz_1_100M.
Nous obtenons:

![](https://i.imgur.com/o1k1o3F.png)

Apèrs renommer le port GPIO2 et relier les ports ip2intc_irpt avec les deux entrées du module Concat.Nous sauvgardons le Block Design et choisissons Validate Design et nous obtenons:

![](https://i.imgur.com/KimtkSQ.png)

**3)Implémentation de la plate-forme matérielle**
Nous ajoutons le fichier XDC sur moodle et modifions le nom du port(sys_clock)...(nous suivons le sujet)
Nous lancons le schématique et nous obtenons:

![](https://i.imgur.com/PiODXtt.png)

Nous pouvons voir que dans ce schéma tout s'est bien passé.

**4)Création des projets pour le développement logiciel sous Vitis**
Maintenant nous passons à Vitis qui nous permet de coder en langage C pour réaliser la fonction sur la carte Basy3.

**5)Développement de l’application logicielle**
Les 8 LED de gauche puissent clignoter si l’interrupteur 0 est relevé:

![](https://i.imgur.com/B3LRyrk.png)

Si l’interrupteur 1 est relevé,les 4 LED de droite affichent la valeur d’un compteur modulo 16 incrémenté par le bouton Center:

![](https://i.imgur.com/sCCrCff.png)

Si on appuie sur le bouton Left, les LED 7 à 4 s’allument et si on appuie sur le bouton Right, les 4 LED 7 à 4 s’éteignent:

![](https://i.imgur.com/8bhEQAf.png)

Faire un chenillard qui parcourt les 16 LEDs de la carte avec une vitesse de défilement paramétrable grâce aux 4 interrupteurs:

![](https://i.imgur.com/D67g0rp.png)

Il est difficile de capturer un chenillard devant la caméra,mais nous voyons quand même un peu que led clignotent de droite à gauche.

* **Séance 3：3 EME PARTIE – – CONCEPTION D’IP POUR LE MICROBLAZE**
Nous continuons le TP3 avec ce que nous avons fait en TP2.Nous suivons les instructions dans le sujet et décrivons un module VHDL dans le fichier my_led.vhd qui possède 1 entrée sur 4 bits et 1 sortie sur 16 bits...etc
Après nous ouvrons le Block design et nous obtenons les figures au dessous:

![](https://i.imgur.com/boIHyrK.png)

![](https://i.imgur.com/AyTsrnn.png)

Nous voyons que il y a 4 entrées et 16 sorties dans ce schéma qui répondent aux exigences dans le sujet.

Pour la partie du code,nous voulons que les 4 interrupteurs de droite contrôlent respectivement les leds sur les bits 15-12, 11-8, 7-4 et 3-0,comme indiqué ci-desssous:

![](https://i.imgur.com/ZCjJzfx.png)
