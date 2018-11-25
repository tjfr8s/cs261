#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MIN(a, b) ((a < b) ? a : b)
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
    char* word = nextWord(file);
    while(word != NULL){
        if(hashMapContainsKey(map, word)){
            (*hashMapGet(map,word))++;
        }
        else{
            hashMapPut(map, word, 1);
        }
        free(word);
        word = nextWord(file);
    }
}

/*
int levenshteinDistance(const char* word1, 
                    int length1, 
                    const char* word2, 
                    int length2){
    int cost;

    if(length1 == 0) {return length2;}
    if(length2 == 0) {return length1;}

    if(word1[length1 - 1] == word2[length2 - 1]){
        cost = 0;
    } 
    else{
        cost = 1;
    }

    return MIN(levenshteinDistance(word1, length1 - 1, word2, length2) + 1,
                   MIN(levenshteinDistance(word1, length1, word2, length2 - 1) + 1,
                   levenshteinDistance(word1, length1 - 1, word2, length2 - 1) + cost));
}
*/

// algorithm source: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
int levenshteinDistance(const char *word1, const char *word2) {
    unsigned int x, y, word1len, word2len;
    word1len = strlen(word1);
    word2len = strlen(word2);
    unsigned int matrix[word1len+1][word1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= word2len; x++){
        matrix[x][0] = matrix[x-1][0] + 1;
    }
    for (y = 1; y <= word1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= word2len; x++){
        for (y = 1; y <= word1len; y++){
            int cost = 1;
            if(word1[y-1] == word2[x-1]){
                cost = 0;
            }

            matrix[x][y] = MIN3(matrix[x-1][y] + 1, 
                                matrix[x][y-1] + 1, 
                                matrix[x-1][y-1] + cost);
            }
    }
    return(matrix[word2len][word1len]);
}

void levenshtein(HashMap* dictionary, char** bestFive, const char* word){
    int i;
    int j;
    for(j = 0; j < 5; j++){
        bestFive[j] = NULL;
    }
    for(i = 0; i < hashMapCapacity(dictionary); i++){
        HashLink* current = dictionary->table[i];
        while(current != NULL){
            current->value = levenshteinDistance(current->key,
                                                 word);
            int numNull;
            numNull = 0;
            while(bestFive[numNull] == NULL && numNull < 5){
                numNull++; 
            }
            if(numNull > 0){
                bestFive[numNull - 1] = current->key;
            }
            else{
                int addBefore = 0; 
                while(addBefore < 5 && 
                      *hashMapGet(dictionary, bestFive[addBefore]) < current->value){
                    addBefore++;
                }
                if(addBefore < 5){
                    int j;
                    for(j = 4; j > addBefore; j--){
                        bestFive[j] = bestFive[j - 1];
                    }
                    bestFive[addBefore] = current->key;
                }
            }
            current = current->next;
        }
    }
}


/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    char* bestFive[5];
    int i;
    for(i = 0; i < 5; i++){
        bestFive[i] = NULL;
    }
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        printf("%s\n", inputBuffer);
        int i = 0;
        while(inputBuffer[i] != '\0'){
            inputBuffer[i] = tolower(inputBuffer[i]);
            i++;
        }
        
        if(strcmp(inputBuffer, "quit") == 0){
            printf("Quitting...\n"); 
        }
        else if(hashMapContainsKey(map, inputBuffer)){
            printf("The inputted word %s is spelled correctly.\n", inputBuffer);
        }
        else{
            printf("The inputted word %s is spelled incorrectly\n"
                    "Maybe you meant:\n", inputBuffer);
            levenshtein(map, bestFive, inputBuffer);
            int printIndex;
            for(printIndex = 0; printIndex < 5; printIndex++){
                printf("%s, %d\n", bestFive[printIndex], *hashMapGet(map, bestFive[printIndex]));
            }
        }
        
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}
