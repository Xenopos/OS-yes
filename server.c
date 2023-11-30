#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 177013
#define MAX_MESSAGE_SIZE 1024

typedef struct {
    char name[20];
    int currentHealth;
    int maxHealth;
} Player;

typedef struct {
    char actionName[20];
    int actioninput;
    int heal;
} Action;

typedef struct {
    Player XiyaPlayer;
    Player ShizukaPlayer;
    Action Xiyactions[5];
    Action Shizukaactions[5];
    int choosing;
} GameState;

typedef struct {
    int isXiyaDead;           
    int isXiyaTurn;          
    int isShizukaDead;      
    int isXiyaDisconnected;  
    int isPreparationPhase;  
    int isExecutionPhase;   
} XiyaFlags;

void on_execution_phase(GameState gameState)
{   
    printf("fuck you ");
    for (int compare = 0; compare < 5; ++compare) {
        int xiyaAction = gameState.Xiyactions[compare].actioninput;
        int shizukaAction = gameState.Shizukaactions[compare].actioninput;

        if (xiyaAction == 1 && shizukaAction == 1)
            printf("Xiya initiated attack and Shizuka initiated attack\n");
        else if (xiyaAction == 2 && shizukaAction == 1)
            printf("Xiya initiated heal and Shizuka initiated attack\n");
        else if (xiyaAction == 3 && shizukaAction == 1)
            printf("Xiya initiated defend and Shizuka initiated attack\n");
        else if (xiyaAction == 4 && shizukaAction == 1)
            printf("Xiya initiated counter and Shizuka initiated attack\n");
        else if (xiyaAction == 1 && shizukaAction == 2)
            printf("Xiya initiated attack and Shizuka initiated heal\n");
        else if (xiyaAction == 2 && shizukaAction == 2)
            printf("Xiya initiated heal and Shizuka initiated heal\n");
        else if (xiyaAction == 3 && shizukaAction == 2)
            printf("Xiya initiated defend and Shizuka initiated heal\n");
        else if (xiyaAction == 4 && shizukaAction == 2)
            printf("Xiya initiated counter and Shizuka initiated heal\n");
        else if (xiyaAction == 1 && shizukaAction == 3)
            printf("Xiya initiated attack and Shizuka initiated defend\n");
        else if (xiyaAction == 2 && shizukaAction == 3)
            printf("Xiya initiated heal and Shizuka initiated defend\n");
        else if (xiyaAction == 3 && shizukaAction == 3)
            printf("Xiya initiated defend and Shizuka initiated defend\n");
        else if (xiyaAction == 4 && shizukaAction == 3)
            printf("Xiya initiated counter and Shizuka initiated defend\n");
        else if (xiyaAction == 1 && shizukaAction == 4)
            printf("Xiya initiated attack and Shizuka initiated counter\n");
        else if (xiyaAction == 2 && shizukaAction == 4)
            printf("Xiya initiated heal and Shizuka initiated counter\n");
        else if (xiyaAction == 3 && shizukaAction == 4)
            printf("Xiya initiated defend and Shizuka initiated counter\n");
        else if (xiyaAction == 4 && shizukaAction == 4)
            printf("Xiya initiated counter and Shizuka initiated counter\n");
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void on_preparation_phase() {
    XiyaFlags xiyaFlags;
    GameState gameState;
    int actionsInputted = 0;
    int choosingAction = 0;

    while (xiyaFlags.isPreparationPhase) {
        int hasInvalidActionInput = 0;

         printf("1 = Attack\n"
                "2 = Heal\n"
                "3 = Defend\n"
                "4 = Counter\n");

        for (choosingAction; choosingAction < 4; choosingAction++) {
            printf("Enter desired action for slot %d (enter 0 to clear): ", choosingAction + 1);
            if (scanf("%d", &gameState.Xiyactions[choosingAction].actioninput) != 1) {
                hasInvalidActionInput = 1;
                printf("Invalid input. Please enter a number.\n");
                clear_input_buffer();
                break;
            }

            if (gameState.Xiyactions[choosingAction].actioninput == 0) {
                printf("Array cleared.\n");
                hasInvalidActionInput = 1;
                clear_input_buffer();
                break;
            }

            if (gameState.Xiyactions[choosingAction].actioninput < 1 || gameState.Xiyactions[choosingAction].actioninput > 4) {
                hasInvalidActionInput = 1;
                printf("Invalid action input. Please enter numbers between 1 and 4 or 0 to clear.\n");
                clear_input_buffer();
                choosingAction = -1;
                break;
            }

            actionsInputted++;
        }

        if (hasInvalidActionInput) {
            actionsInputted = 0;
            choosingAction = 0;
            continue;
        }

        if (actionsInputted == 4) {
            printf("All slots are filled.\n");

            for (int count = 0; count < 4; count++) {
                int actionInput = gameState.Xiyactions[count].actioninput;
                printf("Slot %d: %d ", count + 1, actionInput);

                switch (actionInput) {
                    case 1:
                        printf("Action: Attack\n");
                        break;
                    case 2:
                        printf("Action: Heal\n");
                        break;
                    case 3:
                        printf("Action: Defend\n");
                        break;
                    case 4:
                        printf("Action: Counter\n");
                        break;
                    default:
                        printf("Invalid action input.\n");
                        break;
                }
            }

            printf("Proceed to Execution Phase? (Enter 1 to proceed, 0 to reset): ");
            int proceedInput;
            if (scanf("%d", &proceedInput) == 1) {
                if (proceedInput == 1) {
                    xiyaFlags.isExecutionPhase = 1;
                    break; 
                } else if (proceedInput == 0) {
                    actionsInputted = 0;
                    choosingAction = 0;
                    clear_input_buffer();
                } else {
                    printf("Invalid input. Please enter 1 to proceed or 0 to reset.\n");
                    clear_input_buffer();
                }
            } else {
                printf("Invalid input. Please enter a number.\n");
                clear_input_buffer();
            }
        }
    }
}


void ShowIntro()
{
    printf("Mentee Shizuka is not ready...\n");
    printf("Mentee Shizuka is ready...\n");
}


int main(int argc, char const *argv[])
{
    ShowIntro();

    XiyaFlags xiyaFlags;  
    xiyaFlags.isPreparationPhase = 1;  

    while (xiyaFlags.isExecutionPhase == 1)
    {
        printf("test");
    }

    if (xiyaFlags.isPreparationPhase == 1) {
        on_preparation_phase();
    }


    return 0;
}
