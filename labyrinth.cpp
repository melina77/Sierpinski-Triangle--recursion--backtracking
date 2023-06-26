/* File Synopsis:
 * This file contains two functions which validate a path through a maze and get the next move in a linked
 * list path through a maze. In order to successfully get through a maze, all items in the list need to be
 * found within the maze. This file also contains a custom maze and my solution to that maze.
 */
#include "labyrinth.h"
#include "demo/MazeGenerator.h"
#include "testing/SimpleTest.h"
using namespace std;

const string kYourName = "Melina Eftekhari";
const string kPathOutOfNormalMaze = "ESENEWSSESNWSWWNN";

/**
 * Given a location in a maze, returns whether the given sequence of
 * steps will let you escape the maze.
 *
 * To escape the maze, you need to collect all items in the `needs` set.
 * You can only take steps in the four cardinal directions,
 * and you can't move in directions that don't exist in the maze.
 */
bool isPathToFreedom(MazeCell* start, string moves, Set<string> needs) {
    MazeCell * cur = start;
    if(needs.contains(cur->contents)){//if the path starts on an item in the list, remove that item from the list
        needs.remove(cur->contents);
}
    while(!needs.isEmpty()){
        if(moves == ""){
            return false;//the entire path has been followed and all items have not been found
        }

        getNextMove(cur, moves);
        if(cur == nullptr){
            return false;//the path contains an invalid move
        }

        string content = cur->contents;
        if(content != ""){//if the move contains an item, remove it from the list
            if(needs.contains(content)){
                needs.remove(content);
            }
        }
    }
    return true;
}


/* Function Synopsis:
 * The getNextMove function finds the next move in the maze given a string of cardinal directions.
 * This is a helper function for isPathToFreedom which takes in by reference the MazeCell of the current
 * cell and the string of moves to escape the maze. Nothing is returned since the parameters are passed
 * in by reference and edited.
 */
void getNextMove(MazeCell*& cur, string& moves){
    if(moves[0] == 'N'){
        cur = cur->north;
    }
    else if(moves[0] == 'E'){
        cur = cur->east;
    }
    else if(moves[0] == 'S'){
        cur = cur->south;
    }
    else if(moves[0] == 'W'){
        cur = cur->west;
    }
    else{
        error("Contains moves other than the four cardinal directions.");
    }
    moves = moves.substr(1,moves.size()-1);
}


/* * * * * * Test Cases Below This Point * * * * * */

PROVIDED_TEST("Check paths in the sample from writeup") {
    Set<string> allThree = {"Spellbook", "Potion", "Wand"};
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN", allThree));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES", allThree));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES", allThree));

    /* This path works to pick up just potion */
    EXPECT(isPathToFreedom(maze[2][2], "ESNW", {"Potion"}));

    /* This path doesn't work, since doesn't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW", allThree));

    /* This path doesn't work, cannot walk through walls. */
    EXPECT(!isPathToFreedom(maze[2][2], "NNWWSSSEEE", allThree));
}

PROVIDED_TEST("Works when start on an item") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "E", {"Potion"}));
    EXPECT(isPathToFreedom(maze[0][1], "W", {"Potion", "Spellbook"}));
}

PROVIDED_TEST("Reports errors if given illegal characters") {
    auto maze = toMaze({"P-S-W"});

    EXPECT_ERROR(isPathToFreedom(maze[0][0], "Q", {"Wand"}));
    EXPECT_ERROR(isPathToFreedom(maze[0][0], "Ee", {"Wand"}));
}

PROVIDED_TEST("Escape from your personal labyrinth!") {
    Set<string> allThree = {"Spellbook", "Potion", "Wand"};
    EXPECT(kYourName != "TODO");
    MazeCell* startLocation = mazeFor(kYourName);

   EXPECT(kPathOutOfNormalMaze != "TODO");
   EXPECT(isPathToFreedom(startLocation, kPathOutOfNormalMaze, allThree));
}

