#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "funcoes.h"

#define TOTAL 5

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

typedef struct parametros{
	int argc;
	char **argv;
}parametros;

struct nodo {
    int newsockfd;
};

struct nodo nodo[5];

void *cliente(void *arg) {
    long cid = (long)arg;
    int i, n;
    char buffer[256];
	int s = 0;
    while (1) {
        bzero(buffer,sizeof(buffer));
        n = read(nodo[cid].newsockfd,buffer,50);
		if( s == 0){
            cadastrar(buffer);
            s++;
        }
	
        printf("Recebeu: %s - %lu\n", buffer,strlen(buffer));
		if(strcmp(buffer,"abrir\n") == 0){
            if(estado_porta == 1){
                snprintf(mensagem_cliente, sizeof(mensagem_cliente)-1,"Porta já está aberta!\n");
                n = write(nodo[cid].newsockfd,mensagem_cliente,256);
            } else{
            snprintf(buffer,sizeof(buffer)-1,"Digite Sua Senha!");
            n = write(nodo[cid].newsockfd,buffer,256);
            n = read(nodo[cid].newsockfd,buffer,256);
            open_door(buffer);
            n = write(nodo[cid].newsockfd,mensagem_cliente,256);
            }
}
        if (n <= 0) {
            printf("Erro lendo do socket id %lu!\n", cid);
            close(nodo[cid].newsockfd);
            nodo[cid].newsockfd = -1;

            pthread_exit(NULL);
        }
        // MUTEX LOCK - GERAL
        pthread_mutex_lock(&m);
		//if(strcmp(buffer,"abrir\n") == 0){
		//	printf("Porta Aberta");
//}
        for (i = 0;i < TOTAL; i++) {
            if ((i != cid) && (nodo[i].newsockfd != -1)) {
                n = write(nodo[i].newsockfd,buffer,50);
                if (n <= 0) {
                    printf("Erro escrevendo no socket id %i!\n", i);
//                    close(nodo[i].newsockfd);
//                    nodo[i].newsockfd = -1;
                }
            }
        }
        pthread_mutex_unlock(&m);
        // MUTEX UNLOCK - GERAL
    }
}

void *server(void *arg){
	struct parametros *servidor1 = (parametros*)arg;
	int argc = servidor1->argc;
	char **argv = servidor1->argv;

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    int sockfd, portno;
    pthread_t t;
    long i;

    if (argc < 2) {
        printf("Erro, porta nao definida!\n");
        printf("./SOFTWARE PORTA");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Erro abrindo o socket!\n");
        exit(1);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        printf("Erro fazendo bind!\n");
        exit(1);
    }
    listen(sockfd,5);

    for (i = 0; i < TOTAL; i++) {
      nodo[i].newsockfd = -1;
    }
    while (1) {
        for (i = 0; i < TOTAL; i++) {
          if (nodo[i].newsockfd == -1) break;
        }
        nodo[i].newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
        // MUTEX LOCK - GERAL
        pthread_mutex_lock(&m);
        if (nodo[i].newsockfd < 0) {
            printf("Erro no accept!\n");
            exit(1);
        }
        pthread_create(&t, NULL, cliente, (void *)i);
        pthread_mutex_unlock(&m);
        // MUTEX UNLOCK - GERAL
    }
    //    close(sockfd);
    return 0; 
}
