#pragma once

#include <stdio.h>

typedef struct {
  int line;
  int index;
} TokenPosition;

TokenPosition GetClosingParenthesis(char **buffer, int START_INDEX,
                                    int BUFFER_SIZE, TokenPosition token) {

  int firstParenthesis = START_INDEX;
  int numOfFoundStartingParentheses = 0;
  int numOfFoundClosingParentheses = 0;

  for (int i = START_INDEX; i < BUFFER_SIZE; i++) {
    char c = (*buffer)[i];

    if (c == '(') {
      numOfFoundStartingParentheses++;
    } else if (c == ')') {
      numOfFoundClosingParentheses++;
      return (TokenPosition){0, i};
    } else if (c == EOF) {
      return (TokenPosition){-1, -1};
    }
  }
  return (TokenPosition){-1, -1};
}

