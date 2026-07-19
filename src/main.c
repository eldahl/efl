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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "parser.h"

int main(int argv, char **argc) {
  int evaluating = 1;
  int INPUT_BUFFER_SIZE = 1024;

  char *inputBuffer = (char *)malloc(INPUT_BUFFER_SIZE * sizeof(char));
  if (inputBuffer == NULL) {
    printf("Memory allocation failed!\n");
    return 1;
  }
  
  // Create Root
  TreeNode* root = create_node("Root");

  // Level 1
  TreeNode* branch1 = create_node("Branch A");
  TreeNode* branch2 = create_node("Branch B");
  add_child(root, branch1);
  add_child(root, branch2);

  // Level 2 Branches (many branches on branch A)
  add_child(branch1, create_node("Sub branch A1"));
  add_child(branch1, create_node("Sub branch A2"));
  add_child(branch1, create_node("Sub branch A3"));

  // Level 2 Branch on branch B
  TreeNode* sub_b1 = create_node("Sub branch B1");
  add_child(branch2, sub_b1);

  // Level 3 branch
  add_child(sub_b1, create_node("Leaf B1.1"));

  // Show result
  printf("Tree structure:\n");
  print_tree(root, 0);

  // Clean up
  free_tree(root);

  while (evaluating == 1) {

    int readChars = scanf("%s", inputBuffer);
    printf("\n");

    for (int i = 0; i < readChars; i++) {
      if (inputBuffer[i] == '(') {
        TokenPosition startParenthesis = {0, i};
        TokenPosition foundParenthesis = GetClosingParenthesis(
            &inputBuffer, i, INPUT_BUFFER_SIZE, startParenthesis);
        if (foundParenthesis.index == -1 || foundParenthesis.line == -1) {
          printf("No closing parenthesis found");
        }

        //scopes[scopesSize++] = (Scope){startParenthesis, foundParenthesis};
        printf("parentheses pair: %d, %d", startParenthesis.index,
               foundParenthesis.index);
      }
    }

    if (inputBuffer[0] == 'a') {
      printf("aaaaaaaaaaaaaaa\n");
    }

    // for(int i = 0; i < INPUT_BUFFER_SIZE; i++) {
    // 	printf("%c", inputBuffer[i]);
    // }

    if (inputBuffer[0] == 'e' && inputBuffer[1] == 'x' &&
        inputBuffer[2] == 'i' && inputBuffer[3] == 't') {
      evaluating = 0;
    }

    // Zero the input buffer
    memset(inputBuffer, 0, INPUT_BUFFER_SIZE * sizeof(char));
  }

  // Remember to free the buffer memory
  free(inputBuffer);

  return 0;
}

