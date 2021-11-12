#include "functions.h"

void my_memset(char* buff, char c, int size){
    int index = 0;
    while (index < size)
    {
        buff[index] = c;
        index++;
    }
}

void my_bzero(char* buff, int size){
    my_memset(buff, 0, size);
}

char* my_init(int size){
    char* buff = (char*)malloc(size);
    my_bzero(buff, size);
    return buff;
}

int is_option(char* str){
    if (str[0] == '-')
        return 1;
    return 0;
}

void set_option(options* option, char* name, char* value){
    int i = 0;
    while (name[i]){
        if (name[i] == 'c')
            option->c = value;
        if (name[i] == 'p')
            option->p = value;
        if (name[i] == 't')
            option->t = atoi(value);
        i++; 
    }
}

options* get_option(int ac, char **av){
    options* option = (options*)my_init(sizeof(options));
    int i = 0;
    while (i < ac){
        if (is_option(av[i]) == 1){
            set_option(option, av[i], av[i+1]);
        }
        i++;
    }
    return option;
}


int main(int ac, char **av)
{
    char* pieces;
    char* code;
    int attempts;

    printf("Will you find the secret code?\n");

    options* option = get_option(ac, av);

    pieces = "01234567";

    if (option->c != NULL){
        code = option->c;
    }
    else {
        code  = gen_random(pieces);
    }

    if (option->t != 0){
        attempts = option->t;
    }
    else {
        attempts = 10;
    }
    execute_game(code, pieces, attempts);
    return 0;
}