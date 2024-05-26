# Explication de notre code

Notre menu principal «int main» a été réparti en 4 sous partis placées dans un switch
case:

## ➢ Explication du premier cas
Lorsque l'utilisateur choisit l'option 1 du menu principal pour créer un entraînement,
le programme suit les étapes suivantes. D’une part la saisie des informations de base
de l'entraînement est exécuté grâce à une fonction nommée «valideDate» qui a pour
rôle de vérifier si une date est valide. Cette fonction est utilisée pour valider la date
saisie par l'utilisateur pour l'entraînement. Elle vérifie que la date est dans un format
correct et correspond à une date valide dans le calendrier.
Ensuite, la fonction «viderBuff» qui a pour rôle de vider le tampon de saisie. Cette
fonction est appelée pour vider le tampon de saisie après que l'utilisateur a entré la
date de l'entraînement. Cela garantit qu'il n'y a pas de données résiduelles dans le
tampon.
De plus, concernant la définition des résultats par athlète, nous avons utilisé une
fonction nommée «definirResultatsParAthlete» qui a pour rôle de définir les résultats
pour chaque athlètes. Cette fonction est appelée pour chaque athlète participant à
l'entraînement. Elle permet à l'utilisateur de saisir les résultats spécifiques obtenus
lors d’un entraînement pour un athlète. Cela comprend le nom, l’épreuve, la date, la
position et le temps.
Pour finir, le rôle de la fonction «relaisExiste» est de déterminer si un relais à déjà eu
lieu à cette date. Si l'entraînement implique une épreuve de relais, cette fonction est
appelée pour être sur que la date saisie ne correspond pas a celle d’un relais déjà
existant. En effet, deux relais ne peuvent pas avoir lieu le même jour pour un athlète.
## ➢ Explications du deuxième cas
Le «case 2» a pour principal but de constituer l’historique d’un athlète selon plusieurs
catégorie.
Premièrement, nous demandons à l’utilisateur de saisir de le nom de l’athlète dont il
veut connaître l’historique. S’en suit une sécurité qui permet de prendre en compte le
cas où l’utilisateur saisirait un nom non existant, ou ferait une faute d’orthographe.
Ensuite, la procédure «tri_date» permet de créer un fichier dans lequel sera stocker la
fiche d’entraînement de l’athlète mis en paramètre, trié par date. L’utilisateur pourra
donc consulter ce fichier.

De surcroît, nous demandons à l’utilisateur si il veut consulter l’historique seulement
pour une épreuve de ce même athlète. Il s’en suit donc une sécurité permettant de
prendre en compte les cas où l’utilisateur répond: oui, non, ou autre. Si la réponse est
oui, et bien nous demandons à l’utilisateur de quel épreuve veut-il connaître
l’historique. En fonctions de sa réponse, la procédure «tri_epreuve_date» permet de
créer un fichier dans lequel sera trier, pour l’épreuve sélectionné la fiche de l’athlète
par date. L’utilisateur pourra consulter ce fichier.

## ➢ Explication du troisième cas
Le case 3 permet à l'utilisateur de consulter les statistiques des performances des
athlètes. Lorsqu'il sélectionne cette option, l'utilisateur peut choisir un athlète et une
épreuve pour voir un résumé de ses performances. Cela inclut le meilleur temps, le
pire temps et le temps moyen de l'athlète pour l'épreuve choisie. De plus,
l'entraîneur peut identifier les trois meilleurs athlètes pour chaque discipline en
fonction de leurs temps moyens, ce qui aide à décider quels athlètes envoyer aux
Jeux Olympiques.
Enfin, il est possible d'afficher la progression d'un athlète en comparant ses
performances entre deux dates pour la même épreuve. Cela permet de suivre
l'évolution de l'athlète et de prendre des décisions basées sur des données précises.

#### La fonction recupererdonnees 
lit les chronos d'un athlète pour une épreuve
spécifique (hors relais) à partir d'un fichier texte. Elle crée et retourne un tableau
dynamique contenant ces chronos, le premier élément indiquant le nombre de
chronos récupérés.
#### La fonction recupererdonnees1 
lit les chronos d'un athlète pour une épreuve de
relais à partir d'un fichier texte. Elle crée et retourne un tableau dynamique
contenant ces chronos, le premier élément indiquant le nombre de chronos
récupérés.
#### La procédure triInsertion 
trie un tableau de chronos en utilisant l'algorithme de tri
par insertion. À chaque étape, elle insère un élément du tableau à sa position
correcte par décalage des éléments plus grands vers la droite.
#### La fonction statistique 
calcule la moyenne, le meilleur et le pire temps d'un athlète
pour une épreuve spécifique (hors relais) à partir des chronos récupérés, trie les
chronos, et met à jour un fichier de statistiques avec les moyennes des athlètes pour
cette épreuve.
#### La fonction statistique1 
calcule la moyenne, le meilleur et le pire temps d'un relais
pour une épreuve spécifique en utilisant les chronos récupérés, puis retourne ces
valeurs dans un tableau dynamique.
#### La procédure afficheStatistique 
prend en paramètre le nom de l'athlète et le nom de
l'épreuve, puis utilise la fonction statistique pour obtenir les données (meilleur
temps, pire temps, moyenne) de l'athlète pour cette épreuve, et enfin affiche ces
données à l'écran.
#### La procédure afficheSatistique1 
prend en paramètre le nom de l'athlète et le nom de
l'épreuve de relais, puis utilise la fonction statistique1 pour obtenir les données
(meilleur temps, pire temps, moyenne) de l'athlète pour cette épreuve, et enfin
affiche ces données à l'écran.
#### La procédure Meilleurs_Athletes 
prend en paramètre le nom de l'épreuve et utilise la
fonction tri_moyennes pour trier les moyennes des athlètes dans l'ordre croissant.
Ensuite, elle lit les trois premières lignes du fichier trié pour afficher les trois
meilleurs athlètes avec leur moyenne de temps dans cette épreuve.
#### La procédure differenceTempsDates 
prend en paramètres le nom de l'athlète, le nom
de l'épreuve, ainsi que deux dates. Elle extrait les chronos de l'athlète pour l'épreuve
spécifiée aux deux dates données, puis calcule et affiche la différence de temps entre
ces deux chronos.
#### La procédure differenceTempsDates1 
fonctionne de manière similaire à differenceTempsDates, 
mais elle est spécifiquement conçue pour les épreuves de relais. Elle prend en paramètres 
le nom de l'athlète, le nom de l'épreuve de relais, ainsi que deux dates, 
extrait les chronos de l'athlète pour le relais spécifié aux deux
dates données, puis calcule et affiche la différence de temps entre ces deux chronos.

## ➢ Explication du quatrième cas
Cette dernière option permet simplement à l'utilisateur de quitter le menue principal.
