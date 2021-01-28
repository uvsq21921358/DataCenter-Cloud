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

char chaine[20]; 

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

/**
*ce qui serai bien c'est de pouvoir mettre le code ici pour l'enregistrement des valeurs Up Down
*avant l'affichage

**/


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
	printf("\n\n"); 
        printf("lancement de genere Markov %d avec nom du fichier: %s et U=%s D=%s fin\n\n\n",i,nom,indicea,indiceb);
	
	//excecution du progragramme generMarkov avec les differents arguments
	execlp("/root/Documents/test/test/alleatoire/generMarkov","generMarkov","-f",nom,indicea,indiceb,NULL);
	exit(0);

default: /*le processus père */
	fils_mort=wait(&status);//On attend que le procceessus fils finisse d'executer generMarkov avant que le pere excexute le reste du programme
	printf("je suis le père mon pid est %d\n",getpid());
	printf("pid de mon fils, %d\n", ret);
	if(WIFEXITED(status))/*veirifie s'il s'est terminé avec un exit*/
	{
	  printf("mon fils s'est terminé normalement\n");
	  printf("je suis le père; le code de retour de mon fils est %d\n",WEXITSTATUS(status));
	}
	if(WIFSIGNALED(status))
	 {
	   printf("vous avez tuez mon fils\n");
	   printf("je suis le père; le code de retour de mon fils est %d\n",WEXITSTATUS(status));
	}
    }


i++;
}

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

	//affichage argument a passé a generMarkov
	printf("\n\n"); 
        printf("lancement de Gthld %d avec nom du fichier: %s fin\n\n\n",i,nom);
	
	//excecution du progragramme generMarkov avec les differents arguments
	execlp("/root/Documents/TER/GenerationdesMatrices/distribution/gthLD","gthLD","-f",nom,"Rii",NULL);
printf("test");
	exit(0);

default: /*le processus père */
	fils_mort=wait(&status);//On attend que le procceessus fils finisse d'executer generMarkov avant que le pere excexute le reste du programme
	printf("je suis le père mon pid est %d\n",getpid());
	printf("pid de mon fils, %d\n", ret);
	if(WIFEXITED(status))/*veirifie s'il s'est terminé avec un exit*/
	{
	  printf("mon fils s'est terminé normalement\n");
	  printf("je suis le père; le code de retour de mon fils est %d\n",WEXITSTATUS(status));
	}
	if(WIFSIGNALED(status))
	 {
	   printf("vous avez tuez mon fils\n");
	   printf("je suis le père; le code de retour de mon fils est %d\n",WEXITSTATUS(status));
	}
    }


i++;
}



} 

  
