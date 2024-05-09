#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 50
#define MAX_LINE_LENGTH 100


// fonction pour entrer un resultat pour un athlete
void setResultForAthlete(const char *athlete) {

    char filename[MAX_FILENAME_LENGTH];
    snprintf(filename, MAX_FILENAME_LENGTH, "%s.txt", athlete);

    FILE *file = fopen(filename, "a"); // mode ecriture
    if (file == NULL) {
        printf("Erreur pour ouvrir le fichier %s\n", athlete);
        return;
    }

    char epreuve[MAX_LINE_LENGTH];
    char date[MAX_LINE_LENGTH];
    char resultat[MAX_LINE_LENGTH];

    printf("Entrez l'épreuve: ");
    scanf("%s", epreuve);

    printf("Entrez la date (YYYY-MM-DD): ");
    scanf("%s", date);

    printf("Entrez le resultat: ");
    scanf("%s", resultat);

    fprintf(file, "%s;%s;%s\n", date, epreuve, resultat);
    fclose(file);

    printf("Resultat pour %s dans %s est de.\n", athlete, epreuve);
}

void Afficher_Epreuve_Par_Athlete (char *athlete) {

    FILE* fichier = NULL;
    char c;
    char nom_fichier [250];

    strcpy(nom_fichier,athlete);
    strcat(nom_fichier,".txt");

    /*on rajoute l'extension .txt au nom de l'athlete */
    fichier = fopen(nom_fichier, "r");

    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un
        do
        {
            c = fgetc(fichier); // On lit le caractère
            if (c == ';') printf(" | ");
            else printf("%c", c);

        } while (c != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

        fclose(fichier);
    }
}

int main() {

    int choix;
    char athlete[MAX_LINE_LENGTH];

    printf("\033c" );
    printf("******** Menu Principal ******** \n");
    printf("(1) Saisir Entrainement \n");
    printf("(2) Historiques \n");
    printf("(3) Statistiques \n");
    printf("(4) Quitter  \n");

    printf("Choix: ");
    scanf("%d", &choix);

    switch (choix)
    {
        case 1 /* creer un entrainement */:

            printf("Entrez le nom de l'athlete: ");
            scanf("%s", athlete);
            setResultForAthlete(athlete);
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
            printf("ce choix n'est pas possible");
            break;
    }

    return 0;

}tyftyftyfytfytftfuy

