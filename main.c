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

typedef struct {
    char nom[50];
    Date date;
    char epreuve[50];
    float temps;
    int position;
} Athlete;

typedef struct {
    char nom[50];
    float moyenne;
}AthleteMoyenne;

//Procédure de tri d'insertion pour trier les dates
void tri_insertion_date(Athlete tab[], int n){
    int i,j;
    Athlete k;
    for (i=1;i<n;i++){
        k=tab[i];
        j=i-1;

        // Comparer les dates
        while (j>=0 &&
               (tab[j].date.annee > k.date.annee ||
                (tab[j].date.annee == k.date.annee && tab[j].date.mois > k.date.mois) ||
                (tab[j].date.annee == k.date.annee && tab[j].date.mois == k.date.mois && tab[j].date.jour > k.date.jour))){
            tab[j+1]=tab[j];
            j=j-1;
        }tab[j+1]=k;
    }
}

void tri_date(const char *fichier_entree_nom){
    const char *fichier_sortie_nom = "fichier_tri_date.txt";

    // Ouverture du fichier d'entrée
    FILE *fichier_entree = fopen(fichier_entree_nom, "r");
    if (fichier_entree == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        exit(2);
    }
    Athlete fiches[100];
    int i = 0;
    char ligne[200];

    // Lire les données depuis le fichier d'entrée
    while (fgets(ligne, 199, fichier_entree)){
        if (sscanf(ligne, "%49s %d/%d/%d %49s %f",fiches[i].nom,
                   &fiches[i].date.jour,
                   &fiches[i].date.mois,
                   &fiches[i].date.annee,
                   fiches[i].epreuve,
                   &fiches[i].temps) == 6){
            i++;
        }
    }
    fclose(fichier_entree);

    // Trier les fiches par date en utilisant le tri par insertion
    tri_insertion_date(fiches, i);

    // Ouverture du fichier de sortie
    FILE *fichier_sortie = fopen(fichier_sortie_nom, "w");
    if (fichier_sortie == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        exit(2);
    }

    // Écrire les données triées dans le fichier de sortie
    for (int k=0;k<i;k++){
        fprintf(fichier_sortie, "%s  %d/%d/%d  %s  %.2f\n",fiches[k].nom,
                fiches[k].date.jour,
                fiches[k].date.mois,
                fiches[k].date.annee,
                fiches[k].epreuve,
                fiches[k].temps);
    }fclose(fichier_sortie);
}

void tri_epreuve_date(const char *fichier_entree_nom, const char *epreuve_cible, const char *fichier_sortie_nom){

    // Ouverture du fichier d'entrée
    FILE *fichier_entree = fopen(fichier_entree_nom, "r");
    if (fichier_entree == NULL){
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        exit(1);
    }
    Athlete fiches[100];
    int i = 0;
    char ligne[200];

    // Lire les données depuis le fichier d'entrée
    while (fgets(ligne, 199, fichier_entree)) {
        if (sscanf(ligne, "%49s %d/%d/%d %49s %f",fiches[i].nom,
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
    tri_insertion_date(fiches, i);

    // Ouverture du fichier de sortie
    FILE *fichier_sortie = fopen(fichier_sortie_nom, "w");
    if (fichier_sortie == NULL){
        perror("Erreur lors de l'ouverture du fichier de sortie");
        exit(1);
    }

    // Écrire les fiches pour l'épreuve cible dans le fichier de sortie
    for (int k = 0; k < i; k++) {
        if (strcmp(fiches[k].epreuve, epreuve_cible) == 0){
            fprintf(fichier_sortie, "%s %d/%d/%d %s %.2f\n",fiches[k].nom,
                    fiches[k].date.jour,
                    fiches[k].date.mois,
                    fiches[k].date.annee,
                    fiches[k].epreuve,
                    fiches[k].temps);
        }
    }
    fclose(fichier_sortie);
}

void tri_epreuve_date1(const char *fichier_entree_nom, const char *epreuve_cible, const char *fichier_sortie_nom){

    // Ouverture du fichier d'entrée
    FILE *fichier_entree = fopen(fichier_entree_nom, "r");
    if (fichier_entree == NULL){
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        exit(1);
    }
    Athlete fiches[100];
    int i = 0;
    char ligne[200];

    // Lire les données depuis le fichier d'entrée
    while (fgets(ligne, 199, fichier_entree)) {
        if (sscanf(ligne, "%49s %d/%d/%d %49s %d %f",fiches[i].nom,
                   &fiches[i].date.jour,
                   &fiches[i].date.mois,
                   &fiches[i].date.annee,
                   fiches[i].epreuve,
                   &fiches[i].position,
                   &fiches[i].temps) == 7) {
            i++;
        }
    }
    fclose(fichier_entree);

    // Trier les fiches par date en utilisant le tri par insertion
    tri_insertion_date(fiches, i);

    // Ouverture du fichier de sortie
    FILE *fichier_sortie = fopen(fichier_sortie_nom, "w");
    if (fichier_sortie == NULL){
        perror("Erreur lors de l'ouverture du fichier de sortie");
        exit(1);
    }

    // Écrire les fiches pour l'épreuve cible dans le fichier de sortie
    for (int k = 0; k < i; k++) {
        if (strcmp(fiches[k].epreuve, epreuve_cible) == 0){
            fprintf(fichier_sortie, "%s %d/%d/%d %s %d %.2f\n",fiches[k].nom,
                    fiches[k].date.jour,
                    fiches[k].date.mois,
                    fiches[k].date.annee,
                    fiches[k].epreuve,
                    fiches[k].position,
                    fiches[k].temps);
        }
    }
    fclose(fichier_sortie);
}

//Procédure de tri d'insertion pour trier les moyennes
void tri_insertion_moyenne(AthleteMoyenne tab[], int n){
    int i,j;
    AthleteMoyenne k;
    for (i=1;i<n;i++){
        k=tab[i];
        j=i-1;

        // Comparer les moyennes
        while (j>=0 && tab[j].moyenne>k.moyenne) {
            tab[j+1]=tab[j];
            j=j-1;
        }tab[j+1]=k;
    }
}
//Procédure pour trier les moyennes
void tri_moyennes(const char *fichier_entree_nom, const char *fichier_sortie_nom){
    // Ouverture du fichier d'entrée
    FILE *fichier_entree = fopen(fichier_entree_nom, "r");
    if (fichier_entree == NULL){
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        exit(2);
    }
    AthleteMoyenne athletes[100];
    int n=0;
    char ligne[200];
    rewind(fichier_entree);
    // Lire les données depuis le fichier d'entrée
    while (fgets(ligne,199, fichier_entree)){
        if(sscanf(ligne, "%49s %f", athletes[n].nom, &athletes[n].moyenne)==2){
            n++;
        };
    }fclose(fichier_entree);

    // Trier les athlètes par moyenne en utilisant le tri par insertion
    tri_insertion_moyenne(athletes, n);

    // Ouverture du fichier de sortie
        FILE *fichier_sortie = fopen(fichier_entree_nom, "w");

    if (fichier_sortie == NULL){
        perror("Erreur lors de l'ouverture du fichier de sortie");
        exit(2);
    }


    // Écrire les données triées dans le fichier de sortie
    for (int i=0;i<n;i++){
        fprintf(fichier_sortie, "%s %.2f\n", athletes[i].nom, athletes[i].moyenne);

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
void Definir_Resultat_Par_Athlete( char *athlete) {

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
                // on ajoute la ligne athlete date epreuve position resultat
                fprintf(fichier, "%s %d/%d/%d %s %d %f\n", athlete, dates.jour, dates.mois, dates.annee, epreuve,position, resultat);
                // on ajoute la ligne athlete date epreuve resultat
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



//fonction pour récupérer les chronos dans un fichier pour un athlete sur une épreuve sauf le relais
float * recupererdonnees(char *athlete, char *epreuve) {
    FILE *fichier = NULL;

    char nom_fichier[MAX_LONGUEUR_SAISIE];
    //on copie le nom de l'athlete dans le nom du fichier
    strncpy(nom_fichier, athlete, MAX_LONGUEUR_SAISIE-1);
    //on ajoute _ juste après puis epreuve
   strcat(nom_fichier,"_");
    strcat(nom_fichier,epreuve);
    // on ajoute .txt a la fin de nom_fichier
    strcat(nom_fichier, ".txt");

    fichier = fopen(nom_fichier, "r");

    if (fichier != NULL) {

        Athlete fiches[100];
        int i=1;
        char lignes[200];
        // Lire les données depuis le fichier d'entrée
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
//on crée un tableau qui sera composé des temps de l'athlète en allouant l'espace en fonction du nombre de ligne du fichier
        float *chronos = malloc((i +1) * sizeof(float));
        if (chronos == NULL) {
            printf("erreur d'allocation de la mémoire\n");
            exit(1);
        }
        rewind(fichier);
        chronos[0] = (float)i ;
        //on rentre les chronos
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


//fonction pour récupérer les chronos pour le relais
float * recupererdonnees1(char *athlete, char *epreuve) {
    FILE *fichier = NULL;
    char nom_fichier[MAX_LONGUEUR_SAISIE];
    //On copie le nom de l'athlete dans le nom du fichier
    strncpy(nom_fichier, athlete, MAX_LONGUEUR_SAISIE-1);
    //on ajoute _ juste après puis le nom de l'epreuve
    strcat(nom_fichier,"_");
    strcat(nom_fichier,epreuve);
    // on ajoute .txt a la fin de nom_fichier
    strcat(nom_fichier, ".txt");

    fichier = fopen(nom_fichier, "r");

    if (fichier != NULL) {

        Athlete fiches[100];
        int i=1;
        char lignes[200];
        // Lire les données depuis le fichier d'entrée
        while (fgets(lignes, 199, fichier)) {
            if (sscanf(lignes, "%49s %d/%d/%d %49s %d %f",
                       fiches[i].nom,
                       &fiches[i].date.jour,
                       &fiches[i].date.mois,
                       &fiches[i].date.annee,
                       fiches[i].epreuve,
                       &fiches[i].position,
                       &fiches[i].temps) == 7) {

                i++;
            }
        }
        //on crée un tableau qui sera composé des temps de l'athlète en allouant l'espace en fonction du nombre de ligne du fichier
        float *chronos = malloc((i +1) * sizeof(float));
        if (chronos == NULL) {
            printf("erreur d'allocation de la mémoire\n");
            exit(1);
        }
        rewind(fichier);
        //on entre la taille du tableau dans la première case
        chronos[0] = (int)i ;
        //on rentre les chronos en commencant à la case 1
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

// Procédure de tri par insertion pour trier les chronos
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

//fonction qui permet de connaître le calculer, la moyenne, trouver le meilleur et le pire temps hors relais
float * statistique ( char *athlete,  char *epreuve) {
    //on récupère le tableau de chronos dans la fonction récupérer données
    float *a = recupererdonnees(athlete, epreuve);
    int taille = (int)a[0];
    //on appelle la procédure pour trier le tableau de chronos
    triInsertion(a + 1, taille-1);
    //on calcule la moyenne
    float moyenne = 0;
    for (int i = 1; i < taille; i++) {
        moyenne += a[i];
    }
    float vraimoyenne = moyenne / (taille-1);

    //on crée un tableau dans lequel on rentrera le pire et le meilleur temps et la moyenne
    float *tab = malloc(3 * sizeof(float));
    //le pire temps
    tab[0]=a[taille-1];
    //le meilleur temps
    tab[1]=a[1];
    //la moyenne
    tab[2]=vraimoyenne;
    AthleteMoyenne top_athlete;
    strncpy(top_athlete.nom, athlete,49);
    top_athlete.moyenne=tab[2];
    //pour pouvoir connaître les athlètes qui iront au Jo, on va créér un fichier qui aura la moyenne et le nom de l'athlete
    FILE*fichier;
    //on ouvre le fichier correspondant en fonction des épreuves, il n'y a pas le relais, on demande de choisir les 3 meilleurs athlètes, ce qui n'a aps de sens pour un relais de 4 personnes
    if(strcmp(epreuve, "100m")==0) {
        fichier = fopen("statistiquess100m.txt", "a+");
    }
    else if(strcmp(epreuve, "400m")==0) {
        fichier = fopen("statistiquess400m.txt", "a+");
    }
    else if(strcmp(epreuve, "5000m")==0) {
        fichier = fopen("statistiquess5000m.txt", "a+");
    }
    else if(strcmp(epreuve, "marathon")==0) {
        fichier = fopen("statistiquessmarathon.txt", "a+");
    }else{
        exit(1);
    }
    AthleteMoyenne athletes[100];
    int n = 0;
    char ligne[200];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        sscanf(ligne, "%49s %f", athletes[n].nom, &athletes[n].moyenne);
        n++;
    }
    fclose(fichier);

    // Vérifier si l'athlète est déjà présent
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(athletes[i].nom, top_athlete.nom) == 0) {
            athletes[i].moyenne = top_athlete.moyenne;
            found = 1;
            break;
        }
    }
    //on entre les valeurs dans le fichier (le nom et la moyenne)
    if(found==0){
    fprintf(fichier,"%s %f\n",top_athlete.nom ,top_athlete.moyenne);
    }
    fclose(fichier);
    free(a);

    return tab;
}

//fonction qui permet de connaître le calculer, la moyenne, trouver le meilleur et le pire temps du relais
float * statistique1 ( char *athlete,  char *epreuve) {
//on récupère le tableau de chronos dans la fonction récupérer données
    float *a = recupererdonnees1(athlete, epreuve);
    int taille = (int)a[0];
//on appelle la procédure pour trier le tableau de chronos
    triInsertion(a + 1, taille-1);
//on calcule la moyenne
    float moyenne = 0;
    for (int i = 1; i < taille; i++) {
        moyenne += a[i];
    }
    float vraimoyenne = moyenne / (taille-1);

//on crée un tableau dans lequel on rentrera le pire et le meilleur temps et la moyenne
    float *tab = malloc(3 * sizeof(float));
    //le pire temps
    tab[0]=a[taille-1];
    //le meilleur temps
    tab[1]=a[1];
    //la moyenne
    tab[2]=vraimoyenne;

    free(a);

    return tab;
}

//Procédure affichant le meilleur et le pire temps ainsi que la moyenne de l'athlete pour une epreuve
void afficheSatistique( char *athlete, char* epreuve) {
//on récupère le tableau composé de la moyenne, le pire et le meilleur temps, puis on l'affiche
    float *tab = statistique(athlete, epreuve);
    printf("le meilleur temps de l'athlete %s au %s est %f  \n", athlete, epreuve, tab[1]);
    printf("le pire temps de l'athlete %s au %s est %f \n ", athlete, epreuve, tab[0]);
    printf("la moyenne de l'athlete %s pour l'epreuve %s est %f\n", athlete, epreuve, tab[2]);
    free(tab);
}

//Procédure affichant le meilleur et le pire temps ainsi que la moyenne de l'athlete pour une epreuve pour le relais
void afficheSatistique1( char *athlete, char* epreuve) {
//on récupère le tableau composé de la moyenne, le pire et le meilleur temps, puis on l'affiche
    float *tab = statistique1(athlete, epreuve);
    printf("le meilleur temps de l'athlete %s au %s est %f  \n", athlete, epreuve, tab[1]);
    printf("le pire temps de l'athlete %s au %s est %f \n ", athlete, epreuve, tab[0]);
    printf("la moyenne de l'athlete %s pour l'epreuve %s est %f\n", athlete, epreuve, tab[2]);
    free(tab);
}

//Procédure permettant de trouver et d'afficher les 3 meilleurs athletes en fonction de leur moyenne pour participer au JO
void Meilleurs_Athletes(char *epreuve){
    AthleteMoyenne athlete;
    FILE*fichier;
    //On ouvre le fichier qui correspond à l'épreuve, on appelle la procédure tri_moyennes pour trier les moyennes dans l'ordre croissant
    if(strcmp(epreuve, "100m")==0) {
         tri_moyennes("statistiquess100m.txt", "LULU.txt");
        fichier = fopen("statistiquess100m.txt", "r");
    }
    else if(strcmp(epreuve, "400m")==0) {
        tri_moyennes("statistiquess400m.txt", "LULU.txt");
        fichier = fopen("statistiquess400m.txt", "r");
    }
    else if(strcmp(epreuve, "5000m")==0) {

        tri_moyennes("statistiquess5000m0.txt", "LULU.txt");
        fichier = fopen("statistiquess5000m.txt", "r");
    }
    else if(strcmp(epreuve, "marathon")==0) {
        tri_moyennes("statistiquessmarathon", "LULU.txt");
        fichier = fopen("statistiquessmarathon.txt", "r");
    }else{
        exit(1);
    }

    for (int i=0; i<3; i++){
        fscanf(fichier, "%s %f\n",athlete.nom, &athlete.moyenne);
        if (i==0){
            printf("l'athlete %s est le premier avec la meilleure moyenne de temps, %f, dans l'epreuve %s\n",athlete.nom, athlete.moyenne, epreuve);
        }
        if (i==1){
            printf("l'athlete %s est le deuxieme avec la  moyenne de temps, %f, dans l'epreuve %s\n",athlete.nom, athlete.moyenne, epreuve);
        }
        if (i==2){
            printf("l'athlete %s est le troisieme avec la  moyenne de temps, %f, dans l'epreuve %s\n",athlete.nom, athlete.moyenne, epreuve);
        }
    }
    fclose(fichier);
}

//Procédure pour calculer la différence de temps pour une epreuve entre 2 dates
void differenceTempsDates(char *athlete, char *epreuve, Date a, Date  b){
    FILE *fichier = NULL;
    char nom_fichier[MAX_LONGUEUR_SAISIE];
    //on copie le nom de l'athlete dans le nom du fichier
    strncpy(nom_fichier, athlete, MAX_LONGUEUR_SAISIE-1);
    //on ajoute _ juste après puis epreuve
   strcat(nom_fichier,"_");
    strcat(nom_fichier,epreuve);
    //on ajoute .txt a la fin de nom_fichier
    strcat(nom_fichier, ".txt");
//on ouvre le fichier
    fichier = fopen(nom_fichier, "r");

    if (fichier != NULL) {
        //on alloue l'espace pour le tableau qui comprendra le premier chrono des 2 dates
        float *chrono = malloc(2 * sizeof(float));
        chrono[0] = 0;
        chrono[1] = 0;
        char lignes[200];
        Athlete fiches[100];
        int i = 1;
        // Lire les données depuis le fichier d'entrée
        while (fgets(lignes, 199, fichier)) {
            if (sscanf(lignes, "%49s %d/%d/%d %49s %f",
                       fiches[i].nom,
                       &fiches[i].date.jour,
                       &fiches[i].date.mois,
                       &fiches[i].date.annee,
                       fiches[i].epreuve,
                       &fiches[i].temps) == 6) {
                //on compare la date entrée par l'utlisateur et celle sur la ligne, si c'est elle, on entre dans dans le tableau le chrono
                if (fiches[i].date.jour == a.jour && fiches[i].date.mois == a.mois && fiches[i].date.annee == a.annee) {
                    chrono[0] = fiches[i].temps;
                    i++;
                }
                //on compare la date entrée par l'utlisateur et celle sur la ligne, si c'est elle, on entre dans dans le tableau le chrono
                if (fiches[i].date.jour == b.jour && fiches[i].date.mois == b.mois && fiches[i].date.annee == b.annee) {
                    chrono[1] = fiches[i].temps;
                    i++;
                }
            }
        }
        fclose(fichier);
        if (chrono[0] == 0 || chrono[1] == 0) {
            printf("l'une  des dates que vous avez rentre n'existe pas\n");
//on calcule la différence de temps entre les chronos
        } else {
            float difference = chrono[0] - chrono[1];
            if (difference < 0) {
                difference = chrono[1] - chrono[0];
            }
            printf(" entre %d/%d/%d et %d/%d/%d, avec pour temps respectif %f, %f est de %f\n", a.jour, a.mois, a.annee,
                   b.jour, b.mois, b.annee, chrono[0], chrono[1], difference);
            free(chrono);
        }
    }
    fclose(fichier);
}

//Procédure pour calculer la différence de temps pour une epreuve entre 2 dates pour le relais
void differenceTempsDates1(char *athlete, char *epreuve, Date a, Date  b){
    FILE *fichier = NULL;
    char nom_fichier[MAX_LONGUEUR_SAISIE];
    //on copie le nom de l'athlete dans le nom du fichier
    strncpy(nom_fichier, athlete, MAX_LONGUEUR_SAISIE-1);
    //on ajoute _ juste après puis epreuve
    strcat(nom_fichier,"_");
    strcat(nom_fichier,epreuve);
    //on ajoute .txt a la fin de nom_fichier
    strcat(nom_fichier, ".txt");
//on ouvre le fichier
    fichier = fopen(nom_fichier, "r");

    if (fichier != NULL) {
        //on alloue l'espace pour le tableau qui comprendra le premier chrono des 2 dates
        float *chrono = malloc(2 * sizeof(float));
        chrono[0] = 0;
        chrono[1] = 0;
        char lignes[200];
        Athlete fiches[100];
        int i = 1;
        // Lire les données depuis le fichier d'entrée
        while (fgets(lignes, 199, fichier)) {
            if (sscanf(lignes, "%49s %d/%d/%d %49s %d %f",
                       fiches[i].nom,
                       &fiches[i].date.jour,
                       &fiches[i].date.mois,
                       &fiches[i].date.annee,
                       fiches[i].epreuve,
                       &fiches[i].position,
                       &fiches[i].temps) == 6) {
                //on compare la date entrée par l'utlisateur et celle sur la ligne, si c'est elle, on entre dans le tableau le chrono
                if (fiches[i].date.jour == a.jour && fiches[i].date.mois == a.mois && fiches[i].date.annee == a.annee) {
                    chrono[0] = fiches[i].temps;
                    i++;
                }
                //on compare la date entrée par l'utlisateur et celle sur la ligne, si c'est elle, on entre dans le tableau le chrono
                if (fiches[i].date.jour == b.jour && fiches[i].date.mois == b.mois && fiches[i].date.annee == b.annee) {
                    chrono[1] = fiches[i].temps;
                    i++;
                }
            }
        }
        fclose(fichier);
        if (chrono[0] == 0 || chrono[1] == 0) {
            printf("l'une  des dates que vous avez rentre n'existe pas\n");
//on calcule la différence de temps entre les chronos
        } else {
            float difference = chrono[0] - chrono[1];
            if (difference < 0) {
                difference = chrono[1] - chrono[0];
            }
            printf(" entre %d/%d/%d et %d/%d/%d, avec pour temps respectif %f, %f est de %f\n", a.jour, a.mois, a.annee,
                   b.jour, b.mois, b.annee, chrono[0], chrono[1], difference);
            free(chrono);
        }
    }
    fclose(fichier);
}

int main() {
   //si les fichiers qui comporteront les moyennes des athlètes n'existent pas, on les crée
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

            switch (choix) {
                case 1 /* creer un entrainement */:
                    printf("Entrez le nom de l'athlete: ");
                    scanf("%s", athlete);
                    Definir_Resultat_Par_Athlete(athlete);
                    break;


                case 2 /* Voir Historiques */:
                    printf("****HISTORIQUE****");
                    char *fichier_sortie_epreuve = "fichier_tri_epreuve.txt";
                    char epr[100], a[100];

                    // Demande à l'utilsateur de saisir le nom de l'athlete
                    printf("\nSaisir le nom de l'athlete comme ceci : 'nom.txt':\n");
                    scanf("%s", athlete);
                    while (fopen(athlete, "r") == NULL) {
                        printf("Le fichier n'existe pas, ou alors vous avez oublie le '.txt'\n");
                        printf("Saisir le nom de l'athlete comme ceci : 'nom.txt':\n");
                        scanf("%s", athlete);
                    }
                    // Trie les entrainements d'un athlete par date grâce à la fonction tri_date
                    tri_date(athlete);
                    printf("La fiche de %s a été triee par date dans le fichier nomme 'fichier_tri_date'", athlete);

                    // Demande à l'utilsateur s'il veut voir l'historique pour une épreuve de l'athlete
                    printf("\n\nVoulez vous consulter l'historique de une epreuve de l'athlete %s ? (! répondre par oui ou non)",
                           athlete);
                    scanf("%s", a);

                    // Verification de la bonne écriture de l'utilisateur
                    while (strcmp(a, "oui") != 0 && strcmp(a, "non") != 0) {
                        printf("Repondre par oui ou par non !!!");
                        scanf("%s", a);
                    }
                    if (strcmp(a, "oui") == 0) {
                        printf("\nDire le nom de l'epreuve dont vous voulez connaitre l'historique (100m,400m,5000m,marathon,relais)\n");
                        scanf("%s", epr);
                        while (strcmp(epr, "400m") != 0 &&
                               strcmp(epr, "100m") != 0 &&
                               strcmp(epr, "marathon") != 0 &&
                               strcmp(epr, "relais") != 0 &&
                               strcmp(epr, "5000m") != 0) {
                            printf("Vous n'avez pas saisit une epreuve qui existe !!!");
                            printf("\nDire le nom de l'épreuve dont vous voulez connaitre l'historique (100m,400m,5000m,marathon,relais)\n");
                            scanf("%s", epr);
                        }
                        tri_epreuve_date(athlete, epr, fichier_sortie_epreuve);
                        printf("La fiche de %s a été triee avec l'epreuve '%s' dans le fichier nomme 'fichier_tri_epreuve'\n\n",
                               athlete, epr);
                    } else if (strcmp(a, "non") == 0) {
                        printf("D'accord\n\n");
                    }
                    break;

                case 3 /* Voir Statistiques */:
                    //vérifier si l'utilisateur rentre un athlete qui existe
                    do {
                        printf("Saisir le nom de l'athlete: ");
                        scanf("%s", athlete);

                        // On regroupe .txt avec athlete pour appeler le fichier de l'athlete
                        char athlete_verif[MAX_LONGUEUR_SAISIE + 4]; // +4 pour ".txt" et le caractère nul
                        snprintf(athlete_verif, MAX_LONGUEUR_SAISIE + 4, "%s.txt", athlete);

                        // Ouverture du fichier correspondant
                        FILE *fichier5 = fopen(athlete_verif, "r");

                        // Vérification si le fichier existe
                        if (fichier5 != NULL) {
                            fclose(fichier5); // Fermeture du fichier si ouvert avec succès
                            break; // Sortie de la boucle si le fichier existe
                        } else {
                            printf("Le fichier sur l'athlete n'existe pas.\n");
                            viderBuffer();
                        }
                    } while (1);
                    //on alloue la place pour le nom des épreuves
                    char *epreuve = malloc(10);
                    if (epreuve == NULL) {
                        exit(1);
                    }
                    Date date1;
                    Date date2;
                    int n_epreuve=-1;
                    do {
                    printf("Entrez l'epreuve: \n");
                    printf("(1) 100m \n");
                    printf("(2) 400m \n");
                    printf("(3) 5000m \n");
                    printf("(4) marathon \n");
                    printf("(5) relais \n");
                    scanf("%d", &n_epreuve);

                        switch (n_epreuve) {
                            case 1 /* 100m */:
                                //on nomme la chaîne de caractère epreuve en fonction du choix de l'épreuve
                                strcpy(epreuve, "100m");
                                printf("vous avez choisi l'epreuve %s\n", epreuve);

                                char reponse;
                                do {
                                    do {
                                        printf("Entrez la date (JJ/MM/AAAA) que vous voulez observer: \n");
                                        scanf("%2d/%2d/%4d", &date1.jour, &date1.mois, &date1.annee);
                                        //on vérifie si la date est correctement rentrée
                                        if (valideDate(date1.jour, date1.mois, date1.annee) != 0) {
                                            // on formate la date comme JJ/MM/AAAA
                                            do {
                                                printf("Entrez la deuxieme date (JJ/MM/AAAA) a laquelle vous voulez observer la difference de temps avec la premiere: \n");
                                                scanf("%2d/%2d/%4d", &date2.jour, &date2.mois, &date2.annee);

                                                if (valideDate(date2.jour, date2.mois, date2.annee) != 0) {
                                                    // on formate la date comme JJ/MM/AAAA
                                                    differenceTempsDates(athlete, epreuve, date1, date2);
                                                } else {
                                                    printf("Erreur! Entrer une nouvelle date \n");
                                                    viderBuffer();
                                                }
                                            } while (valideDate(date2.jour, date2.mois, date2.annee) == 0);
                                        } else {
                                            printf("Erreur! Entrer une nouvelle date \n");
                                            viderBuffer();
                                        }
                                    } while (valideDate(date2.jour, date2.mois, date2.annee) == 0);
                                    printf("Voulez-vous verifier la difference de temps pour d'autres dates ? (O/N): ");

                                    scanf(" %c", &reponse);
                                } while (reponse == 'O' || reponse == 'o');

                                printf("Les statistiques de l'athlete %s pour l'epreuve %s:\n", athlete, epreuve);
                                char *fichier_sortie_epreuve = malloc(50);
                                //on renomme la chaîne de caractère en athlète

                                strcpy(fichier_sortie_epreuve, athlete);
                                //on ajoute _ et le nom de l'épreuve à la chaîne
                                strcat(fichier_sortie_epreuve, "_");
                                strcat(fichier_sortie_epreuve, epreuve);
                                //on ajoute .txt a la fin de la chaîne
                                strcat(fichier_sortie_epreuve, ".txt");
                                char *fichier_entree_nom = malloc(50);
                                strcpy(fichier_entree_nom, athlete);
                                //on ajoute .txt a la fin de nom_fichier
                                strcat(fichier_entree_nom, ".txt");
                                tri_epreuve_date(fichier_entree_nom, epreuve, fichier_sortie_epreuve);
                                afficheSatistique(athlete, epreuve);

                                //on va vérifier si dans le fichier qui comporte les moyennes de tous athletes pour cette epreuve, comprend au moins 3 athlètes
                                int i=0;
                                FILE *fichier = fopen("statistiquess100m.txt", "r");
                                rewind(fichier);
                                AthleteMoyenne fiches[100];
                                char lignes[200];
                                // Lire les données depuis le fichier d'entrée
                                while (fgets(lignes, 199, fichier)) {
                                    if (sscanf(lignes, "%49s %f",
                                               fiches[i].nom,
                                               &fiches[i].moyenne) == 2 ) {

                                        i++;
                                    }
                                }

                                rewind(fichier);
                                fclose(fichier);
                                if (i >= 3) {
                                    printf(" Connaitre les 3 meilleurs athletes a l'epreuve %s: \n", epreuve);
                                    Meilleurs_Athletes(epreuve);
                                } else {
                                    printf("il n'y pas assez d'athlete pour savoir qui emmener aux JO");
                                }
                                break;

                            case 2 /* 400m */:
                                //on nomme la chaîne de caractère épreuve en fonction du choix de l'épreuve
                                strcpy(epreuve, "400m");
                                printf("vous avez choisi l'epreuve %s\n", epreuve);

                                char reponse1;
                                do {
                                    do {
                                        printf("Entrez la date (JJ/MM/AAAA) que vous voulez observer: \n");
                                        scanf("%2d/%2d/%4d", &date1.jour, &date1.mois, &date1.annee);
                                        //on vérifie si la date est correctement rentrée
                                        if (valideDate(date1.jour, date1.mois, date1.annee) != 0) {
                                            // on formate la date comme JJ/MM/AAAA
                                            do {
                                                printf("Entrez la deuxieme date (JJ/MM/AAAA) a laquelle vous voulez observer la difference de temps avec la premiere: \n");
                                                scanf("%2d/%2d/%4d", &date2.jour, &date2.mois, &date2.annee);

                                                if (valideDate(date2.jour, date2.mois, date2.annee) != 0) {
                                                    // on formate la date comme JJ/MM/AAAA
                                                    differenceTempsDates(athlete, epreuve, date1, date2);
                                                } else {
                                                    printf("Erreur! Entrer une nouvelle date \n");
                                                    viderBuffer();
                                                }
                                            } while (valideDate(date2.jour, date2.mois, date2.annee) == 0);
                                        } else {
                                            printf("Erreur! Entrer une nouvelle date \n");
                                            viderBuffer();
                                        }
                                    } while (valideDate(date2.jour, date2.mois, date2.annee) == 0);
                                    printf("Voulez-vous verifier la difference de temps pour d'autres dates ? (O/N): ");

                                    scanf(" %c", &reponse1);
                                } while (reponse1 == 'O' || reponse1 == 'o');

                                printf("Les statistiques de l'athlete %s pour l'epreuve %s:\n", athlete, epreuve);
                                char *fichier_sortie_epreuve1 = malloc(50);
                                //on renomme la chaîne de caractère en athlète

                                strcpy(fichier_sortie_epreuve1, athlete);
                                //on ajoute _ et le nom de l'épreuve à la chaîne
                                strcat(fichier_sortie_epreuve1, "_");
                                strcat(fichier_sortie_epreuve1, epreuve);
                                //on ajoute .txt a la fin de nom_fichier
                                strcat(fichier_sortie_epreuve1, ".txt");
                                char *fichier_entree_nom1 = malloc(50);
                                strcpy(fichier_entree_nom1, athlete);
                                //on ajoute .txt a la fin de nom_fichier
                                strcat(fichier_entree_nom1, ".txt");
                                tri_epreuve_date(fichier_entree_nom1, epreuve, fichier_sortie_epreuve1);
                                afficheSatistique(athlete, epreuve);


                                //on va vérifier si dans le fichier qui comporte les moyennes de tous athletes pour cette epreuve, comprend au moins 3 athlètes
                                int i1=0;
                                FILE *fichier1 = fopen("statistiquess100m.txt", "r");
                                rewind(fichier1);
                                AthleteMoyenne fiches1[100];
                                char lignes1[200];
                                // Lire les données depuis le fichier d'entrée
                                while (fgets(lignes1, 199, fichier1)) {
                                    if (sscanf(lignes1, "%49s %f",
                                               fiches1[i].nom,
                                               &fiches1[i].moyenne) == 2 ) {

                                        i1++;
                                    }
                                }

                                rewind(fichier1);
                                fclose(fichier1);
                                if (i1 >= 3) {
                                    printf(" Connaitre les 3 meilleurs athletes a l'epreuve %s: \n", epreuve);
                                    Meilleurs_Athletes(epreuve);
                                } else {
                                    printf("il n'y pas assez d'athlete pour savoir qui emmener aux JO");
                                }
                                break;

                            case 3 /* 5000m */:
                                //on nomme la chaîne de caractère épreuve en fonction du choix de l'épreuve
                                strcpy(epreuve, "5000m");
                                printf("vous avez choisi l'epreuve %s\n", epreuve);
                                char reponse2;
                                do {
                                    do {
                                        printf("Entrez la date (JJ/MM/AAAA) que vous voulez observer: \n");
                                        scanf("%2d/%2d/%4d", &date1.jour, &date1.mois, &date1.annee);
                                        //on vérifie si la date est correctement rentrée
                                        if (valideDate(date1.jour, date1.mois, date1.annee) != 0) {
                                            // on formate la date comme JJ/MM/AAAA
                                            do {
                                                printf("Entrez la deuxieme date (JJ/MM/AAAA) a laquelle vous voulez observer la difference de temps avec la premiere: \n");
                                                scanf("%2d/%2d/%4d", &date2.jour, &date2.mois, &date2.annee);

                                                if (valideDate(date2.jour, date2.mois, date2.annee) != 0) {
                                                    // on formate la date comme JJ/MM/AAAA
                                                    differenceTempsDates(athlete, epreuve, date1, date2);
                                                } else {
                                                    printf("Erreur! Entrer une nouvelle date \n");
                                                    viderBuffer();
                                                }
                                            } while (valideDate(date2.jour, date2.mois, date2.annee) == 0);
                                        } else {
                                            printf("Erreur! Entrer une nouvelle date \n");
                                            viderBuffer();
                                        }
                                    } while (valideDate(date2.jour, date2.mois, date2.annee) == 0);
                                    printf("Voulez-vous verifier la difference de temps pour d'autres dates ? (O/N): ");

                                    scanf(" %c", &reponse2);
                                } while (reponse2 == 'O' || reponse2 == 'o');

                                printf("Les statistiques de l'athlete %s pour l'epreuve %s:\n", athlete, epreuve);
                                char *fichier_sortie_epreuve2 = malloc(50);
                                //on renomme la chaîne de caractère en athlète

                                strcpy(fichier_sortie_epreuve2, athlete);
                                //on ajoute _ et le nom de l'épreuve à la chaîne
                                strcat(fichier_sortie_epreuve2, "_");
                                strcat(fichier_sortie_epreuve2, epreuve);
                                //on ajoute .txt a la fin de nom_fichier
                                strcat(fichier_sortie_epreuve2, ".txt");
                                char *fichier_entree_nom2 = malloc(50);
                                strcpy(fichier_entree_nom2, athlete);
                                //on ajoute .txt a la fin de nom_fichier
                                strcat(fichier_entree_nom2, ".txt");
                                tri_epreuve_date(fichier_entree_nom2, epreuve, fichier_sortie_epreuve2);
                                afficheSatistique(athlete, epreuve);


                                //on va vérifier si dans le fichier qui comporte les moyennes de tous athletes pour cette epreuve, comprend au moins 3 athlètes
                                int i2=0;
                                FILE *fichier2 = fopen("statistiquess100m.txt", "r");
                                rewind(fichier2);
                                AthleteMoyenne fiches2[100];
                                char lignes2[200];
                                // Lire les données depuis le fichier d'entrée
                                while (fgets(lignes2, 199, fichier2)) {
                                    if (sscanf(lignes2, "%49s %f",
                                               fiches2[i].nom,
                                               &fiches2[i].moyenne) == 2 ) {

                                        i++;
                                    }
                                }

                                rewind(fichier2);
                                fclose(fichier2);
                                if (i2 >= 3) {
                                    printf(" Connaitre les 3 meilleurs athletes a l'epreuve %s: \n", epreuve);
                                    Meilleurs_Athletes(epreuve);
                                } else {
                                    printf("il n'y pas assez d'athlete pour savoir qui emmener aux JO");
                                }
                                break;

                            case 4 /* marathon */:
                                //on nomme la chaîne de caractère épreuve en fonction du choix de l'épreuve
                                strcpy(epreuve, "marathon");
                                printf("vous avez choisi l'epreuve %s\n", epreuve);
                                char reponse3;
                                do {
                                    do {
                                        printf("Entrez la date (JJ/MM/AAAA) que vous voulez observer: \n");
                                        scanf("%2d/%2d/%4d", &date1.jour, &date1.mois, &date1.annee);
                                        //on vérifie si la date est correctement rentrée
                                        if (valideDate(date1.jour, date1.mois, date1.annee) != 0) {
                                            // on formate la date comme JJ/MM/AAAA
                                            do {
                                                printf("Entrez la deuxieme date (JJ/MM/AAAA) a laquelle vous voulez observer la difference de temps avec la premiere: \n");
                                                scanf("%2d/%2d/%4d", &date2.jour, &date2.mois, &date2.annee);

                                                if (valideDate(date2.jour, date2.mois, date2.annee) != 0) {
                                                    // on formate la date comme JJ/MM/AAAA
                                                    differenceTempsDates(athlete, epreuve, date1, date2);
                                                } else {
                                                    printf("Erreur! Entrer une nouvelle date \n");
                                                    viderBuffer();
                                                }
                                            } while (valideDate(date2.jour, date2.mois, date2.annee) == 0);
                                        } else {
                                            printf("Erreur! Entrer une nouvelle date \n");
                                            viderBuffer();
                                        }
                                    } while (valideDate(date2.jour, date2.mois, date2.annee) == 0);
                                    printf("Voulez-vous verifier la difference de temps pour d'autres dates ? (O/N): ");

                                    scanf(" %c", &reponse3);
                                } while (reponse3 == 'O' || reponse3 == 'o');

                                printf("Les statistiques de l'athlete %s pour l'epreuve %s:\n", athlete, epreuve);
                                char *fichier_sortie_epreuve3 = malloc(50);
                                //on renomme la chaîne de caractère en athlète

                                strcpy(fichier_sortie_epreuve3, athlete);
                                //on ajoute _ et le nom de l'épreuve à la chaîne
                                strcat(fichier_sortie_epreuve3, "_");
                                strcat(fichier_sortie_epreuve3, epreuve);
                                //on ajoute .txt a la fin de nom_fichier
                                strcat(fichier_sortie_epreuve3, ".txt");
                                char *fichier_entree_nom3 = malloc(50);
                                strcpy(fichier_entree_nom3, athlete);
                                //on ajoute .txt a la fin de nom_fichier
                                strcat(fichier_entree_nom3, ".txt");

                                tri_epreuve_date(fichier_entree_nom3, epreuve, fichier_sortie_epreuve3);
                                afficheSatistique(athlete, epreuve);

                                //on va vérifier si dans le fichier qui comporte les moyennes de tous athletes pour cette epreuve, comprend au moins 3 athlètes
                                int i3=0;
                                FILE *fichier3 = fopen("statistiquess100m.txt", "r");
                                rewind(fichier3);
                                AthleteMoyenne fiches3[100];
                                char lignes3[200];
                                // Lire les données depuis le fichier d'entrée
                                while (fgets(lignes3, 199, fichier3)) {
                                    if (sscanf(lignes3, "%49s %f",
                                               fiches3[i].nom,
                                               &fiches3[i].moyenne) == 2 ) {

                                        i++;
                                    }
                                }

                                rewind(fichier3);
                                fclose(fichier3);
                                if (i3 >= 3) {
                                    printf(" Connaitre les 3 meilleurs athletes a l'epreuve %s: \n", epreuve);
                                    Meilleurs_Athletes(epreuve);
                                } else {
                                    printf("il n'y pas assez d'athlete pour savoir qui emmener aux JO");
                                }
                                break;

                            case 5 /* relais */:
                                //on nomme la chaîne de caractère épreuve en fonction du choix de l'épreuve
                                strcpy(epreuve, "relais");
                                printf("vous avez choisi l'epreuve %s", epreuve);

                                printf("Les statistiques de l'athlete %s pour l'epreuve %s:\n", athlete, epreuve);
                                char *fichier_sortie_epreuve4 = malloc(50);
                                //on renomme la chaîne de caractère en athlète

                                strcpy(fichier_sortie_epreuve4, athlete);
                                //on ajoute _ et le nom de l'épreuve à la chaîne
                                strcat(fichier_sortie_epreuve4, "_");
                                strcat(fichier_sortie_epreuve4, epreuve);
                                //on ajoute .txt a la fin de nom_fichier
                                strcat(fichier_sortie_epreuve4, ".txt");
                                char *fichier_entree_nom4 = malloc(50);
                                strcpy(fichier_entree_nom4, athlete);
                                //on ajoute .txt a la fin de nom_fichier
                                strcat(fichier_entree_nom4, ".txt");
                                tri_epreuve_date1(fichier_entree_nom4, epreuve, fichier_sortie_epreuve4);
                                afficheSatistique1(athlete, epreuve);
                                char reponse4;
                                do {
                                    do {
                                        printf("Entrez la date (JJ/MM/AAAA) que vous voulez observer: \n");
                                        scanf("%2d/%2d/%4d", &date1.jour, &date1.mois, &date1.annee);
                                        //on vérifie si la date est correctement rentrée
                                        if (valideDate(date1.jour, date1.mois, date1.annee) != 0) {
                                            // on formate la date comme JJ/MM/AAAA
                                            do {
                                                printf("Entrez la deuxieme date (JJ/MM/AAAA) a laquelle vous voulez observer la difference de temps avec la premiere: \n");
                                                scanf("%2d/%2d/%4d", &date2.jour, &date2.mois, &date2.annee);

                                                if (valideDate(date2.jour, date2.mois, date2.annee) != 0) {
                                                    // on formate la date comme JJ/MM/AAAA
                                                    differenceTempsDates(athlete, epreuve, date1, date2);
                                                } else {
                                                    printf("Erreur! Entrer une nouvelle date \n");
                                                    viderBuffer();
                                                }
                                            } while (valideDate(date2.jour, date2.mois, date2.annee) == 0);
                                        } else {
                                            printf("Erreur! Entrer une nouvelle date \n");
                                            viderBuffer();
                                        }
                                    } while (valideDate(date2.jour, date2.mois, date2.annee) == 0);
                                    printf("Voulez-vous verifier la difference de temps pour d'autres dates ? (O/N): ");

                                    scanf(" %c", &reponse4);
                                } while (reponse4 == 'O' || reponse4 == 'o');
                                break;

                            default:
                                printf("ce choix n'est pas possible \n");
                                printf("veuillez choisir le bon numero pour l'epreuve\n");
                                viderBuffer();
                                break;
                        }
                    }while (n_epreuve < 1 || n_epreuve > 5);
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