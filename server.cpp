#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_CLIENT 20
#define MAX_MSG 1024
#define PORT 8080

int clients[MAX_CLIENT];

void* handleClient(void* arg){
    // Add your client handling logic here
    int client_fd = *(int*)arg;
    return NULL;
}

int main(){
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    pthread_t thread_client;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;// Recebe conexão sem filtros

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, MAX_CLIENT);
    printf("Server started on port: %d\n", PORT);

    socklen_t client_len = sizeof(client_addr);
    while(client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)){
        printf("Novo Cliente conectado!!!%d\n");
        pthread_create(&thread_client, NULL, handleClient, &client_fd);
        pthread_detach(thread_client); //Deixando a thread livre
    }

    close(server_fd);
    printf("Servidor desconectado!%d\n");
    return 0;
}