/*
    Program 1: Wumpus, version 1 (fixed size array)

    Course: CS 211, Fall 2022, Wed 8am lab
    Systems: Mac using Replit
    Author: Jennifer Le, jle34
*/
#include <stdbool.h> // for bool variables
#include <stdio.h>
#include <stdlib.h> // for srand

//--------------------------------------------------------------------------------
void displayCave() {
  printf("       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}
//--------------------------------------------------------------------------------
void displayInstructions() {
  printf("Hunt the Wumpus:                                             \n"
         "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
         "room has 3 tunnels leading to other rooms.                   \n"
         "                                                             \n"
         "Hazards:                                                     \n"
         "1. Two rooms have bottomless pits in them.  If you go there you fall "
         "and die.   \n"
         "2. The Wumpus is not bothered by the pits, as he has sucker feet. "
         "Usually he is \n"
         "   asleep. He will wake up if you enter his room. When you move into "
         "the Wumpus'\n"
         "   room, then he wakes and moves if he is in an odd-numbered room, "
         "but stays    \n"
         "   still otherwise.  After that, if he is in your room, he snaps "
         "your neck and  \n"
         "   you die!                                                          "
         "           \n"
         "                                                                     "
         "           \n"
         "Moves:                                                               "
         "           \n"
         "On each move you can do the following, where input can be upper or "
         "lower-case:  \n"
         "1. Move into an adjacent room.  To move enter 'M' followed by a "
         "space and       \n"
         "   then a room number.                                               "
         "           \n"
         "2. Enter 'R' to reset the person and hazard locations, useful for "
         "testing.      \n"
         "3. Enter 'C' to cheat and display current board positions.           "
         "           \n"
         "4. Enter 'D' to display this set of instructions.                    "
         "           \n"
         "5. Enter 'P' to print the maze room layout.                          "
         "           \n"
         "6. Enter 'G' to guess which room Wumpus is in, to win or lose the game! \n"
         "7. Enter 'X' to exit the game.                                       "
         "           \n"
         "                                                                     "
         "           \n"
         "Good luck!                                                           "
         "           \n"
         " \n\n");
} // end displayInstructions()
//--------------------------------------------------------------------------------
// assign different rooms at random to person, wumpus and pits using srand()
void assignRooms(int *pit1, int *pit2, int *wumpusRoom, int *currentRoom) {

    // seed random number generator
    srand(1);
    // % 20 can only get numbers 1 through 19 so + 1 is needed
    *pit1 = rand() % 20 + 1;
    *pit2 = rand() % 20 + 1;
    
    // while loops below make sure rooms are all differnt
    while (*pit2 == *pit1) {
        *pit2 = rand() % 20 + 1;
    }
    *wumpusRoom = rand() % 20 + 1;
    while (*wumpusRoom == *pit2 || *wumpusRoom == *pit1) {
        *wumpusRoom = rand() % 20 + 1;
    }
    *currentRoom = rand() % 20 + 1;
    while (*currentRoom == *wumpusRoom || *currentRoom == *pit2 ||
           *currentRoom == *pit1) {
        *currentRoom = rand() % 20 + 1;
    }
}
//--------------------------------------------------------------------------------
// prints message that is outputted before every move is made, prints hazzards
// in adjacent rooms, and prompts user for input
void enterMove(int currentRoom, int wumpusRoom, int pit1, int pit2,
               int adjacentRooms[21][3], char *move, int moveCount){
    
    printf("You are in room %d. ", currentRoom);
    int i;
    // checks for hazzards in adjacent room
    for (i = 0; i < 3; i++) {
        if (adjacentRooms[currentRoom][i] == wumpusRoom) {
            printf("You smell a stench. ");
        }
        if (adjacentRooms[currentRoom][i] == pit1 ||
            adjacentRooms[currentRoom][i] == pit2) {
            printf("You feel a draft. ");
        }
    }
    printf("\n\n");
    printf("%d. Enter your move (or 'D' for directions): ", moveCount);
    scanf(" %c", *&move); // incremets while loop in main
}
//--------------------------------------------------------------------------------
// runs when user chooses to move rooms, prints different messages depending
// on which room is choosen and where the obstacles are.
void optionM(int *currentRoom, int *wumpusRoom, int pit1, int pit2,
             int adjacentRooms[21][3], int *moveCount, bool *die) {
    
    int nextRoom;
    scanf(" %d", &nextRoom);
    // true if next room is not adjacent to current room
    bool roomError = true;  // true by default
    int i;
    // checks to see if user moves to an adjacent room
    for (i = 0; i < 3; i++) {
        if (adjacentRooms[*currentRoom][i] == nextRoom) {
            roomError = false;
        }
    }
    if (roomError) {
        printf("Invalid move.  Please retry. \n");
        return;   // exits function, enterMove() at end of
    }               // while loop in main lets user try again
    else {
        *currentRoom = nextRoom;
    }
    // checks for hazzards in current room
    if (*currentRoom == pit1 || *currentRoom == pit2) {
        printf("Aaaaaaaaahhhhhh....\n    You fall into a pit and die.\n");
        *die = true;  // triggers while loop to break and game to end
        return;
    }
    // if wumpus is in odd room
    if (*currentRoom == *wumpusRoom && *wumpusRoom % 2 == 1) {
        printf("You hear a slithering sound, as the Wumpus slips away. "
               "\nWhew, that was close! \n");
        // wumpus moves to adjacent room with the lowest value
        *wumpusRoom = adjacentRooms[*currentRoom][0];
    }
    // if wumpus is in even room
    if (*currentRoom == *wumpusRoom && *wumpusRoom % 2 == 0) {
        printf("You briefly feel a slimy tentacled arm as your neck is "
               "snapped. \nIt is over.\n");
        *die = true;
        return;
    }
    (*moveCount)++;
}
//--------------------------------------------------------------------------------
// runs when user wants to guesss where the wumpus is. Win/lose message
// is printed out depending on user's guess.
void optionG(int wumpusRoom){
    printf("Enter room (1..20) you think Wumpus is in: ");
    int guessRoom;
    scanf("%d", &guessRoom);
    if (guessRoom == wumpusRoom) {  // if user guesses correctly
        printf("You won!\n");
    }
    if (guessRoom != wumpusRoom) {  // if user guesses incorrectly
        printf("You lost!\n");
    }
}
//--------------------------------------------------------------------------------
int main(void) {
    
    int pit1, pit2, wumpusRoom, currentRoom;    // person is in current room
    assignRooms(&pit1, &pit2, &wumpusRoom, &currentRoom);

    // elements at index j are the adjacent rooms of room i for adjacentRoom[i][j]
    int adjacentRooms[21][3] = {
        {0, 0, 0},
        {2, 5, 8},     {1, 3, 10},   {2, 4, 12},    {3, 5, 14},    {1, 4, 6},
        {5, 7, 15},    {6, 8, 17},   {1, 7, 9},     {8, 10, 18},   {2, 9, 11},
        {10, 12, 19},  {3, 11, 13},  {12, 14, 20},  {4, 13, 15},   {6, 14, 16},
        {15, 17, 20},  {18, 16, 7},  {9, 17, 19},   {11, 18, 20},  {13, 16, 19}
    };
    char move;          // can be lowercase or uppercase M, R, C, D, P, G, X
    int nextRoom;       // room user wants to move to for option m
    int moveCount = 1;
    bool die = false;   // tracks when user dies and game should end

    enterMove(currentRoom, wumpusRoom, pit1, pit2, adjacentRooms, &move, moveCount);
//--------------------------------------------------------------------------------
    while (move != 'x' && move != 'X') {
        // when user wants to move rooms
        if (move == 'm' || move == 'M') {
            optionM(&currentRoom, &wumpusRoom, pit1, pit2,
                    adjacentRooms, &moveCount, &die);
            if (die) { break; }
        }
        // when user wants reset rooms and pick the rooms themselves
        if (move == 'r' || move == 'R') {
            printf("Enter the room locations (1..20) for player, "
                   "wumpus, pit1, and pit2: \n\n");
            scanf("%d %d %d %d", &currentRoom, &wumpusRoom, &pit1, &pit2);
        }
        // when user wants to cheat and know which room the obstacles are in
        if (move == 'c' || move == 'C') {
            printf("Cheating! Game elements are in the following rooms: \n"
                   "Player Wumpus Pit1 Pit2  \n%4d %7d %5d %5d \n\n",
                   currentRoom, wumpusRoom, pit1, pit2);
        }
        // when user wants to display cave and instructions
        if (move == 'd' || move == 'D') {
            printf("\n");
            displayCave();
            displayInstructions();
        }
        // when user only wants to display cave
        if (move == 'p' || move == 'P') {
            printf("\n");
            displayCave();
        }
        // when user wants to guess where the wumpus is
        if (move == 'g' || move == 'G') {
            optionG(wumpusRoom);
            break;
        }
        // increments while loop
        enterMove(currentRoom, wumpusRoom, pit1, pit2, adjacentRooms, &move, moveCount);
    }
    printf("\nExiting Program ...\n");
    return 0;
}
