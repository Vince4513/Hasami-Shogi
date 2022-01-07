#include <stdio.h>
#define VRAI 1
#define FAUX 0

typedef struct Cas{
    int occupe;
    char valeur;
    } Case;
    
typedef struct Plat{
    Case cas [9][9];
    int nbB;
    int nbN;
    
    } Plateau;


void remplissage_Plateau(Plateau *P){
    int i,j;
    P->nbB=18;
    P->nbN=18;
    i=0;
// Remplissage des pions noirs
    while(i<2){
        j=0;
        while(j<9){
            P->cas[i][j].occupe=VRAI;
            P->cas[i][j].valeur='N';
            j++;
        }
        i++;
    }
// remplissage des cases vides
    while(i<7){
            j=0;
            while(j<9){
                P->cas[i][j].occupe=FAUX;
                P->cas[i][j].valeur='o';
                j++;
            }
            i++;
        }
// Remplissage des pions blancs
     while(i<9){
        j=0;
        while(j<9){
            P->cas[i][j].occupe=VRAI;
            P->cas[i][j].valeur='B';
            j++;
        }
        i++;
    }

}

void matrice_affichage (Case mat[9][9]){
	int i,j;
        
    /* Affichage des indices de colonnes */
    printf("    ");
    for (j=0; j<9; j++) printf("%d  ",j+1);
    printf("\n");
        
    /* Affichage de la matrice */
    for (i=0; i<9; i++) {
        printf("%c   ",'A'+i);
        for (j=0; j<9; j++) printf("%c  ", mat[i][j].valeur);
        printf("\n");
    }
	
    printf("\n");
}

void deplacementv1(Plateau *P){
  char virgule,ldep,larr;
  int cdep,carr,valide;
  valide=FAUX;
  while(valide=FAUX){
        printf("Saisir la position d'arrivée et  de départ suivant ce format : posDépart,PosArrivé\n");
        scanf("%c",&ldep);
        scanf("%d",&cdep);
        scanf("%c",&virgule);
        scanf("%c",&larr);
        scanf("%d",&carr);
        if(ldep>='A' && ldep <='I' && cdep>=1 && cdep<=9 && larr>='A' && larr<='I' && carr >=1 && carr<=8){
             while((nbPionBlanc() > 5)||(nbPionNoir() > 5)){ 
	       T = blanc;
	       if (M[ldep][cdep] == T){
		 if(cdep == carr || ldep == larr){
		   if(length(ldep,larr,cdep,carr) <= 2){
		     if(M[larr][carr].occupé != FAUX){
		       deplacement();
		       T = noir;
		     }
		     else { printf("La ");
		     }
		   }
		   else{ 
		   }
		 }
		 else{ printf("Déplacez vous en colonne ou en ligne.\n");
		 }
	       }
	       else{ printf("Choisissez un pion de votre couleur.\n");
	       }
	     }
            
            
            }
        else{
            printf("veuillez saisir un déplacement valide\n");
            }
        }
      
}

        
int main(){
    Plateau Plat;
    char joueurcour;
    joueurcour='B';
    remplissage_Plateau(&Plat);
    matrice_affichage(Plat.cas);
    printf("début de la partie\n");
    printf("Tour des %c\n",joueurcour);
    deplacementv1(&Plat);
    return 0;
        
}
