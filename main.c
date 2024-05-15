#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONGUEUR_FICHIER 50
#define MAX_LONGUEUR_SAISIE 100

// fonction pour verifier si la date est valide
int valideDate(int jour, int mois, int annee)
{
    // on verifie que le mois est compris entre 1 et 12 et que le jour est superieur a 1
    if (annee < 0 || mois < 1 || mois > 12 || jour < 1)
        return 0;
    // on teste que le jour n'excede pas 30 pour les mois de avril, juin, septembre et novembre
    if (mois == 4 || mois == 6 || mois == 9 || mois == 11) {
        if (jour > 30) return 0;
        // on teste que le jour n'excede pas 29 ou 28 pour le mois de fevrier selon que l'annee soit bissextile ou non
    } else if (mois == 2) {
        if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
            // l'annee est bissextile
            if (jour > 29) return 0;
        } else {
            // l'annee n'est pas bissextile
            if (jour > 28) return 0;
        }
    }
        // on teste le jour pour tous les autres mois restant finissant en 31
    else if (jour > 31) {
        return 0;
    }

    return 1;
}

// fonction pour entrer un resultat pour un athlete
void Definir_Resultat_Par_Athlete(const char *athlete) {

    char nom_fichier[MAX_LONGUEUR_FICHIER];

    // on copie le nom de l'athlete dans la variable nom_fichier
    strcpy(nom_fichier,athlete);
    // on ajoute l'extension .txt a nom_fichier
    strcat(nom_fichier,".txt");

    // on ouvre le fichier en mode ecriture et si le fichier n'existe pas on le cree
    FILE *fichier = fopen(nom_fichier, "a");
    if (fichier == NULL) {
        printf("Erreur pour ouvrir le fichier %s\n", athlete);
        return;
    }

    char epreuve[MAX_LONGUEUR_SAISIE];
    char date[MAX_LONGUEUR_SAISIE];
    char resultat[MAX_LONGUEUR_SAISIE];
    int jour, mois, annee;
    int n_epreuve ;
    int position ;

    do {

        printf("Entrez l'epreuve: \n");
        printf("(1) 100m \n");
        printf("(2) 400m \n");
        printf("(3) 5000m \n");
        printf("(4) marathon \n");
        printf("(5) relais \n");
        scanf("%d", &n_epreuve);

        if(n_epreuve >= 1 && n_epreuve <= 5) {

            printf("vous avez entré: %d \n", n_epreuve);

            do {
                printf("Entrez la date (JJ/MM/AAAA): \n" );
                scanf("%d/%d/%d", &jour, &mois, &annee);

                if(valideDate(jour, mois, annee)){
                    // printf("la date est: %d/%d/%d \n",jour, mois, annee);
                    sprintf(date, "%d/%d/%d", jour, mois, annee);
                }else{
                    printf("erreur! Entrer une nouvelle date \n");
                }
            } while (valideDate(jour, mois, annee)==0);

            if (n_epreuve == 5) {
                printf("Entrez la position de l'athlete dans le relais: ");
                scanf("%d",&position);
            }

            printf("Entrez le resultat: ");
            scanf("%s", resultat);

            switch(n_epreuve){
                case 1 :
                    strcpy(epreuve,"100m");
                    break;
                case 2 :
                    strcpy(epreuve,"400m");
                    break;
                case 3 :
                    strcpy(epreuve,"5000m");
                    break;
                case 4 :
                    strcpy(epreuve,"marathon");
                    break;
                case 5 :
                    strcpy(epreuve,"relais");
                    break;
            }

            if (n_epreuve == 5)
                // on ajoute la ligne athlete;date;epreuve;position;resultat;
                fprintf(fichier, "%s;%s;%s;%d;%s;\n", athlete, date, epreuve,position, resultat);
                // on ajoute la ligne athlete;date;epreuve;resultat;
            else fprintf(fichier, "%s;%s;%s;%s;\n", athlete, date, epreuve, resultat);

            fclose(fichier);
            printf("Resultat pour %s dans %s est de %s\n", athlete, epreuve, resultat);

        }else{
            printf("erreur! le nombre entre n'est pas une proposition \n");
        }
    } while (n_epreuve > 5);
}

void Afficher_Epreuve_Par_Athlete (char *athlete) {

    FILE* fichier = NULL;
    char c;
    char nom_fichier [250];

    // on copie le nom de l'athlete dans la variable nom_fichier
    strcpy(nom_fichier,athlete);

    // on ajoute .txt a la fin de nom_fichier
    strcat(nom_fichier,".txt");

    fichier = fopen(nom_fichier, "r");

    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un tant qu'on n'est pas a la fin du fichier
        do
        {
            c = fgetc(fichier); // On lit le caractère
            if (c == ';') printf(" | ");
            else printf("%c", c);

        } while (c != EOF);

        fclose(fichier);
    }
}

int main() {

    int choix;
    char athlete[MAX_LONGUEUR_SAISIE];

    printf("\033c" );

    // on affiche le menu tant que choix est different de 4

    do {
        // on affiche le menu principal
        printf("******** Menu Principal ******** \n");
        printf("(1) Saisir Entrainement \n");
        printf("(2) Historiques \n");
        printf("(3) Statistiques \n");
        printf("(4) Quitter  \n");
        printf("Choix: ");
        scanf("%d", &choix);

        // on teste choix et on execute le mode choisi

        switch (choix)
        {
            case 1 /* creer un entrainement */:
                printf("Entrez le nom de l'athlete: ");
                scanf("%s", athlete);
                Definir_Resultat_Par_Athlete(athlete);
                break;

            case 2 /* Voir Historiques */:
                printf("saisir nom de l'athele:");
                scanf("%s",athlete);
                Afficher_Epreuve_Par_Athlete (athlete);
                break;

            case 3 /* Voir Statistiques */:
                printf("3 \n");
                break;

            case 4 /* Quitter */:
                printf("4 \n");
                break;

            default:
                printf("ce choix n'est pas possible \n");
                break;
        }

    } while (choix != 4 );

    return 0;

}