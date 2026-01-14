/* ------------------------------------------------------------------------------
   Program: Popular Vote Minimizer
   Course: CS 211, Fall 2024
   Author: Adhvetha SP
   ------------------------------------------------------------------------------
   Description : This program determines the minimum number of popular votes 
   required to win the U.S. presidency based on historical election data,
   utilizing recursive algorithms and memoization for efficiency.
   ------------------------------------------------------------------------------
   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

// Task 1 - Calculates and returns the total number of electoral votes from a given array of states 
int totalEVs(State* states, int szStates) {
   int total = 0;
   for(int i = 0; i < szStates; i++){
    total += states[i].electoralVotes;
   }
    return total; 
}

// Task 1 - Calculates and returns the total number of popular votes from a given array of states 
int totalPVs(State* states, int szStates) {
    int total = 0;
   for(int i = 0; i < szStates; i++){
    total += states[i].popularVotes;
   }
    return total; 
    
}

//Task 2 - Parses the command_line arguments to set the election year, fast mode, and quiet mode.
bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    *year = 0; 
    *quietMode = false; 
    *fastMode = false; 
    // Loops through the command-line args and sets the corresponding settings
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-y") == 0){
            if((i + 1) < argc){
                char* nextArg = argv[i + 1];
                if(strcmp(nextArg,"-f") == 0 || strcmp(nextArg,"-q") == 0 || strcmp(nextArg, "-y") == 0){
                    *year = 0;
                }
                else{
                    int inpYear = atoi(argv[i+1]);
                    if(inpYear >= 1828 && inpYear <= 2020 && inpYear % 4 == 0 ){
                        *year = inpYear;
                }
                    else{
                        *year = 0;
                }
                i++;
            }
        }
            else{
                return false;
            }
        }
        else if(strcmp(argv[i], "-f") == 0){
            *fastMode = true;
        }
        else if(strcmp(argv[i], "-q") == 0){
            *quietMode = true;
            }
        else{
             return false;
            }
        }
    return true; 
}

// Task 3 - Generates the input filename for the election data based on the given year.
void inFilename(char* filename, int year) {
    sprintf(filename, "data/%d.csv", year);
}

//Task 3 - Generates the output filename for storing the results based on the given year.
void outFilename(char* filename, int year) {
    sprintf(filename, "toWin/%d_win.csv", year);
    return;
}

// Task 5 - Parses a single line of election data and populates the State struct with the parsed data
bool parseLine(char* line, State* myState) {
    char* parsedToken;

    parsedToken = strtok(line, ",");
    if(parsedToken == NULL){
        return false;
    }
    strncpy(myState ->name, parsedToken, 49);
    myState->name[49] = '\0';

    parsedToken = strtok(NULL,",");
    if(parsedToken == NULL){
        return false;
    }
    
    strncpy(myState -> postalCode, parsedToken, 2);
    myState->postalCode[2] = '\0';

    parsedToken = strtok(NULL,",");
    if(parsedToken == NULL){
        return false;
    }
    myState->electoralVotes = atoi(parsedToken);

    parsedToken = strtok(NULL,",");
    if(parsedToken == NULL){
        return false;
    }
    myState->popularVotes = atoi(parsedToken);

    return true; 
}
//Task 6 - Reads election data from a file and populates an array of State structs with the data
bool readElectionData(char* filename, State* allStates, int* nStates) {
    FILE* outFile = fopen(filename, "r");
    if(outFile == NULL){
        return false;
    }
    *nStates = 0; 
    char line[256];

    // Reads each line from the file
    while(fgets(line, sizeof(line), outFile)){
        size_t length = strlen(line);
        if(length > 0 && line[length - 1] == '\n'){
            line[length - 1] = '\0';
        }
        if(parseLine(line, &allStates[*nStates])){
            (*nStates)++;
        }
        else{
            printf("Unable to parse the line.");
        }
    }
    fclose(outFile);
    return true; 
}
//Task 7 - Recursively finds the minimum popular vote subset of states that satisfies the required electoral votes.
MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    // Base case 1, return the current result if we have enough EVs
    if(EVs <= 0){
        MinInfo result;
        result.sufficientEVs = true;
        result.subsetPVs = 0; 
        result.szSomeStates = 0;
        return result;
    }
    // Base case 2 return failure (i.e insufficient EVs) if we have gone through all the states and didn't reach the required EVs
    if(start >= szStates){
        MinInfo result;
        result.sufficientEVs = false;
        result.subsetPVs = 0;
        result.szSomeStates = 0;
        return result;
    }

    // Recursive step 1 - checks the remaining states excluding the current state
    MinInfo excludeCurrentState = minPopVoteAtLeast(states, szStates, start + 1, EVs);

    //Recursive step 2 - checks all states including the current state
    MinInfo includeCurrentState = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes);
    if(includeCurrentState.sufficientEVs){
        int votesToWin = (states[start].popularVotes / 2) + 1;
        includeCurrentState.subsetPVs += votesToWin;
        includeCurrentState.someStates[ includeCurrentState.szSomeStates] = states[start];
        includeCurrentState.szSomeStates++;
    }

    if(includeCurrentState.sufficientEVs && (!excludeCurrentState.sufficientEVs || includeCurrentState.subsetPVs < excludeCurrentState.subsetPVs)){
        return includeCurrentState;
    }
    else{
        return excludeCurrentState;
    }
}
// Task 7 - Wrapper function that initiates the process of finding the minimum popular vote subset of states to win.
MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}

// Task 8 - Optimized version of the minPopVoteAtLeast function that uses memoization to speed up the calculations.
MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    // Base case 1 -  return result if sufficient electoral votes are achieved
        if(EVs <= 0){
        MinInfo result;
        result.sufficientEVs = true;
        result.subsetPVs = 0; 
        result.szSomeStates = 0;
        return result;
    }
    // Base case 2 return result if we have gone through all the states
    if(start >= szStates){
        MinInfo result;
        result.sufficientEVs = false;
        result.subsetPVs = 0;
        result.szSomeStates = 0;
        return result;
    }
    //Checks if the result is already memoized
    if(memo[start][EVs].subsetPVs != -1){
        return memo[start][EVs];
    }

    // Recursive step 1 - exclude current state
    MinInfo excludeCurrentState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo);

    //Recursive step 2 - cinclude current state
    MinInfo includeCurrentState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo);

    if(includeCurrentState.sufficientEVs){
        int votesToWin = (states[start].popularVotes / 2) + 1;
        includeCurrentState.subsetPVs += votesToWin;
        includeCurrentState.someStates[includeCurrentState.szSomeStates] = states[start];
        includeCurrentState.szSomeStates++;

    }
    // to memoize the result
    MinInfo result;
    if(includeCurrentState.sufficientEVs && (!excludeCurrentState.sufficientEVs || includeCurrentState.subsetPVs < excludeCurrentState.subsetPVs)){
        result = includeCurrentState;
    }
    else{
        result = excludeCurrentState;
    }
    memo[start][EVs] = result;
    return result;
}

// Task 8 - Wrapper function that initiates the memoized version of finding the minimum popular vote subset of states to win the election.
MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*));
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);

    for(int i = 0; i <= szStates;++i ){
        free(memo[i]);
    }
    free(memo);

    return res;
}

// Function for sorting states by name for Task 9 - sorts the array of State structs by state name in alpabetical order
void sortStates(State* states, int num){
    for(int i = 0; i < num - 1; i++){
        int minIndex = i;
        for(int j = i + 1; j < num; j++){
            if(strcmp(states[j].name, states[minIndex].name) < 0){
                minIndex = j;
            }
        }
        if(minIndex != i){
            State temp = states[i];
            states[i] = states[minIndex];
            states[minIndex] = temp; 
        }
    }
}

// Task 9 - Writes the election results to a file.
bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    sortStates(toWin.someStates, toWin.szSomeStates);
    FILE* outFile = fopen(filenameW, "w");
    if(outFile == NULL){
        return false;
    }
    //Writes the total EVs, PVs and the result to the file
    fprintf(outFile,"%d,%d,%d,%d\n", totEVs, totPVs,wonEVs,toWin.subsetPVs);
    for(int i = 0; i < toWin.szSomeStates; i++){
        int votesToWin = (toWin.someStates[i].popularVotes/2) + 1;
        fprintf(outFile, "%s,%s,%d,%d\n",toWin.someStates[i].name,toWin.someStates[i].postalCode,toWin.someStates[i].electoralVotes,votesToWin);
    }
    fclose(outFile);
    return true;
}
