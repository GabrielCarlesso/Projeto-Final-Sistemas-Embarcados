
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include "realgps.h"
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include "server1.h"

int estado_porta = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


	char mensagem_cliente [256];


struct usuario_t {
	char senha [256];
};


void cadastrar (char *buffer){
	char *senha = buffer;
	FILE *fp;
	struct usuario_t usuario;
	int i =0 ;
	memset(&usuario, 0, sizeof(struct usuario_t));
	strcpy(usuario.senha,senha);
	//usuario.senha = senha;
	//printf("Cadastro de usuarios:\n");
	//printf("Login> ");
	//scanf("%s", &usuario.login);
	//printf("senha> ");
	//scanf("%s", &usuario.senha);

	fp = fopen("login.txt", "wb");
	if (!fp){
		printf("Nao foi possivel criar o arquivo de login");
		return;
	}
	fwrite(&usuario, sizeof(struct usuario_t), 1, fp);
	fclose(fp);
}


int open_door(char *buffer){

	int cod, i;
	pthread_mutex_lock(&mutex);
		estado_porta = 1;
		snprintf(mensagem_cliente, sizeof(mensagem_cliente) -1, "Porta Aberta\n");
				
	pthread_mutex_unlock(&mutex);
	
}

void close_door(){
	pthread_mutex_lock(&mutex);
	estado_porta = 0;
	printf("*****Porta Fechada*****");

	pthread_mutex_unlock(&mutex);
}


void status (){
	pthread_mutex_lock(&mutex);
	if (estado_porta == 0){
		printf("Porta já está fechada");
	} else {
		printf("Porta já está aberta");
	}

	pthread_mutex_unlock(&mutex);
}





/*int login(){
	FILE *fp;
		struct usuario_t usuario;
		fp = fopen("login.txt", "rb");
		//if(!fp){
			//cadastrar();
			//fp = fopen("login.txt", "rb");
			if (!fp){
				printf("Não foi possivel encontrar o arquivo de login\n");
				return 0;
			}
		}
		memset(&usuario, 0, sizeof(struct usuario_t));

		fread(&usuario, sizeof(struct usuario_t), 1, fp);
		fclose(fp);
		if (!strcmp("", usuario.senha)){
				printf("nenhum usuario encontrado, abrindo cadastro!\n");
				cadastrar();
		} else{
			int tentativas = 0;
				do{
					char senha[SENHA_MAX];
					printf("Login: ");
					scanf("%s", &login);
					printf("Senha: ");
					scanf("%s", &senha);
					if (!strcmp(login, usuario.login) && !strcmp(senha, usuario.senha)){
							printf("Bem vindo %s\n", usuario.login);
							return 1;
					} else {
							printf("Usuario ou senha invalidos!\n");
							tentativas++;
					}
				} while (tentativas < 3);
				printf("Numero maximo de tentativas alcancados!\n");
		return 0;
		}
		return 0;
}
*/
