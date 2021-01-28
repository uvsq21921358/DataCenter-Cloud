#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#define MaxU 50

int main()
{
int a=0,b=1,mat=0;
pid_t ret, fils_mort;
int i=0,j =1,status;
char nom[12];
char indicea[4],indiceb[4];
int valMax = 0;
char chaine[32];
double perte=0, Consenergie=0, NombreMoyn=0;

printf("Lancement de generMarkov\n");
while(i<MaxU-1){//valeur de U


j=1;
while(j<i+2){//toutes les valeurs possibles de D entre 1 et la valeur Actutelle de U
ret=fork();//creation du fils
switch(ret){
case -1 : /*erreur*/
        perror("pb fork");
        exit(2);
case 0: /*le processus fils exécute la commande "./generMarkov -f filename Up Down" */

		a = i+2;
		b = j ;
		//creation du nom du fichier utiliser par generMarkov sous le format Matrice"i" où "i" est le numero du processus
		snprintf(nom, 12, "Matrice%d", mat);
        mat++;
		//convertion des variables a et b en chaine de caractere dans la variable indicea et indiceb
		snprintf(indicea, 4, "%d", a);
		snprintf(indiceb, 4, "%d", b);

        FILE* fichier = NULL;

        fichier = fopen("fichierUD", "a+");

        if (fichier != NULL)
        {
			//on écrit dans le fichier
        	fprintf(fichier, "%s		%s\n", indicea,indiceb);
        	fclose(fichier); // On ferme le fichier qui a été ouvert
        }else{

		printf("Impossible de creer le fichier pour les couple U D\n");
		exit(0);

       }

		//excecution du progragramme generMarkov avec les differents arguments

		execlp("/root/Documents/TER/execution/generMarkov","generMarkov","-f",nom,indicea,indiceb,NULL);
		exit(0);

default: /*le processus père */
	fils_mort=wait(&status);//On attend que le procceessus fils finisse d'executer generMarkov avant que le pere excexute le reste du programme
	if(WIFSIGNALED(status))
	 {
	   printf("vous avez arreter le programme fils\n");
	   printf("le code de retour du fils est %d\n",WEXITSTATUS(status));
	}



  }
	j++;
	mat++;
}

i++;
}

printf("\n");
i=0;
printf("Lancement de gthLD\n");

valMax = (MaxU * (MaxU - 1))/2;
while(i<valMax){//1225 = 50*49/2

ret=fork();//creation du fils

switch(ret){
case -1 : /*erreur*/
        perror("pb fork");
        exit(2);
case 0: /*le processus fils exécute la commande "./generMarkov -f filename Up Down" */

		//creation du nom du fichier utiliser par generMarkov sous le format Matrice"i" où "i" est le numero du processus
        snprintf(nom, 12, "Matrice%d", i);

		//excecution du progragramme generMarkov avec les differents arguments
		execlp("/root/Documents/TER/execution/gthLD","gthLD","-f",nom,"Rii",NULL);

		exit(0);

default: /*le processus père */
		fils_mort=wait(&status);//On attend que le procceessus fils finisse d'executer generMarkov avant que le pere excexute le reste du programme
	
		if(WIFSIGNALED(status))
		{
			printf("vous avez arreter le programme fils\n");
			printf("le code de retour de mon fils est %d\n",WEXITSTATUS(status));
		}
    }


i++;
}

printf("\n");
printf("Lancement de rewardComponentMit\n");
i=0;

while(i<valMax){

ret=fork();//creation du fils

switch(ret){
case -1 : /*erreur*/
        perror("pb fork");
        exit(2);
case 0: /*le processus fils exécute la commande "./generMarkov -f filename Up Down" */

		//creation du nom du fichier utiliser par generMarkov sous le format Matrice"i" où "i" est le numero du processus
        snprintf(nom, 12, "Matrice%d", i);

		FILE* fichier = NULL;

        fichier = fopen("fichierUD", "r");

        if (fichier != NULL)
       {
        // On lit et on écrit dans le fichier
		int lec=0;
        	while(lec<i+1){
			fscanf(fichier, "%s		%s\n", indicea,indiceb);
			lec++;
		}
        	fclose(fichier); // On ferme le fichier qui a été ouvert
       }else{

		printf("Impossible de d'ouvrir le fichier pour les couple U D\n");
		exit(0);

       }
	
		//excecution du progragramme generMarkov avec les differents arguments
		execlp("/root/Documents/TER/execution/rewardComponentMit","rewardComponentMit","-f",nom,indicea,indiceb,NULL);
		exit(0);

default: /*le processus père */
		fils_mort=wait(&status);//On attend que le procceessus fils finisse d'executer generMarkov avant que le pere excexute le reste du programme
		if(WIFSIGNALED(status))
		{
			printf("vous avez arreter le programme fils\n");
			printf("le code de retour de mon fils est %d\n",WEXITSTATUS(status));
		}
    }
i++;
}
printf("\n");
i=0;

FILE* fichierRF = NULL; //fichier qui va contenir les resultats de tout les fichiers Matrice.resultat
FILE* fichierR = NULL; //les differents fichiers Matrice.resultat

printf("");

fichierRF = fopen("fichierReward", "a+");
fprintf(fichierRF,"U;D;P;E;NM\n");
fclose(fichierRF);

while(i<valMax)
{
		snprintf(chaine, 32, "Matrice%d.resultat", i);
	


       fichierR = fopen(chaine, "r");

       if (fichierR != NULL)
       {
			// On lit dans le fichier
			fscanf(fichierR,"%12d  %12d",&a,&b);
			fscanf(fichierR,"  %lf  %lf  %lf",&perte,&Consenergie,&NombreMoyn);
			fclose(fichierR);
       }else{

			printf("Impossible d'ouvire le fichier .resultats\n");
			exit(0);

       }
	   
       fichierRF = fopen("fichierReward", "a+");
       if (fichierRF != NULL)
       {
			// on écrit dans le fichier
			fprintf(fichierRF,"%d;%d;%.12lf;%.12lf;%.12lf\n",a,b,perte,Consenergie,NombreMoyn);
        	fclose(fichierRF); // On ferme le fichier qui a été ouvert
       }else{

			printf("Impossible de creer le fichier final pour les  Reward finale\n");
			exit(0);

       }

		i++;
}

printf("Finnnnnnnnnnnnnnnn");
printf("\n\n");

}

  
