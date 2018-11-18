#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MIN(a, b) ((a < b) ? a : b)

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

void levenshtein(HashMap* dictionary, const char* word){
    int i;
    for(i = 0; i < hashMapCapacity(dictionary); i++){
        HashLink* current = dictionary->table[i];
        while(current != NULL){
            current->value = levenshteinDistance(current->key,
                                                 strlen(current->key),
                                                 word,
                                                 strlen(word));
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
        levenshtein(map, inputBuffer)
        printf("%s\n", inputBuffer);
        
        //printf("%s, %s, ld: %d", "test", inputBuffer, levenshteinDistance("test", strlen("test"), inputBuffer, strlen(inputBuffer)));
        
        //Fix me:  implement the spell checker code here..
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
        //hashMapPrint(map);
    }
    
    hashMapDelete(map);
    return 0;
}
