#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONGUEUR_FICHIER 50
#define MAX_LONGUEUR_SAISIE 100

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct{
    char nom[50];
    Date date;
    char epreuve[50];
    float temps;
}Athlete;

typedef struct{
    char *nom;
    float moyenne;
}AthleteMoyenne;

void tri_insertion(Athlete arr[], int n) {
    int i, j;
    Athlete key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Comparer les dates
        while (j >= 0 &&
               (arr[j].date.annee > key.date.annee ||
                (arr[j].date.annee == key.date.annee && arr[j].date.mois > key.date.mois) ||
                (arr[j].date.annee == key.date.annee && arr[j].date.mois == key.date.mois && arr[j].date.jour > key.date.jour))) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }arr[j + 1] = key;
    }
}

void tridate_1athlete(const char *fichier_entree_nom) {

    printf("test -1\n");
    const char *fichier_sortie_nom = "fichier_tri.txt";
    FILE *fichier_entree = fopen(fichier_entree_nom, "r");
    if (fichier_entree == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        exit(2);
    }
    Athlete fiches[100];
    int i = 0;
    char ligne[200];
    while (fgets(ligne, 199, fichier_entree)) {
        if (sscanf(ligne, "%49s %d/%d/%d %49s %f",
                   fiches[i].nom,
                   &fiches[i].date.jour,
                   &fiches[i].date.mois,
                   &fiches[i].date.annee,
                   fiches[i].epreuve,
                   &fiches[i].temps) == 6) {
            i++;
        }
    }
    fclose(fichier_entree);

    // Trier les fiches par date en utilisant le tri par insertion
    tri_insertion(fiches, i);
    FILE *fichier_sortie = fopen(fichier_sortie_nom, "w");
    if (fichier_sortie == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        exit(2);
    }
    for (int k = 0; k < i; k++) {
        fprintf(fichier_sortie, "%s | %d/%d/%d | %s | %.2f\n",
                fiches[k].nom,
                fiches[k].date.jour,
                fiches[k].date.mois,
                fiches[k].date.annee,
                fiches[k].epreuve,
                fiches[k].temps);
    }
    fclose(fichier_sortie);
}


void verifsauvegarde (char *athlete){
    FILE*fichier;
    fichier=fopen("sauvegarde.txt","r+");
    if (fichier==NULL){
        printf("erreur lors de l'ouverture du fichier");
        exit(1);
    }
    char save[50];
    int c=0;
    while(fgets(save,49, fichier)){
        //parcourir la chaine de carctère save jusqu'au caractère \n et renvoie la case la chaine en rajoutant
        save[strspn(save,"\n")]='\0';
        if(strcmp(save,athlete)==0){
            c++;
            break;
        }
    }
    fclose(fichier);
}

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

// fonction pour verifier si un relais existe deja a une date pour un athlete
int relais_existe(char *nom_fichier, char *date, char *athlete){

    char ligne[MAX_LONGUEUR_SAISIE];
    char fichier_athlete[MAX_LONGUEUR_SAISIE];
    char fichier_date[MAX_LONGUEUR_SAISIE];
    char fichier_epreuve[MAX_LONGUEUR_SAISIE];

    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur pour ouvrir le fichier %s\n", athlete);
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%s %s %s", fichier_athlete, fichier_date, fichier_epreuve);

        if (strcmp(fichier_date, date) == 0 && strcmp(fichier_epreuve, "relais") == 0) {
            fclose(fichier);
            return 1;
        }
    }
    fclose(fichier);
   return 0;
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

    Date dates;
    dates.jour = -1;
    dates.mois = -1;
    dates.annee = -1;
    int heures = -1;
    int minutes = -1;
    float secondes = -1;
    int n_epreuve = -1 ;
    int position = -1 ;
    char temps[12];

    verifsauvegarde(nom_fichier);
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
                scanf("%d/%d/%d", &dates.jour, &dates.mois, &dates.annee);

                if(valideDate(dates.jour, dates.mois, dates.annee)){
                    // on formate la date comme JJ/MM/AAAA
                    sprintf(date, "%d/%d/%d", dates.jour, dates.mois, dates.annee);

                    if(relais_existe(nom_fichier, date, athlete) ==1) {
                        printf("il existe deja un relais a cette date \n");
                        viderBuffer();
                    }

                }else{
                    printf("Erreur! Entrer une nouvelle date \n");
                    viderBuffer();
                }
            } while ((valideDate(dates.jour, dates.mois, dates.annee)==0) || (relais_existe(nom_fichier, date, athlete) ==1));


            if (n_epreuve == 5) {
                do {
                    printf("Entrez la position de l'athlete dans le relais:\n ");
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
                scanf("%11s",temps);
                sscanf(temps,"%d:%d:%f",&heures, &minutes, &secondes);

                if( heures >= 0 && heures <= 23 &&
                    minutes >=0 && minutes <= 59 &&
                    secondes >= 0 && secondes <= 59.99 &&
                    temps[8] == '.' && temps[2] == ':' &&
                    temps[5] == ':'){
                    printf("le temps est de %2d:%2d:%f \n",heures, minutes, secondes);
                    resultat = heures * 3600 + minutes * 60 + secondes;

                }else{
                    printf("Erreur! Entrez un nouveau temps \n");
                    viderBuffer();
                }

            } while(heures < 0 || heures > 23 ||
                    minutes < 0 || minutes > 59 ||
                    secondes < 0 || secondes > 59.99 ||
                    temps[8] != '.' || temps[2] != ':' ||
                    temps[5] != ':');

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
                // on ajoute la ligne athlete date epreuve position resultat;
                fprintf(fichier, "%s %d/%d/%d %s %d %f\n", athlete, dates.jour, dates.mois, dates.annee, epreuve,position, resultat);
                // on ajoute la ligne athlete date epreuve  resultat;
            else fprintf(fichier, "%s %d/%d/%d %s %f\n", athlete, dates.jour, dates.mois, dates.annee, epreuve, resultat);

            fclose(fichier);

            printf("Resultat pour %s dans %s est de %f secondes \n", athlete, epreuve, resultat);
            return;

        }else{
            printf("Erreur! le nombre entre n'est pas une proposition \n");
            viderBuffer();
        }
    } while (n_epreuve < 1 || n_epreuve > 5);
}



float * recupererdonnees(char *athlete, char *epreuve) {
    FILE *fichier = NULL;
    char c;
    char nom_fichier[MAX_LONGUEUR_SAISIE];
    strncpy(nom_fichier, athlete, MAX_LONGUEUR_SAISIE-1);
   /* strcat(nom_fichier,"_");
    strcat(nom_fichier,epreuve);
    // on ajoute .txt a la fin de nom_fichier*/
    strcat(nom_fichier, ".txt");

    fichier = fopen(nom_fichier, "r");

    if (fichier != NULL) {
        int nb_chronos = 0; // Nombre de chronos lus
        float chrono; //le temps de l'athlète

        // Lire chaque ligne du fichier
        //quand lis un ; il pass
        Athlete fiches[100];
        int i=1;
        char lignes[200];
        while (fgets(lignes, 199, fichier)) {
            if (sscanf(lignes, "%49s %d/%d/%d %49s %f",
                       fiches[i].nom,
                       &fiches[i].date.jour,
                       &fiches[i].date.mois,
                       &fiches[i].date.annee,
                       fiches[i].epreuve,
                       &fiches[i].temps) == 6) {

                i++;

            }
        }

        float *chronos = malloc((i ) * sizeof(float));
        if (chronos == NULL) {
            printf("erreur d'allocation de la mémoire\n");
            exit(1);
        }
        rewind(fichier);
        chronos[0] = (float)i ;
        for (int j = 1; j <= i; j++) {
            chronos[j]=fiches[j].temps;
        }
        fclose(fichier);
        return chronos;
    }else{
        fclose(fichier);
        exit(1);
    }
}

// Procédure de tri par insertion pour des chronos
void triInsertion(float A[], int n) {
    int noetape, decalage;
    float temp;

    for (noetape = 1; noetape < n; noetape++) {
        temp = A[noetape];
        decalage = noetape - 1;

        while (decalage >= 0 && A[decalage] > temp) {
            A[decalage + 1] = A[decalage];
            decalage = decalage - 1;
        }

        A[decalage + 1] = temp;
    }
}

float * statistique ( char *athlete,  char *epreuve) {

    float *a = recupererdonnees(athlete, epreuve);
    int taille = (int)a[0];

    triInsertion(a + 1, taille-1);

    float moyenne = 0;
    for (int i = 1; i < taille; i++) {
        moyenne += a[i];
    }
    float vraimoyenne = moyenne / 2;


    float *tab = malloc(3 * sizeof(float));
    tab[0]=a[taille-1];
    tab[1]=a[1];
    tab[2]=vraimoyenne;
    AthleteMoyenne top_athlete;
    strncpy(top_athlete.nom, athlete,49);
    top_athlete.moyenne=tab[2];
    FILE*fichier= fopen("statistiquess.txt","r+");
    fprintf(fichier,"%s %s %f\n",top_athlete.nom, epreuve ,top_athlete.moyenne);
    fclose(fichier);

    free(a);

    return tab;
}

void afficheSatistique( char *athlete, char* epreuve) {

    float *tab = statistique(athlete, epreuve);
    printf("le meilleur temps de l'athlete %s au %s est %f  \n", athlete, epreuve, tab[1]);
    printf("le pire temps de l'athlete %s au %s est %f \n ", athlete, epreuve, tab[0]);
    printf("la moyenne de l'athlète %s pour l'épreuve %s est %f\n", athlete, epreuve, tab[2]);
    free(tab);
}


void afficher_top_athletes(char *epreuve, int nb_athletes, AthleteMoyenne *athletes) {
    // Tri des athlètes en fonction de la moyenne
    for (int i = 0; i < nb_athletes - 1; i++) {
        for (int j = i + 1; j < nb_athletes; j++) {
            if (athletes[i].moyenne > athletes[j].moyenne) {
                AthleteMoyenne temp = athletes[i];
                athletes[i] = athletes[j];
                athletes[j] = temp;
            }
        }
    }

    // Affichage des 3 meilleurs athlètes
    printf("Les meilleurs athlètes pour l'épreuve %s:\n", epreuve);
    for (int i = 0; i < 3 && i < nb_athletes; i++) {
        printf("%s : %.2f secondes\n", athletes[i].nom, athletes[i].moyenne);
    }
}


void Meilleurs_Athletes(char *epreuve){
    AthleteMoyenne athlete;
    FILE*fichier;
    if(strcmp(epreuve, "100m")==0) {
        fichier = fopen("statistiquess100m.txt", "r+");
    }
    else if(strcmp(epreuve, "400m")==0) {
        fichier = fopen("statistiquess400m.txt", "r+");
    }
    else if(strcmp(epreuve, "5000m")==0) {
        fichier = fopen("statistiquess5000m.txt", "r+");
    }
    else if(strcmp(epreuve, "marathon")==0) {
        fichier = fopen("statistiquessmarathon.txt", "r+");
    }else{
        exit(1);
    }
    //nom procedure de  tri de nono
    for (int i=0; i<3; i++){
        fscanf(fichier, "%s %f\n",athlete.nom, &athlete.moyenne);
        if (i==0){
            printf("l'athlete %s est le premier avec la meilleure moyenne de temps, %f, dans l'épreuve %s\n",athlete.nom, athlete.moyenne, epreuve);
        }
        if (i==1){
            printf("l'athlete %s est le deuxième avec la  moyenne de temps, %f, dans l'épreuve %s\n",athlete.nom, athlete.moyenne, epreuve);
        }
        if (i==2){
            printf("l'athlete %s est le troisième avec la  moyenne de temps, %f, dans l'épreuve %s\n",athlete.nom, athlete.moyenne, epreuve);
        }
    }
}


void differenceTempsDates(char *athlete, char *epreuve, Date a, Date  b){
    FILE *fichier = NULL;
    char nom_fichier[MAX_LONGUEUR_SAISIE];
    strncpy(nom_fichier, athlete, MAX_LONGUEUR_SAISIE-1);
   // strcat(nom_fichier,"_");
    //strcat(nom_fichier,epreuve);
    // on ajoute .txt a la fin de nom_fichier
    strcat(nom_fichier, ".txt");

    fichier = fopen(nom_fichier, "r");

    if (fichier != NULL) {
        float *chrono=malloc(2*sizeof(float));
        char lignes[200];
        Athlete fiches[100];
        int i=1;
        while (fgets(lignes, 199, fichier)) {
            if (sscanf(lignes, "%49s %d/%d/%d %49s %f",
                       fiches[i].nom,
                       &fiches[i].date.jour,
                       &fiches[i].date.mois,
                       &fiches[i].date.annee,
                       fiches[i].epreuve,
                       &fiches[i].temps) == 6) {

        }

            if (fiches[i].date.jour==a.jour && fiches[i].date.mois==a.mois && fiches[i].date.annee==a.annee){
                chrono[0]=chrono[i];
                i++;
            }
            if (fiches[i].date.jour==b.jour && fiches[i].date.mois==b.mois && fiches[i].date.annee==b.annee) {
                chrono[1]=chrono[i];
            }
        }
        float difference= chrono[0]-chrono[1];
        if(difference<0){
            difference=chrono[1]-chrono[0];
        }
        printf(" entre %d/%d/%d et %d/%d/%d, avec pour temps respectif %f, %f est de %f",a.jour, a.mois,a.annee,b.jour, b.mois, b.annee,chrono[0],chrono[1],difference);
        free(chrono);
    }

}

int main() {
    if(fopen("sauvegarde.txt", "r") == NULL){
        FILE *sauvegarde = fopen("sauvegarde.txt", "w");
        fclose(sauvegarde);
    }
    if(fopen("statistiquess100m.txt", "r") == NULL){
        FILE *statistiquess100m = fopen("statistiquess100m.txt", "w");
        fclose(statistiquess100m);
    }
    if(fopen("statistiquess400m.txt", "r") == NULL){
        FILE *statistiquess400m = fopen("statistiquess400m.txt", "w");
        fclose(statistiquess400m);
    }
    if(fopen("statistiquess5000m.txt", "r") == NULL){
        FILE *statistiquess5000m = fopen("statistiquess5000m.txt", "w");
        fclose(statistiquess5000m);
    }
    if(fopen("statistiquessmarathon.txt", "r") == NULL){
        FILE *statistiquessmarathon = fopen("statistiquessmarathon.txt", "w");
        fclose(statistiquessmarathon);
    }
    int choix = -1;
    char athlete[MAX_LONGUEUR_SAISIE];


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
                tridate_1athlete(athlete);
                break;

        case 3 /* Voir Statistiques */:
            printf("saisir nom de l'athele:");
            scanf("%s",athlete);
                char *epreuve=malloc (10);
                if(epreuve==NULL){
                    exit(1);
                }
                Date date1;
                Date date2;
                int n_epreuve;


                printf("Entrez l'epreuve: \n");
                printf("(1) 100m \n");
                printf("(2) 400m \n");
                printf("(3) 5000m \n");
                printf("(4) marathon \n");
                printf("(5) relais \n");
                scanf("%d", &n_epreuve);
                switch(n_epreuve) {
                    case 1 /* 100m */:
                        //on nomme la chaîne de caractère épreuve en fonction du choix de l'épreuve
                        strcpy(epreuve, "100m");
                        printf("vous avez choisi l'épreuve %s", epreuve);

                        printf("Les statistiques de l'athlète %s pour l'épreuve %s:\n", athlete, epreuve);
                        afficheSatistique(athlete, epreuve);

                       printf(" Connaître les 3 meilleurs athlètes à l'épreuve %s: \n", epreuve);
                        Meilleurs_Athletes(epreuve);

                        do {
                            printf("Entrez la date (JJ/MM/AAAA) que vous voulez observer: \n" );
                            scanf("%2d/%2d/%4d", &date1.jour, &date1.mois, &date1.annee);

                            if(valideDate(date1.jour, date1.mois, date1.annee)){
                                // on formate la date comme JJ/MM/AAAA
                                do {
                                    printf("Entrez la deuxième date (JJ/MM/AAAA) à laquelle vous voulez observer la différence de temps avec la première: \n" );
                                    scanf("%2d/%2d/%4d", &date2.jour, &date2.mois, &date2.annee);

                                    if(valideDate(date2.jour, date2.mois, date2.annee)){
                                        // on formate la date comme JJ/MM/AAAA
                                        differenceTempsDates(athlete, epreuve, date1, date2);
                                    }else{
                                        printf("Erreur! Entrer une nouvelle date \n");
                                        viderBuffer();
                                    }
                                } while (valideDate(date2.jour, date2.mois, date2.annee)==0);
                            }else{
                                printf("Erreur! Entrer une nouvelle date \n");
                                viderBuffer();
                            }
                        } while (valideDate(date2.jour, date2.mois, date2.annee)==0);
                        break;

                    case 2 /* 400m */:
                        //on nomme la chaîne de caractère épreuve en fonction du choix de l'épreuve
                        strcpy(epreuve, "400m");
                        printf("vous avez choisi l'épreuve %s", epreuve);

                        printf("Les statistiques de l'athlète %s pour l'épreuve %s:\n", athlete, epreuve);
                        afficheSatistique(athlete, epreuve);

                        printf(" Connaître les 3 meilleurs athlètes à l'épreuve %s: \n", epreuve);
                        Meilleurs_Athletes(epreuve);

                        do {
                            printf("Entrez la date (JJ/MM/AAAA) que vous voulez observer: \n" );
                            scanf("%2d/%2d/%4d", &date1.jour, &date1.mois, &date1.annee);

                            if(valideDate(date1.jour, date1.mois, date1.annee)){
                                // on formate la date comme JJ/MM/AAAA
                                do {
                                    printf("Entrez la deuxième date (JJ/MM/AAAA) à laquelle vous voulez observer la différence de temps avec la première: \n" );
                                    scanf("%2d/%2d/%4d", &date2.jour, &date2.mois, &date2.annee);

                                    if(valideDate(date2.jour, date2.mois, date2.annee)){
                                        // on formate la date comme JJ/MM/AAAA
                                        differenceTempsDates(athlete, epreuve, date1, date2);
                                    }else{
                                        printf("Erreur! Entrer une nouvelle date \n");
                                        viderBuffer();
                                    }
                                } while (valideDate(date2.jour, date2.mois, date2.annee)==0);
                            }else{
                                printf("Erreur! Entrer une nouvelle date \n");
                                viderBuffer();
                            }
                        } while (valideDate(date2.jour, date2.mois, date2.annee)==0);
                        break;

                    case 3 /* 5000m */:
                        //on nomme la chaîne de caractère épreuve en fonction du choix de l'épreuve
                        strcpy(epreuve, "5000m");
                        printf("vous avez choisi l'épreuve %s", epreuve);

                        printf("Les statistiques de l'athlète %s pour l'épreuve %s:\n", athlete, epreuve);
                        afficheSatistique(athlete, epreuve);

                        printf(" Connaître les 3 meilleurs athletes à l'épreuve %s: \n", epreuve);
                        Meilleurs_Athletes(epreuve);

                        do {
                            printf("Entrez la date (JJ/MM/AAAA) que vous voulez observer: \n" );
                            scanf("%2d/%2d/%4d", &date1.jour, &date1.mois, &date1.annee);

                            if(valideDate(date1.jour, date1.mois, date1.annee)){
                                // on formate la date comme JJ/MM/AAAA
                                do {
                                    printf("Entrez la deuxième date (JJ/MM/AAAA) à laquelle vous voulez observer la différence de temps avec la première: \n" );
                                    scanf("%2d/%2d/%4d", &date2.jour, &date2.mois, &date2.annee);

                                    if(valideDate(date2.jour, date2.mois, date2.annee)){
                                        // on formate la date comme JJ/MM/AAAA
                                        differenceTempsDates(athlete, epreuve, date1, date2);
                                    }else{
                                        printf("Erreur! Entrer une nouvelle date \n");
                                        viderBuffer();
                                    }
                                } while (valideDate(date2.jour, date2.mois, date2.annee)==0);
                            }else{
                                printf("Erreur! Entrer une nouvelle date \n");
                                viderBuffer();
                            }
                        } while (valideDate(date2.jour, date2.mois, date2.annee)==0);
                        break;

                    case 4 /* marathon */:
                        //on nomme la chaîne de caractère épreuve en fonction du choix de l'épreuve
                        strcpy(epreuve, "marathon");
                        printf("vous avez choisi l'épreuve %s", epreuve);

                        printf("Les statistiques de l'athlète %s pour l'épreuve %s:\n", athlete, epreuve);
                        afficheSatistique(athlete, epreuve);

                        printf(" Connaître les 3 meilleurs athletes à l'épreuve %s: \n", epreuve);
                        Meilleurs_Athletes(epreuve);

                        do {
                            printf("Entrez la date (JJ/MM/AAAA) que vous voulez observer: \n" );
                            scanf("%2d/%2d/%4d", &date1.jour, &date1.mois, &date1.annee);

                            if(valideDate(date1.jour, date1.mois, date1.annee)){
                                // on formate la date comme JJ/MM/AAAA
                                do {
                                    printf("Entrez la deuxième date (JJ/MM/AAAA) à laquelle vous voulez observer la différence de temps avec la première: \n" );
                                    scanf("%2d/%2d/%4d", &date2.jour, &date2.mois, &date2.annee);

                                    if(valideDate(date2.jour, date2.mois, date2.annee)){
                                        // on formate la date comme JJ/MM/AAAA
                                        differenceTempsDates(athlete, epreuve, date1, date2);
                                    }else{
                                        printf("Erreur! Entrer une nouvelle date \n");
                                        viderBuffer();
                                    }
                                } while (valideDate(date2.jour, date2.mois, date2.annee)==0);
                            }else{
                                printf("Erreur! Entrer une nouvelle date \n");
                                viderBuffer();
                            }
                        } while (valideDate(date2.jour, date2.mois, date2.annee)==0);
                        break;

                    case 5 /* relais */:
                        //on nomme la chaîne de caractère épreuve en fonction du choix de l'épreuve
                        strcpy(epreuve, "relais");
                        printf("vous avez choisi l'épreuve %s", epreuve);

                        printf("Les statistiques de l'athlète %s pour l'épreuve %s:\n", athlete, epreuve);
                        afficheSatistique(athlete, epreuve);

                        do {
                            printf("Entrez la date (JJ/MM/AAAA) que vous voulez observer: \n" );
                            scanf("%2d/%2d/%4d", &date1.jour, &date1.mois, &date1.annee);

                            if(valideDate(date1.jour, date1.mois, date1.annee)){
                                // on formate la date comme JJ/MM/AAAA
                                do {
                                    printf("Entrez la deuxième date (JJ/MM/AAAA) à laquelle vous voulez observer la différence de temps avec la première: \n" );
                                    scanf("%2d/%2d/%4d", &date2.jour, &date2.mois, &date2.annee);

                                    if(valideDate(date2.jour, date2.mois, date2.annee)){
                                        // on formate la date comme JJ/MM/AAAA
                                        differenceTempsDates(athlete, epreuve, date1, date2);
                                    }else{
                                        printf("Erreur! Entrer une nouvelle date \n");
                                        viderBuffer();
                                    }
                                } while (valideDate(date2.jour, date2.mois, date2.annee)==0);
                            }else{
                                printf("Erreur! Entrer une nouvelle date \n");
                                viderBuffer();
                            }
                        } while (valideDate(date2.jour, date2.mois, date2.annee)==0);
                        break;

                    default:
                        printf("ce choix n'est pas possible \n");
                        break;
                }
            break;

            case 4 /* Quitter */:
                printf("4 \n");
                break;

            default:
                printf("ce choix n'est pas possible \n");
                viderBuffer();
                break;
        }

    } while (choix < 1 || choix > 4);

    return 0;

    }



