#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void get_hint_word(char word[])
{
    srand(time(NULL));
    int random_number = rand() % 10;
    const char *hints[] = {
        "Something you solve for fun", "Flies into space", "A genre of music with lots of syncopation", "A pattern of beats in music without a vowel",
        "A unit of digital information", "A large striped wild cat", "A spider's tangled web", "A giant group of stars and planets",
        "Sailors who steal on the seas", "An ancient science about turning metals to gold"}; //add more later
    const char *words[] = {
        "puzzle", "rocket", "jazz", "rhythm",
        "byte", "tiger", "web", "galaxy",
        "pirate", "alchemy"}; //add more later
    printf("Hint: %s\n\n", hints[random_number]);
    strcpy(word, words[random_number]);
}
void letter_or_blank(const char word[], const char all_guesses[]){
    for(int i=0; word[i]!='\0'; i++){
        for(int j=0; all_guesses[j]!='\0'; j++){
            if(word[i] == all_guesses[j]){
                printf("%c ", word[i]);
                break;
            }else if(all_guesses[j+1] == '\0'){
                printf("_ ");
            }else continue;
        }
    }
}
void drawHangman(int wrong_guesses){
    const char *hangman[]={
        "+-----------+  \n",
        "|           |  \n",
        "|           O  \n",
        "|          /|\\\n",
        "|           |  \n",
        "|          / \\\n",
        "|\n================\n"
    };
    for(int i=0; i<=wrong_guesses; i++){
        if(i == 0)  printf("%s", hangman[0]);
        else if(i> 0 && i < 6) printf("%s", hangman[i]);
        else if(i == 6) printf("%s", hangman[6]);
    }
}
int main()
{
    printf("\t\t\t\t\t!!!WELCOME TO MY HANGMAN GAME!!!\n\n");
    printf("\tRULES: You will be given a hint and you have to guess the word using one letter at a time.\n\n");
    char secret_word[20];
    char guessed[15];
    int wrong_guesses=0;
    get_hint_word(secret_word);
    for(int i=0; i<15; i++){
        printf("\nGuess a letter: ");
        scanf(" %c", &guessed[i]);
        while (getchar() != '\n' && getchar() != EOF); // flush input buffer
        char current_guess = guessed[i];
        int already_guessed = 0;
        for(int j=0; j<i; j++){
            if(guessed[j] == current_guess){
                already_guessed = 1;
                break;
            }
        }
        if(already_guessed){
            printf("You have already guessed this letter. Go Again.\n");
            i--; // decrement i to repeat the same index
            continue;
        }
        int found=0;
        for(int i=0; secret_word[i]!='\0'; i++){
            if(secret_word[i] == current_guess){
                found = 1;
                break;
            }
        }
        if(!found){
            wrong_guesses++;
            printf("Wrong guess! You have %d wrong guesses left.\n", 6 - wrong_guesses);
            drawHangman(wrong_guesses);
            if(wrong_guesses >= 6){
                printf("\t\t\tYou lost! The word was: %s\n", secret_word);
                return 0;
            }
        }
        for(int i=0; secret_word[i]!='\0'; i++){
            int letter_found = 0;
            for(int i=0; secret_word[i]!='\0'; i++){
                for(int j=0; guessed[j]!='\0'; j++){
                    if(secret_word[i] == guessed[j]){
                        letter_found++;
                    }
                }
            }
            if(letter_found == strlen(secret_word)){
                printf("\t\tCongratulations! You guessed the word and saved the man!\n");
                return 0;
            }else continue;
        }
        letter_or_blank(secret_word, guessed);
    }
    printf("The word is: %s\n", secret_word);
    return 0;
}