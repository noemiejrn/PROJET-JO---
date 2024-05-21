#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONGUEUR_FICHIER 50
#define MAX_LONGUEUR_SAISIE 100

// fonction pour vider la variable comme choix
void viderBuffer(void)
{
    int c;
    while((c=getchar()) != EOF && c != '\n');
}

// fonction pour verifier si la date est valide
int valideDate(int jour, int mois, int annee)
{
    // on verifie que le mois est compris entre 1 et 12 et que le jour est superieur a 1
    if (annee < 2000 || mois < 1 || mois > 12 || jour < 1)
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
        exit(1);
    }

    char epreuve[MAX_LONGUEUR_SAISIE];
    char date[MAX_LONGUEUR_SAISIE];
    float resultat ;

    int jour, mois, annee;
    int heures = -1;
    int minutes = -1;
    float secondes = -1;
    int n_epreuve ;
    int position ;
    char temps[12];



    do {

        printf("Entrez l'epreuve: \n");
        printf("(1) 100m \n");
        printf("(2) 400m \n");
        printf("(3) 5000m \n");
        printf("(4) marathon \n");
        printf("(5) relais \n");
        scanf("%d", &n_epreuve);

        if(n_epreuve >= 1 && n_epreuve <= 5 ) {

            printf("vous avez entre: %d \n", n_epreuve);

            do {
                printf("Entrez la date (JJ/MM/AAAA): \n" );
                scanf("%2d/%2d/%4d", &jour, &mois, &annee);

                if(valideDate(jour, mois, annee)){
                    // on formate la date comme JJ/MM/AAAA
                    sprintf(date, "%02d/%02d/%d", jour, mois, annee);
                }else{
                    printf("Erreur! Entrer une nouvelle date \n");
                    viderBuffer();
                }
            } while (valideDate(jour, mois, annee)==0);

            if (n_epreuve == 5) {
                do {
                    printf("Entrez la position de l'athlete dans le relais: ");
                    scanf("%d", &position);
                    if (position >= 1 && position <= 4) {
                        printf("la position de l'athlete est %d \n", position);
                    } else {
                        printf("Erreur! Entrez une position valide \n");
                        viderBuffer();
                    }
                }while(position < 1 || position > 4);
            }
            // capture du temps et sa conversion en minutes

            do{
                printf("Entrez le temps en hh:mm:ss.ss  \n ");
                scanf("%s",temps);
                sscanf(temps,"%d:%d:%f",&heures, &minutes, &secondes);

                if( heures >= 0 && heures <= 23 &&
                    minutes >=0 && minutes <= 59 &&
                    secondes >= 0 && secondes <= 59.99){
                    printf("le temps est de %2d:%2d:%f \n",heures, minutes, secondes);
                    resultat = heures * 3600 + minutes * 60 + secondes;

                }else{
                    printf("Erreur! Entrez un nouveau temps \n");
                    viderBuffer();
                }

            } while(heures < 0 || heures > 23 ||
                    minutes < 0 || minutes > 59 ||
                    secondes < 0 || secondes > 59.99);

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
                fprintf(fichier, "%s;%s;%s;%d;%f;\n", athlete, date, epreuve,position, resultat);
                // on ajoute la ligne athlete;date;epreuve;;resultat;
            else fprintf(fichier, "%s;%s;%s; ;%f;\n", athlete, date, epreuve, resultat);

            fclose(fichier);

            printf("Resultat pour %s dans %s est de %f secondes \n", athlete, epreuve, resultat);
            return;

        }else{
            printf("Erreur! le nombre entre n'est pas une proposition \n");
            viderBuffer();
        }
    } while (n_epreuve > 5);
}

void Afficher_Epreuve_Par_Athlete (char *athlete) {

    FILE* fichier = NULL;
    char c;
    char nom_fichier [MAX_LONGUEUR_SAISIE];

    // on copie le nom de l'athlete dans la variable nom_fichier
    strcpy(nom_fichier,athlete);

    // on ajoute .txt a la fin de nom_fichier
    strcat(nom_fichier,".txt");

    fichier = fopen(nom_fichier, "r");

    if (fichier != NULL)

    {
        // Afficher les entetes du tableau
        printf("| Athlete | Date | Epreuve | Position | Result |\n");
        printf("| ");

        // Boucle de lecture des caractères un à un tant qu'on n'est pas a la fin du fichier
        do
        {
            c = fgetc(fichier); // On lit le caractère
            // on remplace ; par |
            if (c == ';') printf(" | ");
                // sinon affiche le caractere
            else printf("%c", c);
            // on affiche | en debut de ligne
            if (c == '\n') printf("| ");

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
                viderBuffer();
                break;
        }

    } while (choix != 4 );

    return 0;
    }