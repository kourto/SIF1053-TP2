# SIF1053 - Architecture des ordinateurs
## TP2 - Les dispositifs arithmétiques
______________________________________________________________________________________________________
###### Pour ce TP, j'ai fait attention à ce que tout fonctionne correctement sur Windows (j'ai testé plusieurs fois et tout fonctionne correctement)  De plus, j'ai mis tout le code sur un seul fichier puisque ce TP contient beaucoup moins de ligne de code que le précédent donc ce sera plus simple pour le correcteur.

J'ai tout de même écrit le code sous une distribution Linux puisque j'ai rarement accès à l'ordinateur de ma conjointe (qui est sous Windows) car elle l'utilise pour faire du télétravail un minimum de 12 heures par jour depuis le début de la pandémie.

Donc n'ayant pas eu accès à Windows lors de l'écriture du TP, je n'ai pas pu utiliser les fonctions fopen_s, scanf_s et fscanf_s qui sont exclusives à Windows. Par contre, tout fonctionne bien sous Microsoft Studio Community grâce à une ligne de code qui ignore l'erreur C4996.

Dans la fonction division on doit faire une addition ainsi qu'une soustraction, j'ai donc préféré rester dans le même état d'esprit et de faire une fonction additionnel pour l'addition et une pour la soustraction qui font les calculs avec les opérateurs bitwises.

*J'ai aussi pris la liberté d'ajouter une fonction supplémentaire qui fait des tests sur la fonction division, elle vérifie que les résultats sont exactement ceux attendus en les comparants avec des résultats obtenus par des calculs faits avec l'opérateur de division et celui de modulo.*
______________________________________________________________________________________________________
#### Auteur : Yves Courteau
