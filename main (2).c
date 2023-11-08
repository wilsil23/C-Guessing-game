// William Diamond - CSE 240
// 1224931045

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

float GetRandomNumber();
void PlayGuessingGame();
int guessCount=0;
int guesserNumber=0;
int numGuessers=0;

//struct for keeping track of names and number of guesses
struct guesser
{
    char name[30];
    int guesses;
};

struct guesser g[6];

//main function for game
int main()
{
    Read();
    struct guesser g1;
    char input[30];
    char name[30];
    printf("Welcome! Press q to quit or any key to continue:");
    scanf("%s", input);
    if(strcmp(input,"q")==0)
    {
        printf("\nBye Bye!");
    }
    else
    {
        printf("Please enter your name to start:");
        scanf("%s", name);
        strcpy(g1.name, name);
        strcpy(g[guesserNumber].name, name);
    }
    while(strcmp(input,"q")!=0){
        PlayGuessingGame(g1);
        printf("\nPress q to quit or any key to continue:");
        scanf("%s", input);
        if(strcmp(input,"q")==0){
            Write();
            printf("Bye Bye!");
        }
        else{
            printf("Please enter your name to start:");
            scanf("%s", name);
            strcpy(g[guesserNumber].name, name);
        }
    }
}
// Prompts user guess and stores it
int GetGuess()
{
    int guess;
    scanf("%d", &guess);
    guessCount++;
    return guess;
}
//Gets a random number from 10 to 100
float GetRandomNumber()
{
    float randomNumber;
    time_t t;
    srand((unsigned) time(&t));
    randomNumber = (rand()+10)%100;
    return randomNumber;
}
//asks for user to guess square root reprompts if guess too low or too high
void PlayGuessingGame(struct guesser g1)
{
    guessCount=0;
    float randomNumber=GetRandomNumber();
    bool trueFalse=false;
    printf("%f is the square root of what number?", sqrt(randomNumber));
    int guess=GetGuess();
    while(trueFalse != true){
        if(guess>randomNumber){
            printf("too high, guess again:");
            guess=GetGuess();
        }
        else if(guess<randomNumber){
            printf("too low, try again:");
            guess=GetGuess();
            
        }
        else if(guess==randomNumber){
            printf("you got it baby!");
            printf("\nYou made %d guesses.", guessCount);
            g[guesserNumber].guesses=guessCount;
            guesserNumber++;
            numGuessers++;
            if(numGuessers>5){
                numGuessers=5;
                guesserNumber=findLastLeader();
            }
            Update();
            trueFalse=true;
        }
        
    }
}

//prints out values of the leaders
void printLeaders(){
    printf("\nHere are the current leaders:");
    for(int i=0;i<numGuessers;i++){
        printf("\n%s made %d guesses",g[i].name,g[i].guesses);
    }
}



//finds the highest guesses leader and replace if currentguesses is lower
int findLastLeader(){
    int max=0;
    int index=0;
    for(int i=0;i<numGuessers;i++){
        if(g[i].guesses > max){
            max=g[i].guesses;
            index=i;
        }
    }
    printf("max: %d",max);
    printf("guessCount: %d",guessCount);
    if(guessCount >= max){
        return 6;
    }
    g[index].guesses=guessCount;
    strcpy(g[index].name, g[guesserNumber-1].name);
    return 6;
}

//Reads file as long as there is a string and integer on each line and there is less than 6 lines
void Read() {
    FILE* file = fopen("leaders.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "%s %d", g[i].name, &g[i].guesses) == 2 && i < 6) {
        i++;
    }

    fclose(file);
}

//writes to file
void Write() {
    FILE* file = fopen("leaders.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numGuessers; i++) {
        fprintf(file, "%s %d\n", g[i].name, g[i].guesses);
    }

    fclose(file);
}

//updates file
void Update() {
    printLeaders();
}


