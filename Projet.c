#include <stdio.h>
#include <math.h>
#define VRAI 1  //on définit les variables VRAI et FAUX pour faciliter la compréhension du code 
#define FAUX 0  

//action clean_stdin 
//elle permet de vider le buffer quand on demande plusieurs saisies à l'utilisateur
void clean_stdin(void){ 
    int c; 
    do { 
        c = getchar(); 
    } while (c != '\n' && c != EOF); 
}

typedef struct Cas{dd
    int occupe;
    char valeur;
    } Case;
    
typedef struct Plat{
    Case cas [9][9];
    int nbB;
    int nbN;
    
    } Plateau;

// Action remplissage_Plateau
// Cette action a pour but de remplir le plateau avec les valeurs d'un début de partie
void remplissage_Plateau(Plateau *P){
    //Résultat: P : Plateau: plateau a remplir
    //Locales: i: entier: indice de parcours des lignes
    //         j: entier: indice de parcours des colonnes
    int i,j;
    P->nbB=18;    //On initialise le nombre de pions blancs à 18
    P->nbN=18;    //On initialise le nombre de pions noirs à 18
    i=0;          //On initialise i à 0 pour commencer à la première ligne
// Remplissage des pions noirs
    while(i<2){         // On parcourt les deux premières lignes du tableau
        j=0;            //On initialise j à 0 pour parcourir les colonnes
        while(j<9){             // Pour chaque ligne on parcourt les 9 colonnes
            P->cas[i][j].occupe=VRAI;   //On met la valeur de occupe a VRAI
            P->cas[i][j].valeur='N';    //On met la valeur du pion à N pour noir
            j++;
        }
        i++;
    }
// remplissage des cases vides
    while(i<7){             //On parcourt les 5 lignes du milieu
            j=0;            //On initialise j à 0 pour parcourir les colonnes
            while(j<9){          // Pour chaque ligne on parcourt les 9 colonnes  
                P->cas[i][j].occupe=FAUX;   //On met la valeur de occupe a FAUX
                P->cas[i][j].valeur='.';    //On met la valeur du pion à . (symbole du vide)
                j++;
            }
            i++;
        }
// Remplissage des pions blancs
     while(i<9){        // On parcourt les deux premières lignes du tableau
        j=0;            //On initialise j à 0 pour parcourir les colonnes
        while(j<9){         // Pour chaque ligne on parcourt les 9 colonnes
            P->cas[i][j].occupe=VRAI;   //On met la valeur de occupe a VRAI
            P->cas[i][j].valeur='B';    //On met la valeur du pion a B pour blanc
            j++;
        }
        i++;
    }

}

void affichage_Plateau (Case mat[9][9]){
	int i,j;
        
    /* Affichage des indices de colonnes */
    printf("    ");
    for (j=0; j<9; j++) printf("%d  ",j+1);
    printf("\n");
        
    /* Affichage du plateau */
    for (i=0; i<9; i++) {
        printf("%c   ",'A'+i);
        for (j=0; j<9; j++) printf("%c  ", mat[i][j].valeur);
        printf("\n");
    }
	
    printf("\n");
}

/******************************************************************************************/
/* Fonction verifiant que les données saisies par l'utilisateur sont bien dans le plateau */
/******************************************************************************************/
int dans_plateau(char lD, int cD, char lA, int cA){
  /* Données : lD,lA : caractère  */
  /*           cD,cA : entier     */
  
  return (lD>='A' && lD <='I' && cD>=0 && cD<=8 && lA>='A' && lA<='I' && cA >=0 && cA<=8); //On que chaque coordonnée se situe bien dans les limites du plateau, donc les lignes sont entre A et I et les
                                                                                           //colonnes sont entre 0 et 8 (on a décrémenté au préalable les colonnes de  1)
}
    
/******************************************************************************************/
/* Fonction verifiant que l'utilisateur utilisent bien ses pions                          */
/******************************************************************************************/
int joueurTour (char joueurcour, int lD, int cD, Plateau P){
  /* Données : lD,joueurcour : caractère  */
  /*           cD            : entier     */
  /*           P             : Plateau    */
  
  return (P.cas[lD][cD].valeur == joueurcour);  //On vérifie que la case de départ est bien occupée par un pion du joueur actuel
}

/******************************************************************************************/
/* Fonction verifiant que l'utilisateur avance bien ses pions en lignes et en colonnes    */
/******************************************************************************************/
int vert_hori(char lD, int cD, char lA, int cA){
  /* Données : lD,lA : caractère  */
  /*           cD,cA : entier     */
  
  return (lD==lA || cD==cA);        //On vérifie que le déplacement se fait bien selon une seule coordonnée, c'est à dire qu'au moins une cordonnée reste inchanége
}

/******************************************************************************************/
/* Fonction verifiant que la case d'arrivée est bien non occupée                          */
/******************************************************************************************/
int arrivée_vide(Plateau P, int lA, int cA){
  /* Données : lA : caractère  */
  /*           cA : entier     */
  /*           P  : Plateau    */
  
  return (P.cas[lA][cA].occupe==FAUX);  //On vérifie que la case d'arriée à bien occupé à FAUX
}

/******************************************************************************************/
/* Fonction verifiant que les cases entre le départ et l'arrivée sont vides               */
/******************************************************************************************/
int chemin_pion(Plateau P, int lD, int cD, int lA, int cA){
    //Données: P: plateau dont on parcourt les cases
    //         lD: indice de la ligne de départ
    //         cD: indice de la colonne de départ
    //         lA: indice de la ligne d'arrivée
    //         cA: indicde de la colonne d'arrivée
    //
    //Locales: valide: booléen: est initialisé a FAUX et prend la valeur VRAI si le déplacement est valide
  int valide = FAUX;

  //Cas ou l'on se déplace vers la droite
  if (lA == lD && cD < cA){
    while ((cD < cA) && (P.cas[lD][cD+1].occupe==FAUX)){ //On parcout les cases entre la case de départ et la case d'arrivée tant qu'elles sont vides
      cD +=1;
    }
    //On vérifie qu'on a bien atteint la case d'arrive ce qui signifie que les cases intermédiaires sont vides
    if (cD == cA){
      valide = VRAI;  // dans ce cas on passe valide à VRAI
    }
  }
  //Cas ou l'on se déplace vers la gauche
  else if (lA == lD && cD > cA) {
    while ((cD > cA) && (P.cas[lD][cD-1].occupe==FAUX)){ //On parcout les cases entre la case de départ et la case d'arrivée tant qu'elles sont vides
      cD -=1;
    }
     //On vérifie qu'on a bien atteint la case d'arrive ce qui signifie que les cases intermédiaires sont vides
    if (cD == cA){
      valide = VRAI;  // dans ce cas on passe valide à VRAI
    }
  }
 //Cas ou l'on se déplace vers le bas
  else if (cA == cD && lD < lA) {
    while ((lD < lA) && (P.cas[lD+1][cD].occupe==FAUX)){  //On parcout les cases entre la case de départ et la case d'arrivée tant qu'elles sont vides
      lD +=1;
    }
    //On vérifie qu'on a bien atteint la case d'arrive ce qui signifie que les cases intermédiaires sont vides
    if (lD == lA){
      valide = VRAI;  // dans ce cas on passe valide à VRAI
    }
  }
  //Cas ou l'on se déplace vers le haut
  else if (cA == cD && lD > lA) {
    while ((lD > lA) && (P.cas[lD-1][cD].occupe==FAUX)){  //On parcout les cases entre la case de départ et la case d'arrivée tant qu'elles sont vides
      lD -=1;
    }
    //On vérifie qu'on a bien atteint la case d'arrive ce qui signifie que les cases intermédiaires sont vides
    if (lD == lA){
      valide = VRAI; // dans ce cas on passe valide à VRAI
    }
  }
  return valide; 
}



//Action capture
//Action vérifiant si le dernier pion déplacé engendre une capture
void capture(Plateau *P,int lcour, int ccour,char joueurcour){
    //Données:lcour: entier: ligne du pion qui vient d'être déplacé
    //        ccour: entier: colonne du pion qui vient d'être déplacé
    //        joueurcour: couleur du pion qui vient d'être déplacé
    //Données/Résultats: P: Plateau du jeu
    //Locales:l: entier: indice de parcours de ligne
    //        c: entier  indice de parcours de colonne
    //       nb: entier  nombre de pions du joueur adverse
    int l,c,nb;
    // on initialise nb au nombre de pions adverses (que l'on devra modifier si il y a une capture)
    if (joueurcour=='B')
        nb=P->nbN;
    else
        nb=P->nbB;
    
    //vérification d'une capture vers le haut
    l=lcour-1;  //on  décale l'indice de ligne vers le haut
    while(l>=0 && P->cas[l][ccour].occupe==VRAI && P->cas[l][ccour].valeur!=joueurcour) //On vérifie qu'on est bien sur le plateau et on parcourt les cases en dessous jusqu'à trouver une case qui nest pas occupée par un pion
        l--;                                                                            // adverse
    if (l>=0 && P->cas[l][ccour].valeur==joueurcour){  //Si on retrouve un pion de la couleur de départ apres tous les pions de couleur adverse, alors il y a une capture
        printf("capture vers le haut\n");
        nb=nb-(lcour-l)+1;        //On soustrait au nombre de points le nombre de pions capturés
        for(l=l+1;l<lcour;l++){   //On modifie ensuite l'état des cases capturées 
            P->cas[l][ccour].occupe=FAUX;
            P->cas[l][ccour].valeur='.';
        }
    }
    //vérification d'une capture vers le bas
    l=lcour+1; //on  décale l'indice de ligne vers le bas
    while(l<=8 && P->cas[l][ccour].occupe==VRAI && P->cas[l][ccour].valeur!=joueurcour) //On vérifie qu'on est bien sur le plateau et on parcourt les cases en dessous jusqu'à trouver une case qui nest pas occupée par un pion
        l++;                                                                            // adverse
    if (l<=8 && P->cas[l][ccour].valeur==joueurcour){   //Si on retrouve un pion de la couleur de départ apres tous les pions de couleur adverse, alors il y a une capture
        printf("capture vers le bas\n");
        nb=nb-(l-lcour)+1;      //On soustrait au nombre de points le nombre de pions capturés
        for(l=l-1;l>lcour;l--){ //On modifie ensuite l'état des cases capturées 
            P->cas[l][ccour].occupe=FAUX;
            P->cas[l][ccour].valeur='.';
        }
    }
    //vérification d'une capture vers la gauche
    c=ccour-1; //on décale l'indice de colonne vers la gauche
    while(c>=0 && P->cas[lcour][c].occupe==VRAI && P->cas[lcour][c].valeur!=joueurcour) //On vérifie qu'on est bien sur le plateau et on parcourt les cases en dessous jusqu'à trouver une case qui nest pas occupée par un pion
        c--;                                                                            //adverse
    if (c>=0 && P->cas[lcour][c].valeur==joueurcour){   //Si on retrouve un pion de la couleur de départ apres tous les pions de couleur adverse, alors il y a une capture
        printf("capture vers la gauche\n");
        nb=nb-(ccour-c)+1;          //On soustrait au nombre de points le nombre de pions capturés
        for(c=c+1;c<ccour;c++){     //On modifie ensuite l'état des cases capturées
            P->cas[lcour][c].occupe=FAUX;
            P->cas[lcour][c].valeur='.';
        }
    }
    //vérification d'une capture vers la droite
    c=ccour+1;  //on décale l'indice de colonne vers la droite
    while(c<=8 && P->cas[lcour][c].occupe==VRAI && P->cas[lcour][c].valeur!=joueurcour) //On vérifie qu'on est bien sur le plateau et on parcourt les cases en dessous jusqu'à trouver une case qui nest pas occupée par un pion
        c++;                                                                            //adverse
    if (c<=8 && P->cas[lcour][c].valeur==joueurcour){   //Si on retrouve un pion de la couleur de départ apres tous les pions de couleur adverse, alors il y a une capture
        printf("capture vers la droite\n");
        nb=nb-(c-ccour)+1;       //On soustrait au nombre de points le nombre de pions capturés
        for(c=c-1;c>ccour;c--){  //On modifie ensuite l'état des cases capturées
            P->cas[lcour][c].occupe=FAUX;
            P->cas[lcour][c].valeur='.';
        }
    }
    //on attribue au nombre de pions du joueur adverse la nouvelle valeur de nb 
    if (joueurcour=='B')
        P->nbN=nb;
    else
        P->nbB=nb;
}

// Action deplacement
//Action demandant la saisie d'un déplacement puis effectue le deplacement sur le plateau passé en paramètres une fois que le déplacement saisi est valide
void deplacement(Plateau *P,char joueurcour){
    //Données: joueurcour: caractère : caractère qui détermine si c'est le tour du joueur noir ou blanc
    //Données/Résultat: P plateau : plateau pricipal qu'on va actualiser par rapport au déplacement
    //locales: ldep: caractère: valeur de la ligne de départ saisie par l'utilisateur (lettre entre A et I)
    //         larr: caractère: valeur de la ligne d'arrivée saisie par l'utilisateur (lettre entre A et I)
    //         cdep: entier: valeur de la colonne de départ (entre 1 et 9)
    //         carr: entier: valeur de la colonne d'arrivée (ente 1 et 9)
    //         ldepint: entier: valeur de la ligne de départ convertie en entier (ex: A est la ligne 0)
    //         larrint: entier: valeur de la colonne de départ convertie en entier (ex: A est la colonne 0)
    //         valide: booléen: détermine si le mouvement est valide
    
    //Initialisation
    char ldep,larr;
    int ldepint,cdep,larrint,carr,valide;
    valide=FAUX;
    
    while(valide==FAUX){ // tant que le déplacement n'est pas valide, on demande à l'utilisateur de saisir un nouveau déplacement
        printf("Saisir la position d'arrivée et  de départ suivant ce format : posDépart,PosArrivé\n"); //On demande de saisir un déplacement 
        scanf("%c%d,%c%d",&ldep,&cdep,&larr,&carr); 
        clean_stdin(); //On vide le buffer 
        ldepint=ldep-65; // on convertit les lettes en entiers à partir du codage ASCII afin de pouvoir manipuler numériquement les indices de ligne
        larrint=larr-65;
        cdep=cdep-1; // on décale de 1 les indices des colonnes pour correspondre aux indices en c
        carr=carr-1;
        
        if(dans_plateau(ldep,cdep,larr,carr) && joueurTour(joueurcour,ldepint,cdep,*P) && vert_hori(ldep,cdep,larr,carr) && arrivée_vide(*P,larrint,carr) && ( chemin_pion(*P,ldepint,cdep,larrint,carr) || (fabs(ldepint-larrint) +fabs(cdep-carr))==2)){ // On utilise les sous-programmes réalisés pour vérifier que le déplacement est valide (voir ci-dessus), de plus on utilise la valeur absolue pour vérifier si un saut est valide (c'est a dire que le pion se déplace de deux cases seulement sans avoir besoin de contrôler la case intermédiaire, ceci est détaillé dans le compte rendu)
            valide=VRAI;
            }
        else
            printf("Veuillez saisir un déplacement valide\n");
            
        }
    //Une fois que l'utilisateur a saisi un mouvement valide, on effectue le déplacement
    printf("mouvement valide\n");
    P->cas[ldepint][cdep].occupe=FAUX; // On vide la case de départ
    P->cas[ldepint][cdep].valeur='.'; 
    P->cas[larrint][carr].occupe=VRAI; // On pose sur la case d'arrivée le pion du joueur
    P->cas[larrint][carr].valeur=joueurcour;
    capture(P,larrint,carr,joueurcour); //On vérifie si le déplacement effectué a engendré une capture
    system("clear"); //On vide le buffer
}




        
int main(){
    Plateau Plat;
    char joueurcour;
    joueurcour='B';
   
    remplissage_Plateau(&Plat);
    affichage_Plateau(Plat.cas);
    printf("début de la partie\n");
    while(Plat.nbB>5 && Plat.nbN>5){ //On effectue des déplacements tant que la partie n'est pas finie (chaque joueur a plus de 5 pions)
        printf("Tour des %c\n",joueurcour);
        printf("points des blancs: %d\n",Plat.nbB);
        printf("points des noirs: %d\n",Plat.nbN);
        deplacement(&Plat,joueurcour);
        affichage_Plateau(Plat.cas);
        if (joueurcour=='B')
            joueurcour='N';
        else
            joueurcour='B';
    }
    if (Plat.nbB>5)
        printf("Les blancs ont gagné %d à %d\n",Plat.nbB,Plat.nbN);
    else
        printf("Les noirs ont gagné %d à %d\n",Plat.nbN,Plat.nbB);
    return 0;
        
}
