/* ------------------------------------------------------------------------------
   Program: Bit Big Bug Tug - Word Ladder Builder
   Course: CS 211, Fall 2024
   Author: Adhvetha SP
   ------------------------------------------------------------------------------
   Description : This program creates word ladders between two words by changing
   one letter at a time. It dynamically manages memory and uses a dictionary
   file to ensure each word is valid.
   ------------------------------------------------------------------------------
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Task I - The function compares two words and counts the number of 
           character differences.*/
int strCmpCnt(char* word1, char* word2) {
    int count = 0;
    int lengthOfWord1 = strlen(word1);
    int lengthOfWord2 = strlen(word2);

    int minLength = 0;
    if(lengthOfWord1 < lengthOfWord2){
        minLength = lengthOfWord1;
    }
    else{
        minLength = lengthOfWord2;
    }
    // to count differing char
    for(int i = 0; i < minLength; i++){
        if(word1[i] != word2[i]){
            count++;
        }
    }
    count += abs(lengthOfWord1 - lengthOfWord2);
    
    return count;
}

/*Task II - The function compares two words and returns the index of the first 
            differing character. */
int strCmpInd(char* word1, char* word2) {
    int lengthOfWord1 = strlen(word1);
    int lengthOfWord2 = strlen(word2);

    int minLength = 0;
    if(lengthOfWord1 < lengthOfWord2){
        minLength = lengthOfWord1;
    }
    else{
        minLength = lengthOfWord2;
    }
    // to find the index of the first differing character
    for(int i = 0; i < minLength; i++){
        if(word1[i] != word2[i]){
            return i;
        }
    }

    if(lengthOfWord1 != lengthOfWord2){
        return minLength;
    }
    
    return -1; 
}
 
/*Task III - The function appends a new word to a dynamic array of C-strings,
             reallocating memory if needed. */
void appendWord(char*** pWords, int* pNumWords, int* pMaxWords, char* newWord) {
    if(*pNumWords >= *pMaxWords){
       
        *pMaxWords *= 2;
        *pWords = (char**)realloc(*pWords, *pMaxWords * sizeof(char*));
        
        if(*pWords == NULL){
            printf("Error reallocating.\n");
            exit(1);
        }
    }
    // to allocate space for the new word and copy into array
    (*pWords)[*pNumWords] = (char*)malloc((strlen(newWord) + 1) * sizeof(char));
    if((*pWords)[*pNumWords] == NULL){
        printf("Error reallocating.\n");
       exit(1);
    }
    strcpy((*pWords)[*pNumWords], newWord);
    (*pNumWords)++;
}

/*Task IV - The function reads words from a dictionary file and adds words of the 
            specified length to a dynamic array. */
void buildWordArray(char*** pWords, int* pNumWords, int* pMaxWords, char* dictFile, int wordLength){
    FILE* dictionary = fopen(dictFile, "r");

    if(dictionary == NULL){
        printf("Error opening the Dictionary file: %s\n", dictFile);
        exit(1);
    }
    char* tempWord = NULL;
    size_t len = 0;
    // to read words and append the valid ones to the array
    while(getline(&tempWord, &len, dictionary) != -1){
        if(tempWord[strlen(tempWord) - 1] == '\n'){
            tempWord[strlen(tempWord) - 1] = '\0';
        }
        if(strlen(tempWord) == wordLength){
            appendWord(pWords, pNumWords, pMaxWords, tempWord);
        }
    }
    free(tempWord);
    fclose(dictionary);

    printf("The dictionary contains %d words of length %d.\n", *pNumWords, wordLength);
    printf("Max size of the dynamic words array is %d.\n", *pMaxWords);

}

/*Task V - The function performs a linear search on the word list array to find 
           the index of the given word.*/
int linSearchForWord(char** words, int numWords, char* findWord) { 
    for(int i = 0; i < numWords; i++){
        int j = 0;
        while(words[i][j] != '\0' && findWord[j] != '\0' && words[i][j] == findWord[j]){
            j++;
        }
        if(words[i][j] == '\0' && findWord[j] == '\0'){
            return i;
        }
    } 
    return -99; 
}

/*Task VI - The function verifies that a word meets all criteria to be added to the ladder. */
bool checkForValidWord(char** words, int numWords, int wordLen, char** ladder, int ladderHeight, char* aWord) {
    if(strcmp(aWord, "DONE") == 0){
        printf("Stopping with an incomplete word ladder...\n");
        return true;
    }
    if(strlen(aWord) != wordLen){
        printf("Entered word does NOT have the correct length. Try again...\n");
        return false;
    }
    if(linSearchForWord(words, numWords, aWord) == -99){
        printf("Entered word NOT in dictionary. Try again...\n");
        return false;
    }
    if(strCmpCnt(ladder[ladderHeight - 1], aWord) != 1){
        printf("Entered word is NOT a one-character change from the previous word. Try again...\n");
        return false;
    }
    printf("Entered word is valid and will be added to the word ladder.\n");
    return true;
}

/*Task VII - The function checks if the ladder has reached the final word.*/
bool isLadderComplete(char** ladderWords, int height, char* finalWord) {
    char* lastWord = ladderWords[height - 1];
    
    for(int i = 0; lastWord[i] != '\0' && finalWord[i] != '\0'; i++){
        if(lastWord[i] != finalWord[i]){
            return false;
        }
    }
    
    if(strlen(lastWord) == strlen(finalWord)){
        return true;
    }
    
    return false; 
}

/*Task IX - The function displays an incomplete ladder, indicating an ongoing ladder
            building process.*/
void displayIncompleteLadder(char** ladderWords, int height) {
    printf("  ...\n  ...\n  ...\n");
    for(int i = height - 1 ; i >= 0; i--){
        printf("  %s\n", ladderWords[i]);
        }
}

/*Task X - The function displays a complete word ladder with "^" for changed letters. */
void displayCompleteLadder(char** ladderWords, int height) {
    for(int i = height - 1; i >= 0; i--){
        printf("  %s\n", ladderWords[i]);
        if(i > 0){
            printf("  ");
             // to calculate where the character difference occurs
            int diffInd = strCmpInd(ladderWords[i], ladderWords[i - 1]);

            for(int j = 0; j < diffInd; j++){
                printf(" ");
            }
            printf("^");

            for(int k = diffInd + 1; k < strlen(ladderWords[i]); k++){
                printf(" ");
            }
            printf("\n");
 }
    }
}
/* Task XI - The following two functions free dynamically allocated memory for the word
             and ladder arrays.*/
void freeWordMemory(char** words, int numWords){
    for(int i = 0; i < numWords; i++){
        free(words[i]);
    }
    free(words); // to free the array of word pointers
}

void freeLadderMemory(char** ladder, int ladderHeight){
    for(int i = 0; i < ladderHeight; i++){
        free(ladder[i]);
    }
    free(ladder); // to free the array of ladder pointers
}

/*Task XII - The function handles and processes command line arguments to set
             initial program parameters. */
void commandLineArguments(int argc, char* argv[], int* maxLadder, char* startWord, int* wordLen, char* dict, char* finalWord){

    for(int i = 1; i < argc ; i++){
        if(strcmp(argv[i],"-n") == 0 && i + 1 < argc && *wordLen == 0){
            *wordLen = atoi(argv[++i]);
        }
        else if(strcmp(argv[i],"-m") == 0 && i + 1 < argc && *maxLadder == 1){
            *maxLadder = atoi(argv[i + 1]);
        }
        else if(strcmp(argv[i], "-d") == 0 && i + 1 < argc && strcmp(dict, "notAfile") == 0){
            strcpy(dict, argv[i + 1]);
        }
        else if(strcmp(argv[i], "-s") == 0  && i + 1 < argc && strcmp(startWord, "notAword")== 0){
            strcpy(startWord, argv[i + 1]);
        }
        else if(strcmp(argv[i], "-f") == 0  && i + 1 < argc && strcmp(finalWord, "notValid") == 0){
            strcpy(finalWord, argv[++i]);
        }
        else if(argv[i][0] == '-'){
            printf("Unknown command-line argument.\n");
            exit(1);
            }
        }
}



int main(int argc, char* argv[]) {

    printf("\nProcessing command-line arguments...\n");

    int wordLen = 0;
    int maxLadder = 1;
    char dict[100] = "notAfile";     
    char startWord[30] = "notAword";
    char finalWord[30] = "notValid"; 

    commandLineArguments(argc, argv, &maxLadder, startWord, &wordLen, dict, finalWord);

    printf("Interactively (re)setting invalid parameters:\n");

    // set word length using interactive user-input if necessary
    int numInputs = 1;
    while (numInputs > 0 && (wordLen < 2 || wordLen > 20)) {
        printf("Invalid word length = %d\n", wordLen);
        printf("Enter a valid word length (must be 2-20): ");
        numInputs = scanf("%d",&wordLen);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    // set max ladder height using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && maxLadder < 2) {
        printf("Invalid max ladder height = %d\n", maxLadder);
        printf("Enter a valid max ladder height (must be >1): ");
        numInputs = scanf("%d",&maxLadder);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    FILE* fileTry = fopen(dict,"r");
    numInputs = 1;
    while (numInputs > 0 && fileTry == NULL) {
        printf("Dictionary file %s not found...\n", dict);
        printf("Enter filename for dictionary: ");
        numInputs = scanf("%s", dict);
        printf("\n");
        fileTry = fopen(dict,"r");
    }
    
    fclose(fileTry);
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    int numWords = 0; // initially, no words in the array
    int maxWords = 4; // initially, capacity = 4
    char** words = (char**)malloc(maxWords*sizeof(char*));
    buildWordArray(&words, &numWords, &maxWords, dict, wordLen);

    if(linSearchForWord(words, numWords, startWord) >= 0 && linSearchForWord(words,numWords,finalWord) >= 0){
        printf("\n");
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("Dictionary %s contains insufficient %d-letter words...\n",dict,wordLen);
        printf("Terminating program...\n");
        return -1;
    }

    // resetting start word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,startWord) < 0) {
        printf("\nStart word %s is not valid...\n", startWord);
        printf("Enter a valid start word: ");
        numInputs = scanf("%s", startWord);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // resetting final word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,finalWord) < 0 ) {
        printf("Final word %s is not valid...\n", finalWord);
        printf("Enter a valid final word: ");
        numInputs = scanf("%s", finalWord);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    printf("\nWelcome to the CS 211 Word Ladder Builder!\n");
    printf("\n"); 

    printf("Your goal is to make a word ladder between two ");
    printf("%d-letter words: \n  %s -> %s\n\n",wordLen, startWord,finalWord);  
    
    // Allocating the word ladder for the maximum allowed height
    char** ladder = (char**)malloc(maxLadder*sizeof(char*));

    int ladderHeight = 0; // initially, the ladder is empty
    
    // add the start word to the ladder, i.e. the "bottom rung"
    appendWord(&ladder,&ladderHeight,&maxLadder,startWord);
    
    char aWord[30] = "XYZ";
    printf("\n");
    
    //Task VIII
    while ( ladderHeight < maxLadder && strcmp(aWord, "DONE") != 0 && !isLadderComplete(ladder, ladderHeight, finalWord)) {  
        printf("The goal is to reach the final word: %s\n",finalWord);
        printf("The ladder is currently: \n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Current ladder height: %d\n",ladderHeight);
        printf("Maximum ladder height: %d\n",maxLadder);
        printf("Enter the next word (or DONE to stop): ");
        scanf("%s",aWord);
        printf("\n");

        while (!checkForValidWord(words, numWords, wordLen, ladder, ladderHeight, aWord)) {
            printf("Enter another word (or DONE to stop): ");
            scanf("%s",aWord);
            printf("\n");
        }

        // add the entered word to the ladder (unless it is "DONE")
        if (strcmp(aWord,"DONE") != 0) {
            appendWord(&ladder,&ladderHeight,&maxLadder,aWord);
        }
        printf("\n");
    }
    

    // Check if the built word ladder is complete and 
    // display the word ladder appropriately. 
    if (isLadderComplete(ladder, ladderHeight, finalWord)) {
        printf("Word Ladder complete!\n");
        displayCompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you find a shorter Word Ladder next time??? \n");
    } else {
        if (ladderHeight == maxLadder) printf("The Word Ladder reached the maximum height.\n");
        printf("The final Word Ladder is incomplete:\n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you complete the Word Ladder next time??? \n");
    }
     // to free dynamically allocated memory
     freeWordMemory(words, numWords);
     freeLadderMemory(ladder, ladderHeight);
   
    return 0;
}