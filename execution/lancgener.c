#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#define MinU 15
#define MaxU 45
#define MinD 2
#define MaxD 10

int main()
{
int a,b;
pid_t ret, fils_mort;
int i=0,status;
char nom[10];
char indicea[3],indiceb[3];

char chaine[30]; 

printf("Lancement de generMarkov\n");
while(i<50){

ret=fork();//creation du fils
	
srand(time(NULL) + getpid()); //initialisation du temps pour la generation des nombres aleatoire

switch(ret){
case -1 : /*erreur*/
        perror("pb fork");
        exit(2);
case 0: /*le processus fils exécute la commande "./generMarkov -f filename Up Down" */

	//generation des nombres aleatoire dans un intervalle defini par [MinU,MaxU] pour a et [MinD,MaxD]
	a = rand()%(MaxU-MinU) +MinU;
	b = rand()%(MaxD-MinD) +MinD;

	//creation du nom du fichier utiliser par generMarkov sous le format Matrice"i" où "i" est le numero du processus
        snprintf(nom, 10, "Matrice%d", i);
	
	//convertion des variables a et b en chaine de caractere dans la variable indicea et indiceb
	snprintf(indicea, 3, "%d", a);
	snprintf(indiceb, 3, "%d", b);

        FILE* fichier = NULL;

        fichier = fopen("fichierUD", "a+");

        if (fichier != NULL)
       {
        // On lit et on écrit dans le fichier
        	fprintf(fichier, "%s		%s\n", indicea,indiceb);
        	fclose(fichier); // On ferme le fichier qui a été ouvert
       }else{

		printf("Impossible de creer le fichier pour les couple U D\n");
		exit(0);

       }

	//affichage argument a passé a generMarkov
        //printf("lancement de genere Markov %d avec nom du fichier: %s et U=%s D=%s fin\n\n\n",i,nom,indicea,indiceb);

	//excecution du progragramme generMarkov avec les differents arguments
	execlp("/root/Documents/TER/execution/generMarkov","generMarkov","-f",nom,indicea,indiceb,NULL);
	exit(0);

default: /*le processus père */
	fils_mort=wait(&status);//On attend que le procceessus fils finisse d'executer generMarkov avant que le pere excexute le reste du programme
	if(WIFSIGNALED(status))
	 {
	   printf("vous avez tuez mon fils\n");
	   printf("je suis le père; le code de retour de mon fils est %d\n",WEXITSTATUS(status));
	}
    }


i++;
}
printf("\n\n");
i=0;
printf("Lancement de gthLD\n");
while(i<50){

ret=fork();//creation du fils

switch(ret){
case -1 : /*erreur*/
        perror("pb fork");
        exit(2);
case 0: /*le processus fils exécute la commande "./generMarkov -f filename Up Down" */

	//creation du nom du fichier utiliser par generMarkov sous le format Matrice"i" où "i" est le numero du processus
        snprintf(nom, 10, "Matrice%d", i);

	//affichage argument a passé a generMarkov
        //printf("lancement de Gthld %d avec nom du fichier: %s fin\n\n\n",i,nom);
	//excecution du progragramme generMarkov avec les differents arguments
	execlp("/root/Documents/TER/execution/gthLD","gthLD","-f",nom,"Rii",NULL);

	exit(0);

default: /*le processus père */
	fils_mort=wait(&status);//On attend que le procceessus fils finisse d'executer generMarkov avant que le pere excexute le reste du programme
	
	if(WIFSIGNALED(status))
	 {
	   printf("vous avez tuez mon fils\n");
	   printf("je suis le père; le code de retour de mon fils est %d\n",WEXITSTATUS(status));
	}
    }


i++;
}
printf("\n\n");
printf("Lancement de rewardComponentMit\n");
i=0;

while(i<50){

ret=fork();//creation du fils

switch(ret){
case -1 : /*erreur*/
        perror("pb fork");
        exit(2);
case 0: /*le processus fils exécute la commande "./generMarkov -f filename Up Down" */

	//creation du nom du fichier utiliser par generMarkov sous le format Matrice"i" où "i" est le numero du processus
        snprintf(nom, 10, "Matrice%d", i);

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

	//affichage argument a passé a generMarkov
        //printf("lancement de rewardComponentMit %d avec nom du fichier: %s et U=%s D=%s fin\n\n\n",i,nom,indicea,indiceb);
	//printf("..");
	
	//excecution du progragramme generMarkov avec les differents arguments
	execlp("/root/Documents/TER/execution/rewardComponentMit","rewardComponentMit","-f",nom,indicea,indiceb,NULL);
	exit(0);

default: /*le processus père */
	fils_mort=wait(&status);//On attend que le procceessus fils finisse d'executer generMarkov avant que le pere excexute le reste du programme
	if(WIFSIGNALED(status))
	 {
	   printf("vous avez tuez mon fils\n");
	   printf("je suis le père; le code de retour de mon fils est %d\n",WEXITSTATUS(status));
	}
    }


i++;
}
printf("\n");
printf("Finnnnnnnnnnnnnnnn");
printf("\n\n");

i=0;

double perte=0, Consenergie=0, NombreMoyn=0;
FILE* fichierRF = NULL;
FILE* fichierR = NULL;

printf("");

fichierRF = fopen("fichierReward", "a+");
fprintf(fichierRF,"U;D;P;E;NM\n");
fclose(fichierRF);
while(i<50)
{
	snprintf(chaine, 30, "Matrice%d.resultat", i);
	


        fichierR = fopen(chaine, "r");

        if (fichierR != NULL)
       {
        // On lit et on écrit dans le fichier
		/*fscanf(fichier, "%s		%s\n", indicea,indiceb);
        	fclose(fichier); // On ferme le fichier qui a été ouvert*/
		fscanf(fichierR,"%12d  %12d",&a,&b);
		fscanf(fichierR,"  %lf  %lf  %lf",&perte,&Consenergie,&NombreMoyn);
		/*fscanf(fichierR,"%12d  ", a);
		fscanf(fichierR,"%12d  ", b);
		fscanf(fichierR,"%.12lf  ", perte);
		fscanf(fichierR,"%.12lf  ", Consenergie);
		fscanf(fichierR,"%.12lf  ", NombreMoyn);*/
		fclose(fichierR);
       }else{

		printf("Impossible d'ouvire le fichier .resultats\n");
		exit(0);

       }

	

        fichierRF = fopen("fichierReward", "a+");
        if (fichierRF != NULL)
       {
        // On lit et on écrit dans le fichier
		/*fprintf(fichierRF,"%12d  ", &a);
		fprintf(fichierRF,"%12d  ", &b);
		fprintf(fichierRF,"%.12lf  ", &perte);
		fprintf(fichierRF,"%.12lf  ", &Consenergie);
		fprintf(fichierRF,"%.12lf  \n", &NombreMoyn);*/
		fprintf(fichierRF,"%d;%d;%.12lf;%.12lf;%.12lf\n",a,b,perte,Consenergie,NombreMoyn);
        	fclose(fichierRF); // On ferme le fichier qui a été ouvert
       }else{

		printf("Impossible de creer le fichier final pour les  Reward finale\n");
		exit(0);

       }

i++;
}


} 

  
