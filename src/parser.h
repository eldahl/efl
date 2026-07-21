#pragma once

#include <ctype.h>
#include <stdio.h>

#include "tree.h"

TokenPosition GetClosingParenthesis(char **buffer, int BUFFER_SIZE, int START_POSITION,
                                    TokenPosition token);

void Parse(char **buffer, int BUFFER_SIZE) {

  // Base node where the program context starts
  TreeNode *base = create_node();
  // Set base node to parent to itself
  base->parent = base;

  // Keep track of current scope
  TreeNode *currentScope = base;
  int numOfStartingParentheses = 0;
  int numOfClosingParentheses = 0;

  // Operator/Keyword detection
  int lookForKeywordOrOperator = 0;

  // Arguments detection
  int lookForArguments = 0;

  // Finding scopes
  for (int i = 0; i < BUFFER_SIZE; i++) {
    char c = (*buffer)[i];

    if (lookForKeywordOrOperator) {
      // Operators
      if (c == '+') {
        currentScope->statement = (Statement) { STATEMENT_TYPE_OPERATOR, OPERATOR_TYPE_ADDITION, "Addition" };
      }
      else if (c == '-') {
        currentScope->statement = (Statement) { STATEMENT_TYPE_OPERATOR, OPERATOR_TYPE_SUBTRACT, "Subtraction" };
      }
      else if (c == '*') {
        currentScope->statement = (Statement) { STATEMENT_TYPE_OPERATOR, OPERATOR_TYPE_MULTIPLY, "Multiplication" };
      }
      else if (c == '/') {
        currentScope->statement = (Statement) { STATEMENT_TYPE_OPERATOR, OPERATOR_TYPE_DIVISION, "Division" };
      }

      lookForArguments = 1;
      lookForKeywordOrOperator = 0;
      continue;
    }

    if (lookForArguments) {
      if (c == '(') {
        goto scopeDetection;
      }

      if (c == ' ') {
        continue;
      }

      if (isdigit(c)) {
        
      }

    }

scopeDetection:
    if (c == '(') {
      // Increment number of found starting parentheses
      numOfStartingParentheses++;
      
      TokenPosition startParenthesis = { 0, i };

      // Create new scope for the found parenthesis
      TreeNode *newScope = create_node();
      newScope->start_paren = startParenthesis;

      // Add new scope to base
      add_child(currentScope, newScope);

      // New scope
      currentScope = newScope;

      // Start looking for keywords/operators
      lookForKeywordOrOperator = 1;

      continue;
    }
    else if (c == ')') {
      numOfClosingParentheses++;

      TokenPosition closeParenthesis = { 0, i };

      currentScope->close_paren = closeParenthesis;

      //printf("parentheses pair: %d, %d\n", currentScope->start_paren.index, closeParenthesis.index);

      // Case: There are fewer closing the starting parentheses, go a scope up.
      if(numOfClosingParentheses < numOfStartingParentheses) {
        currentScope = currentScope->parent;
        numOfClosingParentheses--;
        numOfStartingParentheses--;
      }
      // Case: There are more closing than starting parentheses, syntax error.
      else if (numOfClosingParentheses > numOfStartingParentheses) {
        printf("SYNTAX ERROR: More closing parentheses than opening parentheses.");
      }
      // Case: There are equal number of closing and starting parentheses, root scope.
      else if (numOfClosingParentheses == numOfStartingParentheses) {
        currentScope = currentScope->parent;
        numOfClosingParentheses--;
        numOfStartingParentheses--;
      }

      continue;
    } else if (c == '\0') {
      printf("End of buffer\n");
      return;
    }
  }
  print_tree(base, 0);
}

