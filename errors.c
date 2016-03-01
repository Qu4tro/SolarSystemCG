#include "errors.h"

void print_error(int error){

    switch (error) {
        case NO_ERROR:
            printf("NO_ERROR");
            break;

        case INVALID_ARGS:
            printf("Gerador não gera nenhum modelo do tipo indicado.\n");
            break;

        case FILE_DOES_NOT_EXIST:
            printf("O ficheiro de input não existe!\n");
            break;

        case UNREADABLE_FILE:
            printf("Não foi possivel ler o ficheiro dado! Verifica se tem as permissões necessárias.\n");
            break;

        default:
            printf("Erro desconhecido!");
            break;
            
    }
}
