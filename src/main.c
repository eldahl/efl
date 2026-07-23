/*
There are two ways to go about building a programming language implementation:

### The Lisp way ###
  Parse & Tokenize
  Build AST
  Interpret directly

### The compiled way ###
  Parse & Tokenize
  Build AST
  Make bytecode/machine code

To start out, it seems like the path of least resistance is the Lisp way.
*/

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "parser.h"
#include "executor.h"


int main(int argv, char **argc) {
  int evaluating = 1;
  size_t INPUT_BUFFER_SIZE = 1024;

  char *inputBuffer = (char *)malloc(INPUT_BUFFER_SIZE * sizeof(char));
  if (inputBuffer == NULL) {
    printf("Memory allocation failed!\n");
    return 1;
  }
  
  while (evaluating == 1) {
    
    getline(&inputBuffer, &INPUT_BUFFER_SIZE, stdin);
    int readChars = strlen(inputBuffer);
    
    printf("chars: %d", readChars);
    printf("\n");
    
    if (inputBuffer[0] == 'e' && inputBuffer[1] == 'x' &&
        inputBuffer[2] == 'i' && inputBuffer[3] == 't') {
      evaluating = 0;
    }

    ParsingTreeNode* syntax_tree = Parse(&inputBuffer, readChars);
    Evaluate(syntax_tree);

    // Zero the input buffer
    memset(inputBuffer, 0, INPUT_BUFFER_SIZE * sizeof(char));
  }

  // Remember to free the buffer memory
  free(inputBuffer);

  return 0;
}

