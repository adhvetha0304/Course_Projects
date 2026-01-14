/* ------------------------------------------------------------------------------
   Program: Link Lint List - Find Shortest Word Ladder
   Course: CS 211, Fall 2024
   Author: Adhvetha SP
   ------------------------------------------------------------------------------
   Description : This program finds the shortest word ladder between two words,
   changing one letter at a time and ensuring each step is a valid word from a 
   dictionary. It uses breadth-first search and dynamically manages memory to 
   avoid leaks.
   
   ------------------------------------------------------------------------------
   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

// Counts words of a given length in a file
int countWordsOfLength(char* filename, int wordSize) { 
FILE* file = fopen(filename, "r");
 // return -1 if the file cannot be opened
if(file == NULL){
    return -1;
}
int count = 0;
int currentLength = 0;
char c;

while((c = fgetc(file)) != EOF){
    if(c == ' ' || c == '\n'){
        if(currentLength == wordSize){
            count++;
        }
        currentLength = 0;
    }
    else{
        currentLength++;
    }
}
if(currentLength == wordSize){
    count++;
}
fclose(file);
return count; 
}

// Test function for countWordsOfLength()
bool test_countWordsOfLength(){
    int count = countWordsOfLength("simple3.txt", 3);
    if(count != 25){
        printf("test_countWordsOfLength FAILED. Expected 25, got %d\n", count);
        return false;
    }
    printf("test_countWordsOfLength PASSED.\n");
    return true;
}

// Builds an array of words of a given length
bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
    FILE* file = fopen(filename, "r");
    // returns false if the file can't be opened
    if(file == NULL){
        return false;
    }

    int count = 0; 
    char buffer[100];

    while(fscanf(file, "%s", buffer) != EOF){
        if(strlen(buffer) == wordSize){  // Only adds words matching wordSize
            strcpy(words[count], buffer);
            count++;
        }
        if(count > numWords){
            fclose(file);
            return false;
        }
    }
    fclose(file);
    // checks if the number of words read matches the expected number
    if(count == numWords){
        return true;
    }
    else{
        return false;
    }
}

// Test function for builWordArray
bool test_buildWordArray(){
    int numWords = 25;
    char* words[numWords];
    for(int i = 0; i < numWords; i++){
        words[i] = (char*)malloc(4*sizeof(char));
    }

    bool passed = buildWordArray("simple3.txt", words, numWords, 3);
    if(!passed){
        printf("test_buildWordArray FAILED. Could not build word array.\n");
        return false;
    }
    printf("test_buildWordArray PASSED.\n");
    return true;
}

// Finds a word in an array using binary search
int findWord(char** words, char* aWord, int loInd, int hiInd) { 
    while(loInd <= hiInd){
        int midInd = loInd + (hiInd - loInd) / 2;
        
        int compareResult = strcmp(words[midInd], aWord);

        if(compareResult == 0){
            return midInd;
        }
        else if(compareResult > 0){
            hiInd = midInd - 1;
        }
        else{
            loInd = midInd + 1;
        }
    }
    return -1; // modify this line
}

// Test function for findWord()
bool test_findWord(){
    char* words[25] = {"aim", "arm","bam","bum","ear","eye","gum",
    "hip","hog","hop","jam","jar","jaw","leg","lip","log","rib","rim",
    "rip","rum","tap","tar","tie","tip","toe"};
    int index = findWord(words, "eye", 0, 24);
    if(index =! 4){
        printf("test_findWord FAILED. Expected 4, got %d\n", index);
        return false;
    }
    printf("test_findWord PASSED.\n");
    return true;
}

// Frees memory for a word array
void freeWords(char** words, int numWords) {
    for(int i = 0; i < numWords; ++i){
        free(words[i]);
    }
    free(words);
}

// Inserts a word at the front of a WordNode list 
void insertWordAtFront(WordNode** ladder, char* newWord) {
    WordNode* node = (WordNode*)malloc(sizeof(WordNode));
    node->myWord = newWord;
    node->next = NULL;

    if(*ladder == NULL){
        *ladder = node;
    }
    else{
        node->next = *ladder;
        *ladder = node;
    }
}

// Test function for insertWordAtFront()
bool test_insertWordAtFront(){
    WordNode* ladder = NULL;
    insertWordAtFront(&ladder, "toe");

    if(ladder == NULL || strcmp(ladder->myWord, "toe") != 0){
        printf("test_insertWordAtFront FAILED.\n");
        return false;
    }
    insertWordAtFront(&ladder, "tip");
    if(strcmp(ladder->myWord, "tip") != 0){
        printf("test_insertWordAtFront FAILED .\n");
        return false;
    }
    printf("test_insertWordAtFront PASSED.\n");
    return true;
}
// Calculates the height of a ladder 
int getLadderHeight(WordNode* ladder) {
    if(ladder == NULL){
        return 0;
    }
    int height = 1 + getLadderHeight(ladder->next);
    return height ;

}

// Test function for getLadderHeight()
bool test_getLadderHeight(){
    WordNode* ladder = NULL;
    insertWordAtFront(&ladder, "toe");
    insertWordAtFront(&ladder, "tip");

    int height = getLadderHeight(ladder);
    if(height != 2){
        printf("test_getLadderHeight FAILED. Expected 2, got %d\n",height);
        return false;
    }
    printf("test_getLadderHeight PASSED.\n");
    return true;
}

// Copies a ladder to create a new linked list with the same words
WordNode* copyLadder(WordNode* ladder) {
    if(ladder == NULL){
        return NULL;
    }

    WordNode* copiedLadder = (WordNode*)malloc(sizeof(WordNode));
    copiedLadder->myWord = ladder->myWord;
    copiedLadder->next = copyLadder(ladder->next);

    return copiedLadder;
}

//Frees memory allocated for a ladder
void freeLadder(WordNode* ladder) {
    if(ladder == NULL){
        return;
    }
    freeLadder(ladder->next);
    free(ladder);
}

// Inserts a ladder at the back of a list of ladderNodes
void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    LadderNode* newLadderNode = (LadderNode*)malloc(sizeof(LadderNode));
    newLadderNode->topWord = newLadder;
    newLadderNode->next = NULL;

    if(*list == NULL){
        *list = newLadderNode;
    }
    else{
        LadderNode* currentLadder = *list;
        while(currentLadder->next != NULL){
            currentLadder = currentLadder->next;
        }
        currentLadder->next = newLadderNode;
    }
}

// Pops the first ladder from a list of LadderNodes
WordNode* popLadderFromFront(LadderNode** list) {
    if(*list == NULL){
        return NULL;
    }
    LadderNode* headNode = *list;
    *list = headNode->next;
    WordNode* firstLadder = headNode->topWord;
    free(headNode);
    return firstLadder;
}

// Frees all ladders in a list of LadderNodes
void freeLadderList(LadderNode* myList) {
    while(myList != NULL){
        LadderNode* nextLadder = myList->next;
        freeLadder(myList->topWord);
        free(myList);
        myList = nextLadder;
    }
}

// Find the shortest word ladder between two words
WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {

    LadderNode* myList = NULL;
    WordNode* startLadder = NULL;
    insertWordAtFront(&startLadder, startWord);
    insertLadderAtBack(&myList, startLadder);

    int startWordInd = findWord(words, startWord, 0, numWords - 1);
    usedWord[startWordInd] = true;

    while(myList != NULL){
        WordNode* currentLadder = popLadderFromFront(&myList);
        char* topWord = currentLadder->myWord;

        if(strcmp(topWord, finalWord) == 0){
            freeLadderList(myList);
            return currentLadder;
        }
        for(int i = 0; i < numWords; i++){
            if(!usedWord[i]){
                int countDiff = 0;
                
                for(int j = 0; j < wordSize; j++){
                    if(topWord[j] != words[i][j]){
                        countDiff++;
                }
                if(countDiff > 1){
                    break;
                }
            }
            if(countDiff == 1){
                WordNode* ladder = copyLadder(currentLadder);
                insertWordAtFront(&ladder, words[i]);
                insertLadderAtBack(&myList,ladder);

                usedWord[i] = true;
            }
        }
    }
    freeLadder(currentLadder);
 }
    return NULL;
}

// Helper function to set a word and ensure it is in the dictionary 
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// Helper function to print a ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// Helper function to print the full list of ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}

// Test function to verify if memory is free correctly
bool test_freeWords(){
    int numWords = 25;
    char** words = (char**)malloc(numWords * sizeof(char*));
    for(int i = 0; i < numWords; i++){
        words[i] = (char*)malloc(4 * sizeof(char));
        strcpy(words[i], "bat");
    }
    freeWords(words, numWords);
    printf("test_freeWords PASSED.\n");
    return true;
}

//Combining all individual tests
void runTests(){
    printf("Running Tests:\n");

    if(!test_countWordsOfLength()){
        printf("countWordsOfLength Test FAILED.\n");
    }
    if(!test_buildWordArray()){
        printf("buildWordArray Test FAILED.\n");
    }
    if(!test_findWord()){
        printf("findWord Test FAILED.\n");
    }
    if(!test_insertWordAtFront()){
        printf("insertWordAtFront Test FAILED.\n");
    }
    if(!test_getLadderHeight()){
        printf("getLadderHeight Test FAILED.\n");
    }
    if(!test_freeWords()){
        printf("freeWords test FAILED.\n");
    }
    printf("All tests completed.\n");
}


//-----------------------------------------------------
// The primary application is fully provided in main(); 
//  no changes should be made to main()
//-----------------------------------------------------
int main() {
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100];
    printf("Enter filename for dictionary: ");
    scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize); 
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}
