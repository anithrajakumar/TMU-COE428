#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern char * pop();
extern void push(char * tagToPush);
extern int isEmpty();

#define MAX_TAG_LENGTH 100

int main(int argc, char * argv[])
{
    int currentChar;
    char currentTag[MAX_TAG_LENGTH];
    int isEndTag = 0;
    int isStartTag = 0;
    int tagPosition = 0;
    int openTagsCount = 0;

    while ((currentChar = getchar()) != EOF) {
        // Skip non-tag characters
        if (!(isalpha(currentChar) || currentChar == '>' || currentChar == '<' || currentChar == '/')) {
            continue;
        }

        if (currentChar == '<') {
            currentChar = getchar();
            if (currentChar == '/') {
                isEndTag = 1;
            } else {
                if (isalpha(currentChar)) {
                    currentTag[tagPosition++] = (char)currentChar;
                    isStartTag = 1;
                } else {
                    fprintf(stderr, "Error: Invalid tag character '%c'\n", currentChar);
                    exit(EXIT_FAILURE);
                }
            }
        } 
        else if (currentChar == '>') {
            currentTag[tagPosition] = '\0';

            if (isStartTag) {
                char *tagCopy = strdup(currentTag);
                if (tagCopy == NULL) {
                    fprintf(stderr, "Error: Failed to allocate memory for tag\n");
                    exit(EXIT_FAILURE);
                }
                push(tagCopy);
                openTagsCount++;
            } 
            else if (isEndTag) {
                char *poppedTag = pop();
                if (poppedTag == NULL) {
                    fprintf(stderr, "Error: Unmatched end tag </%s>\n", currentTag);
                    exit(EXIT_FAILURE);
                }
                if (strcmp(currentTag, poppedTag) != 0) {
                    fprintf(stderr, "Error: Tag mismatch - expected </%s>, found </%s>\n", 
                            poppedTag, currentTag);
                    free(poppedTag);
                    exit(EXIT_FAILURE);
                }
                free(poppedTag);
                openTagsCount--;
            }

            // Reset tag processing state
            memset(currentTag, 0, sizeof(currentTag));
            isStartTag = 0;
            isEndTag = 0;
            tagPosition = 0;
        } 
        else {
            if (tagPosition < MAX_TAG_LENGTH - 1) {
                currentTag[tagPosition++] = (char)currentChar;
            } else {
                fprintf(stderr, "Error: Tag name exceeds maximum length of %d\n", MAX_TAG_LENGTH);
                exit(EXIT_FAILURE);
            }
        }
    }

    if (openTagsCount != 0) {
        fprintf(stderr, "Error: Unclosed tags remaining in document:\n");
        while (!isEmpty()) {
            char *unclosedTag = pop();
            fprintf(stderr, " - <%s>\n", unclosedTag);
            free(unclosedTag);
        }
        exit(EXIT_FAILURE);
    }
    
    printf("Valid XML document\n");
    return EXIT_SUCCESS;
}