/*
*
*   int count_well_placed(char* code, char* guess);
*   int check_position(char* pieces, char c);
*   int* count_pieces(char* pieces, char* code);
*   int count_misplaced(char* code, char* guess, char* pieces);
*   char* gen_random(char* pieces);
*   void execute_game(char* code, char* pieces, int attempts);
*
*
*    void my_memset(char* buff, char c, int size);
*    void my_bzero(char* buff, int size);
*    char* my_init(int size);
*    int is_option(char* str);
*    void set_option(t_option* option, char* name, char* value);
*    t_option* get_option(int ac, char **av);
*
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct options{
    char* p;
    char* c;
    int t;
} options;

int my_strcmp(char* pieces, char* guess){

    int i, j, count = 0;

    for(i=0; pieces[i] != '\0'; i++){
        for(j=0; guess[j] != '\0'; j++){
            if(pieces[i] == guess[j]){
                count++;
            }
        }
    }

    if(count == 4){
        return 1;
    }else 
    return -1;

}

int count_well_placed(char* code, char* guess){
    int count = 0;
    int i = 0;
    while (code[i]){
        if (code[i] == guess[i])
            count++;
        i++;
    }
    return (count);
}

int check_pos(char* pieces, char c){
    int i = 0;
    while (pieces[i]){
        if (pieces[i] == c){
            return (i);
        }
        i++;
    }
    return (-1);
}


int* count_pcs(char* pieces, char* code){
    int* result_array = (int*)malloc(sizeof(int) * 8+1);
    int pos;
    int i = 0;
    while (code[i]){
        pos = check_pos(pieces, code[i]);
        result_array[pos]++;
        i++;
    }
    return (result_array);
}

int count_misplaced(char* code, char* guess, char* pieces){

    int* code_array = count_pcs(pieces, code); 
    int* guess_array = count_pcs(pieces, guess); 
    
    int result = 0;
    int i = 0;
    while (i < 8){
        int left = code_array[i];
        int right = guess_array[i];

        if (left < right){
            result += left;
        }
        else {
            result += right;
        }
        i++;
    }   
    return (((int)result) - (count_well_placed(code, guess)));
}

void execute_game(char* code, char* pieces, int attempts){
    if ((strlen(code) == 4)){

        char *guess = (char*)malloc(sizeof(char) * 5);
        int i = 0;
        
        while (i < attempts){
            printf("---");
            printf("\nRound %d\n", i);
            read(0, guess, 5);
            guess[4] = '\0';

            if (strcmp(guess, code) == 0){
                printf("Congratz! You did it!\n");
                break;
            } 
            if(my_strcmp(pieces, guess) == -1){
                printf("Wrong input!\n");
                i--;
            }
            else {
                printf("Well placed pieces: %d\n", count_well_placed(code, guess));
                printf("Misplaced pieces: %d\n", count_misplaced(code, guess, pieces));
            }
            i++;
            if (i == attempts){
                printf("That was your last attempt, loser!");
            }
        }
    }
    else {
        printf("Wrong input!\n");
    }
}

char* gen_random(char* pieces){
    char* res = (char*)malloc(sizeof(char) + 1);
    srand((unsigned int)(time(NULL)));
	int index = 0;
	for (index = 0; index < 4; index++){
		res[index] = pieces[rand() % (sizeof pieces - 1)];
	}
    res[4] = '\0';
    return res;
}
