#pragma once

#include <stdio.h>

typedef struct {
  int line;
  int index;
} TokenPosition;

TokenPosition GetClosingParenthesis(char **buffer, int BUFFER_SIZE,
                                    TokenPosition token);

void Parse(char **buffer, int BUFFER_SIZE) {

  // Finding scopes
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if ((*buffer)[i] == '(') {
      TokenPosition startParenthesis = {0, i};
      TokenPosition foundParenthesis =
          GetClosingParenthesis(buffer, BUFFER_SIZE, startParenthesis);
      // scopes[scopesSize++] = (Scope){startParenthesis, foundParenthesis};

      if (foundParenthesis.line == -1 || foundParenthesis.index == -1) {
        continue;
      }

      printf("parentheses pair: %d, %d\n", foundParenthesis.index,
             foundParenthesis.index);
    }
  }
}

TokenPosition GetClosingParenthesis(char **buffer, int BUFFER_SIZE,
                                    TokenPosition token) {
  int numOfFoundStartingParentheses = 0;
  int numOfFoundClosingParentheses = 0;

  for (int i = 0; i < BUFFER_SIZE; i++) {
    char c = (*buffer)[i];

    if (c == '(') {
      numOfFoundStartingParentheses++;
      continue;
    } else if (c == ')') {
      numOfFoundClosingParentheses++;
      return (TokenPosition){0, i};
    } else if (c == '\0') {
      //printf("End of buffer\n");
      return (TokenPosition){-1, -1};
    }
  }
  //printf("No closing parenthesis\n");
  return (TokenPosition){-1, -1};
}
