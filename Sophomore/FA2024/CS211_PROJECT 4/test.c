/* ------------------------------------------------------------------------------
   Program: Popular Vote Minimizer
   Course: CS 211, Fall 2024
   Author: Adhvetha SP
   ------------------------------------------------------------------------------
   Description : This file contains the tests for the Popular Vote Minimizer program,
   covering vote calculations, data parsing, argument handling, and slow/memoized 
   minimization functions.
   ------------------------------------------------------------------------------
   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"
/* Task 1 - Tests for correct summation of electoral votes accross
multiple test cases, including edge cases like zero and negative votes */
bool test_totalEVs() {
    State aStates[10];
    int res;
    for(int i = 0; i < 10; i++){
        strcpy(aStates[i].name,"");
        strcpy(aStates[i].postalCode,"");
        aStates[i].electoralVotes = 0;
        aStates[i].popularVotes = 0;
    }
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5);
    if (res != 38) {
        printf("  individual state EVs are 5, 8, 12, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return false;
    }
    printf(" Checking totalEVs() for 6 States:\n");
    res = totalEVs(aStates,6);
    if (res != 48) {
        printf("  individual state EVs are 5, 8, 12, 6, 7, 10\n");
        printf("  expected total EVs = 48, actual total EVs = %d\n",res);
        return false;
    }

    aStates[0].electoralVotes = 0;
    aStates[1].electoralVotes = 0;
    res = totalEVs(aStates, 2);
    if(res != 0 ){
        printf("  individual state EVs are 0, 0\n");
        printf("  expected total EVs = 0, actual total EVs = %d\n", res);
        return false;
    }
    
    aStates[0].electoralVotes = 700000;
    aStates[1].electoralVotes = 1000000;
    res = totalEVs(aStates, 2);
    if(res != 1700000 ){
        printf("  individual state EVs are 700000, 1000000\n");
        printf("  expected total EVs = 1700000, actual total EVs = %d\n", res);
        return false;
    }

    res = totalEVs(aStates, 0);
    if(res != 0){
        printf("  No states provided\n");
        printf("expected total EVs = 1700000, actual total EVs = %d\n" , res);
        return false;
    }

    aStates[0].electoralVotes = -4;
    aStates[1].electoralVotes = -7;
    res = totalEVs(aStates, 2);
    if(res != -11 ){
        printf("  individual state EVs are -4, -7\n");
        printf("  expected total EVs = -11, actual total EVs = %d\n", res);
        return false;
    }
    printf("All totalEVs tests passed!/n");
    return true;
}

/*Task 1 - Tests for accurate summation of popular votes 
across different states*/
bool test_totalPVs() {
    State aStates[10];
    int res;
    
    aStates[0].popularVotes = 25000;
    aStates[1].popularVotes = 90000;
    aStates[2].popularVotes = 150000;
    aStates[3].popularVotes = 75000;
    aStates[4].popularVotes = 6000;
    aStates[5].popularVotes = 110000;

    printf(" Checking totalPVs() for 5 States:\n");
    res = totalPVs(aStates,5);
    if (res != 346000) {
        printf("  individual state PVs are 25000, 90000, 150000, 75000, 6000\n");
        printf("  expected total PVs = 346000, actual total PVs = %d\n",res);
        return false;
    }

    printf(" Checking totalPVs() for 6 States:\n");
    res = totalPVs(aStates,6);
    if (res != 456000) {
        printf("  individual state PVs are 25000, 90000, 150000, 75000, 6000, 110000\n");
        printf("  expected total PVs = 456000, actual total PVs = %d\n",res);
        return false;
    }
    return true; 
}

/*Task 2 - Verifies if setSettings() correctly handles valid and invalid
command-line args, including missing years and flags.*/
bool test_setSettings() {
    int year;
    bool fastMode;
    bool quietMode;
    // Test case 1 
    char* invalidArgs[] = {"program", "-v"};
    printf(" Checking setSettings() for invalid argument '-v'....");
    if(setSettings(2, invalidArgs, &year, &fastMode, &quietMode)){
        printf("Test failed: invalid argument did not return false\n");
        return false;
    }
    // Test case 2 
    char* invalidYearArgs[] = {"program", "-y", "2019"};
    printf(" Checking setSettings() for invalid year '-y 2019'....\n");
    if(!setSettings(3, invalidYearArgs, &year, &fastMode, &quietMode)){
        printf("Test failed: expected year = 0 for invalid year\n");
        return false;
    }
    if(year != 0){
        printf("Test failed: expected year = 0 for invalid year\n");
        return false;
    }
    
    // Test case 3
    char* validArgsWithAllFlags[] = {"program", "-y", "2020", "-f", "-q"};
    printf("Checking setSettings() for valid arguments '-y 2020 -f -q....\n");
    if(!setSettings(5, validArgsWithAllFlags, &year, &fastMode, &quietMode )){
        printf("Test failed: valid input returned false\n");
        return false;
    }
    if(year != 2020 || fastMode != true || quietMode != true){
        printf("Test failed: expected year = 2020, fastMod = true, quietMode = true\n");
        return false;
    }
    
    //Test case 4
    char* missingYearArgs[] = {"program", "-y"};
    printf("Checking setSettings() for missing year '-y'....\n");
    if(setSettings(2, missingYearArgs, &year, &fastMode, &quietMode )) {
        printf("Test failed: missing year did not return false as expected\n");
        return false;
       
    } 
    else{
        printf("Test passed: missing year correctly returned false\n");   
    }
    if(year != 0){
        printf("Test failed: expected year = 0 for missing year\n");
        return false;
    }
    printf("Test passed: expected year = 0 for missing year\n");

    //Test case 5
    char* fastAndQuietArgs[] = {"program", "-f", "-q"};
    printf("Checking setSettings() for valid arguments '-f -q'....\n");
    if(!setSettings(3, fastAndQuietArgs, &year, &fastMode, &quietMode )){
        printf("Test failed: expected year = 0, fastMode = true, quietMode = true\n");
        return false;
    }
    printf("All setSettings tests passed!\n");
    return true; 
}

/*Task 3 - ensures inFilename(* generates the correct input 
file paths for different election years*/
bool test_inFilename() {
    char filename[50];
    inFilename(filename, 2020);
    printf("Checking inFilename() for year = 2020....\n");
    if(strcmp(filename, "data/2020.csv") != 0){
        printf("Test failed: expected filename = data/2020.csv, actaul filename = %s\n", filename);
        return false;
    }
    inFilename(filename, 1996);
    printf("Checking inFilename() for year = 1996....\n");
    if(strcmp(filename, "data/1996.csv") != 0){
        printf("Test failed: expected filename = data/1996.csv, actual filename = %s\n", filename);
        return false;
    }
    printf("All inFilename tests passed!\n");
    return true;
}

/*Task 3 - Verifies outFilename() generates the correct output 
file paths for various years*/
bool test_outFilename() {
    char filename[50];
    outFilename(filename, 2020);
    printf("Checking outFilename() for year = 2020....\n");
    if(strcmp(filename, "toWin/2020_win.csv") != 0){
        printf("Test failed: expected filename = toWin/2020_win.csv, actual filename = %s\n", filename);
        return false;
    }
    outFilename(filename, 1996);
    printf("Checking inFilename() for year = 1996....\n");
    if(strcmp(filename, "toWin/1996_win.csv") != 0){
        printf("Test failed: expected filename = toWin/1996_win.csv, actual filename = %s\n", filename);
        return false;
    }
    printf("All outFilename tests passed!\n");
    return true;
}

/*Task 5 - Tests parseLine() for correct parsing of valid state data
and proper handling of invalid or incomplete data*/
bool test_parseLine() {
    char line[] = "California,CA,55,13942399\n";
    char line2[] = "New York,NY,29,7555665\n";
    char lineInvalid[] = "StateInvalid,XX\n";
    char lineMissingFields[] = "IncompleteState,IS,10\n";
    char lineMaxLength[] = "LongStateNameThatFits,LS,5,123456\n";

    State myState;

    //Test case 1 - valid input
    printf("Checking parseLine() for valid input 'California,CA,55,13942399'....\n");
    if(!parseLine(line,&myState)){
        printf("Test failed: parseLine() returned false for valid input.\n");
        return false;
    }
    if(strcmp(myState.name, "California") != 0 || strcmp(myState.postalCode, "CA") != 0 || 
             myState.electoralVotes != 55 || myState.popularVotes != 13942399){
                printf("Test failed: incorrect values for State");
                return false;
    }

    //Test case 2 - valid input
    printf("Checking parseLine() for valid input 'New York,NY,29,7555665'....\n");
    if(!parseLine(line2,&myState)){
        printf("Test failed: parseLine() returned false for valid input.\n");
        return false;
    }
    if(strcmp(myState.name, "New York") != 0 || strcmp(myState.postalCode, "NY") != 0 || 
             myState.electoralVotes != 29 || myState.popularVotes != 7555665){
                printf("Test failed: incorrect values for State");
                return false;
    }

    //Test case 3 - invalid input line
    printf("Checking parseLine() for invalid input 'InvalidState!!,'....\n");
    if(parseLine(lineInvalid,&myState)){
        printf("Test failed: parseLine() returned true for invalid input.\n");
        return false;
    }

   //Test case 4 - invalid input with missing fields
    printf("Checking for invalid input with missing fields....\n");
    if(parseLine(lineMissingFields, &myState)){
        printf("Test failed: parseline() returned true for invalid input.\n");
        return false;
    }

    //Test case 5
    printf("Checking parseLine() for valid input with maximum length  state name.\n");
    if(!parseLine(lineMaxLength, &myState)){
        printf("Test failed: parseLine() returned false for valid input with maximum length state name.\n");
        return false;
    }
    if(strcmp(myState.name,"LongStateNameThatFits") != 0 || strcmp(myState.postalCode, "LS") != 0 
            || myState.electoralVotes != 5 || myState.popularVotes != 123456){
                printf("Test failed: incorrect values for State State with maximum length.\n");
                return false;
            }
    printf("All parseLine tests passed!\n");
    return true;
}

/*Task 6 - Verifies that readElectionData() correctly reads valid files
and handles invalid files, ensuring the right num of states is processed*/
bool test_readElectionData() {
    State aStates[51];
    int numStates;

    //Test case 1 for valid file
    printf("Checking readElectionData for valid file 'data/2020.csv'....\n");
    if(!readElectionData("data/2020.csv", aStates, &numStates)){
        printf("Test failed: could not reach valid file 'data/2020.csv\n");
        return false;
    }

    // to check the number of states read
    if(numStates != 51){
        printf("Test failed: expected 51 states but only got %d states from 'data/2020.csv'\n", numStates);
        return false;
    }
    printf("Number of states read correctly: %d states\n", numStates);
    
    //Test case 2 for invalid file
    printf("Checking readElectionData for invalid file 'data/invalid.csv'....\n");
    if(readElectionData("data/invalid.csv", aStates, &numStates)){
        printf("Test failed: readElectionData() should return false for invalid file\n");
        return false;
    }

    printf("All readElectionData tests passed!\n");
    return true;

}

/*Task 7 - Tests the slow version of minPopVoteToWin() to ensure
it finds the correct minimum popular votes needed to win
the election.*/
bool test_minPVsSlow() {
    State aStates[4];
    /*Test case 1 - standard scenario with 4 states, checking for
     current electoral and popular votes .*/
    strcpy(aStates[0].name, "RedLand");
    strcpy(aStates[0].postalCode, "RD");
    aStates[0].electoralVotes = 12;
    aStates[0].popularVotes = 1200;

    strcpy(aStates[1].name, "BlueTown");
    strcpy(aStates[1].postalCode, "BL");
    aStates[1].electoralVotes = 4;
    aStates[1].popularVotes = 400;

    strcpy(aStates[2].name, "Greenville");
    strcpy(aStates[2].postalCode, "GR");
    aStates[2].electoralVotes = 10;
    aStates[2].popularVotes = 1000;

    strcpy(aStates[3].name, "YellowCity");
    strcpy(aStates[3].postalCode, "YC");
    aStates[3].electoralVotes = 5;
    aStates[3].popularVotes = 500;

    printf("Checking minPopVoteToWin() for 4 States with varying EVs and PVs....\n");
    MinInfo result1 = minPopVoteToWin(aStates, 4);

    if(!result1.sufficientEVs){
        printf("Test failed: insufficient electoral votes.\n");
        return false;
    }
    if(result1.subsetPVs != 802){
        printf("Test failed: expected subsetPVs = 802, actual subsetPVs = %d\n", result1.subsetPVs);
        return false;
    }
    
    /*Test case 2 - validating subset of states, ensuring only two states 
    are selcted and PVs are calculated correctly.*/
    if(result1.szSomeStates != 2){
        printf("Test failed: expected number of states = 2, actual number of states = %d\n", result1.szSomeStates);
        return false;
    }

        
    int calculatedPVs = 0;
    for(int i = 0; i < result1.szSomeStates; i++){
        calculatedPVs += (result1.someStates[i].popularVotes / 2) +1;
    }
    if(calculatedPVs != result1.subsetPVs){
        printf("Test failed: Calculated subsetPVs (%d) does not match result.subsetPVs (%d)\n", calculatedPVs, result1.subsetPVs);
        return false;
    }

    bool bluetownFound = false;
    bool redlandFound = false;
    for(int i = 0; i < result1.szSomeStates; i++){
        if(strcmp(result1.someStates[i].name, "BlueTown") == 0){
        bluetownFound = true;
      }
      if(strcmp(result1.someStates[i].name, "RedLand") == 0){
        redlandFound = true;
      }
    }
    if(!(bluetownFound && redlandFound)){
         printf("Test failed: expected states are BlueTown and RedLand\n");
         return false;
    }
    printf("Test passed: minPopVoteToWin() returned correct results.\n");

    /*Insufficient EVs scenario, ensures proper handling when no states
    can meet the required EVs*/
    State insufficientStates[1];
    int numStates1 = 0;

    printf("Checking minPopVoteToWin() for insufficient electoral votes....\n");
    MinInfo insufficientResult1 = minPopVoteToWin(insufficientStates,numStates1);

    int EVsCount = totalEVs(insufficientStates, numStates1);
    int requiredEVs = (EVsCount / 2) + 1;

    if(EVsCount < requiredEVs){
        if(insufficientResult1.sufficientEVs){
            printf("Test failed: Expected insufficient EVs, but got sufficient EVs.\n");
            return false;
        } 
        else{
            printf("Test passed: Correctly identifies insufficient EVs.\n");
    }
    }
    else{
        printf("Test invalid: Total EVs are sufficient to win.\n");
        return false;
    }

    printf("Validating subset electoral votes for minPopVoteToWin()....\n");
    int calculatedEVs = 0;
    for(int i = 0; i < result1.szSomeStates; i++){
        calculatedEVs += result1.someStates[i].electoralVotes;
    }
    if(calculatedEVs < requiredEVs){
        printf("Test failed: Insufficient electoral votes in the winning subset.\n");
        return false;
    }

    State insufficientStates2[1];
    strcpy(insufficientStates2[0].name, "StateP");
    strcpy(insufficientStates2[0].postalCode, "SP");
    insufficientStates2[0].electoralVotes = 0;
    insufficientStates2[0].popularVotes = 0;

    int numStates2 = 1;

    /*Test case 4  - edge case with one state having 0 EVs.*/
    printf("Checking minPopVoteToWin() for 1 State with 0 electoral votes....\n");
    MinInfo insufficientResult2 = minPopVoteToWin(insufficientStates2, numStates2);

    int EVsCount2 = totalEVs(insufficientStates2, numStates2);
    int requiredEVs2 = (EVsCount2 / 2) + 1;

    if(EVsCount2 < requiredEVs2){
        if(insufficientResult2.sufficientEVs){
        printf("Test failed: Expected insufficient EVs, but got sufficient EVs.\n");
        return false;
    }
    else{
        printf("Test passed: Correctly identifies insufficient total electoral votes.\n");
    }
    }
    else{
        printf("Test invalid: Total EVs are sufficient to win.\n");
        return false;
    }

    printf("All minPopVoteToWin tests passed!\n");
    return true;

}

/*Task 8 - Verifies that minPopVoteToWinFast() using memoization
returns correct results with improved performance.*/
bool test_minPVsFast() {
    State aStates[4];
    /* Test case 1 - standard scenario with 4 states,
    using memoization to verify optimized performance.*/
    strcpy(aStates[0].name, "RedLand");
    strcpy(aStates[0].postalCode, "RD");
    aStates[0].electoralVotes = 12;
    aStates[0].popularVotes = 1200;

    strcpy(aStates[1].name, "BlueTown");
    strcpy(aStates[1].postalCode, "BL");
    aStates[1].electoralVotes = 4;
    aStates[1].popularVotes = 400;

    strcpy(aStates[2].name, "GreenVille");
    strcpy(aStates[2].postalCode, "GR");
    aStates[2].electoralVotes = 10;
    aStates[2].popularVotes = 1000;

    strcpy(aStates[3].name, "YellowCity");
    strcpy(aStates[3].postalCode, "YC");
    aStates[3].electoralVotes = 5;
    aStates[3].popularVotes = 500;

    MinInfo result = minPopVoteToWinFast(aStates, 4);
    // Test Case 1
    printf("Checking minPopVoteToWin() for 4 States with memoization....\n");
    if(!result.sufficientEVs){
        printf("Test failed: insufficient electoral votes.\n");
        return false;
    }
    // Test Case 2
    if(result.subsetPVs != 802){
        printf("Test failed: expected subsetPVs = 802, actual subsetPVs = %d\n", result.subsetPVs);
        return false;
    }
    // Test Case 3 - validates that memoization still returns the same corrrect subset
    if(result.szSomeStates != 2){
        printf("Test failed: expected number of states = 2, actual number of states = %d\n", result.szSomeStates);
        return false;
    }
   bool bluetownFound = false;
   bool redlandFound = false;
   for(int i = 0; i < result.szSomeStates; i++){
    if(strcmp(result.someStates[i].name, "BlueTown") == 0){
        bluetownFound = true;
      }
    if(strcmp(result.someStates[i].name, "RedLand") == 0){
        redlandFound = true;
      }
   }
   if(!(bluetownFound && redlandFound)){
    printf("Test failed: expected states are BlueTown and RedLand\n");
    return false;
    }
    printf("Test passed: minPopVoteToWin() returned correct results.\n");
    return true;
  
    
}

int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}
