#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pt-1.4/pt.h"
#include "urna.h"

static char candidatos[3][100] = {"SpongeBob SquarePants","Patrick Red Star","Squidward Tentacles"};
static char db[5][100];
static int votes[5];

static int contagem[3]= {0};

/*  */
static int flag_id, flag_printCandidatos, flag_lerVoto, flag_encriptar, flag_total_votos = 0;

/**
Protothread direcionada para identificação do eleitor
 */
static int identificacao(struct pt *pt)
{
  PT_BEGIN(pt);

  while(1) {
    flag_id = 0;
    flag_printCandidatos = 0;
    flag_lerVoto = 0;
    flag_encriptar = 0;
    
    printf("\nBem vindo a eleição 2022! \nSe identifique digitando seu nome:\n");

    scanf("%s", db[flag_total_votos]);
    
    flag_printCandidatos = 1;

    PT_WAIT_UNTIL(pt, flag_id != 0);

    flag_printCandidatos = 1;

    PT_END(pt);
  }


 
}

static int printCandidatos(struct pt *pt)
{
  PT_BEGIN(pt);

  while(1) {
    
    flag_printCandidatos = 0;
 
    printf("Digite o numero do seu Candidato\n");
    printf("Candidato 1 - SpongeBob SquarePants\n");
    printf("Candidato 2 - Patrick Red Star\n");
    printf("Candidato 3 - Squidward Tentacles\n");

    scanf("%i", &votes[flag_total_votos]);

    flag_encriptar = 1;

    PT_WAIT_UNTIL(pt, flag_printCandidatos != 0);
    
    PT_END(pt);
  }
}


static int shuffle(struct pt *pt){
  PT_BEGIN(pt);

  while(1) {
  
    //Embaralha os elementos:
    for (int i = 0; i < flag_total_votos; i++)
    {
    int r = rand() % flag_total_votos;

    int aux;
    char temp[100];

    strcpy(temp, db[i]);
    aux = votes[i];

    strcpy(db[i], db[r]);
    votes[i] = votes[r];

    strcpy(db[r], temp);
    votes[r] = aux;
    }
    
    flag_encriptar = 0;
    flag_id = 1;
    flag_total_votos++;
    
    
    PT_WAIT_UNTIL(pt, flag_encriptar != 0 );

    
    PT_END(pt);
  }
}

static int resultado(struct pt *pt){
  PT_BEGIN(pt);
float porcent[3];
  while(1) {

    PT_WAIT_UNTIL(pt, flag_total_votos == 5 );
    
    
    for (int i = 0; i < flag_total_votos; i++)
    {
      if (votes[i] == 1)
      {
        contagem[0]++; 
      } 
      else if(votes[i] == 2)
      {
        contagem[1]++;
      }
      else if(votes[i] == 3)
      {
        contagem[2]++;
      } 
    }

    porcent[0] = contagem[0] / 5.0 * 100;
    porcent[1] = contagem[1] / 5.0 * 100;
    porcent[2] = contagem[2] / 5.0 * 100;


    int vencedor, second, third;
    
    if (contagem[0] > contagem[1] && contagem[0] > contagem[2])
    {
      vencedor = 0;
      if (contagem[1] > contagem[2]){
        second = 1;
        third = 2;
      }
      else{
        second = 2;
        third =1;
      }
    }
    else if (contagem[1] > contagem[0] && contagem[1] > contagem[2])
    {
      vencedor = 1;
      if (contagem[0] > contagem[2]){
        second = 0;
        third = 2;
      }
      else{
        second = 2;
        third = 0;
      }
    }
    else if(contagem[2] > contagem[0] && contagem[2] > contagem[1]){
      vencedor = 2;
      if (contagem[0] > contagem[1]){
        second = 0;
        third = 1;
      }
      else{
        second = 1;
        third =0;
      } 
    }

    printf("\n\nO resultado da eleição de 2022:");
    printf("\nCom %.2f%% de votos o vencedor é o %s", porcent[vencedor], candidatos[vencedor]);
    printf("\n%s em segundo lugar com %.2f%% de votos e %s terceiro com %.2f%% de votos", candidatos[second],porcent[second], candidatos[third], porcent[third]);

    printf("\n\nVotos computados: \n");
    for (int i = 0; i < flag_total_votos; i++)
    {
      printf("Eleitor: %s Voto: %i \n", db[i], votes[i]);
    }
    break;
    PT_END(pt);
  }
}



static struct pt protothread_identificacao, protothread_printCandidatos, protothread_encriptar, protothread_resultado;

int main(void)
{
  /* Initialize the protothread state variables with PT_INIT(). */
  PT_INIT(&protothread_identificacao);
  PT_INIT(&protothread_printCandidatos);
  PT_INIT(&protothread_encriptar);
  PT_INIT(&protothread_resultado);

  for(int i = 0 ; i < 5; i++) {
    identificacao(&protothread_identificacao);
    printCandidatos(&protothread_printCandidatos);
    shuffle(&protothread_encriptar);
    resultado(&protothread_resultado);
  }

}
