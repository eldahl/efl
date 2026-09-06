#pragma once

#include <ctype.h>
#include <stdio.h>

#include "tree.h"

TokenPosition GetClosingParenthesis(char **buffer, int BUFFER_SIZE, int START_POSITION,
                                    TokenPosition token);

ParsingTreeNode* Parse(char **buffer, int BUFFER_SIZE) {

  // Base node where the program context starts
  ParsingTreeNode *base = create_node();
  // Set base node to parent to itself
  base->parent = base;
  base->statement = (Statement) { STATEMENT_TYPE_SCOPE, OPERATOR_TYPE_NULL, argument_from_string("Main Context", 12) };

  // Keep track of current scope
  ParsingTreeNode *currentScope = base;
  int numOfStartingParentheses = 0;
  int numOfClosingParentheses = 0;

  // Finding scopes
  for (int i = 0; i < BUFFER_SIZE; i++) {
    char c = (*buffer)[i];
    //printf("%d: %c\n", i, c);

    if (currentScope->lookForKeywordOrOperator) {
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
      else if (c == ' ') {
        currentScope->statement = (Statement) { STATEMENT_TYPE_SCOPE, OPERATOR_TYPE_NULL, "Scope" };
      }
      else {
        currentScope->lookForArguments = 1;
        currentScope->lookForKeywordOrOperator = 0;
        goto scopeDetection;
      }

      currentScope->lookForArguments = 1;
      currentScope->lookForKeywordOrOperator = 0;
      continue;
    }

    if (currentScope->lookForArguments) {
      if (isdigit(c)) {
        // Extract characters of number and find the last digit of the number.
        int lastIdx = 0; int lastDigit = 0; char digitBuffer[1024]; 
        for(int idx = 0; isdigit((*buffer)[i + idx]); idx++) { 
          digitBuffer[idx] = (*buffer)[i + idx];
          lastDigit = i + idx;
          lastIdx = idx;
        }
        // Add null termination to the char string so we can do atoi()
        digitBuffer[lastIdx + 1] = '\0';

        int number = atoi(digitBuffer);
        // printf("%d - %d\n", i, lastDigit);
        // printf("digit buffer: %s\n", digitBuffer);
        // printf("number: %d\n", number);

        // LHS
        if(currentScope->arg_lhs.argument_type == ARGUMENT_TYPE_NULL) {
          currentScope->arg_lhs.argument_type = ARGUMENT_TYPE_NUMBER;
          currentScope->arg_lhs.argument_identifier = "Number";
          currentScope->arg_lhs.argument_data = argument_from_number(number);
        }
        // RHS
        else if (currentScope->arg_rhs.argument_type == ARGUMENT_TYPE_NULL) {
          currentScope->arg_rhs.argument_type = ARGUMENT_TYPE_NUMBER;
          currentScope->arg_rhs.argument_identifier = "Number";
          currentScope->arg_rhs.argument_data = argument_from_number(number);
          currentScope->lookForArguments = 0;
        }
        else {
          printf("arg_lhs & arg_rhs is non-NULL when they shouldn't be.\n");
        }

        // Jump character reading progress to the end of the number
        i = lastDigit;
        continue;
      }
      else {
        goto scopeDetection;
      }
    }

scopeDetection:
    if (c == '(') {

      // Increment number of found starting parentheses
      numOfStartingParentheses++;

      // if (lookForKeywordOrOperator) {
      //   currentScope->statement = (Statement) { STATEMENT_TYPE_SCOPE, OPERATOR_TYPE_NULL, "Scope" };
      //   lookForKeywordOrOperator = 0;
      // }

      if (currentScope->lookForArguments) {
        if (currentScope->arg_lhs.argument_type == ARGUMENT_TYPE_NULL) {
          currentScope->arg_lhs = (Argument) { ARGUMENT_TYPE_FUNCTION, NULL, "Scope" };
        }
        else if (currentScope->arg_rhs.argument_type == ARGUMENT_TYPE_NULL) {
          currentScope->arg_rhs = (Argument) { ARGUMENT_TYPE_FUNCTION, NULL, "Scope" };
          currentScope->lookForArguments = 0;
        }
        else {
          printf("arg_lhs & arg_rhs is non-NULL when they shouldn't be.\n");
        }
      }

      TokenPosition startParenthesis = { 0, i };

      // Create new scope for the found parenthesis
      ParsingTreeNode *newScope = create_node();
      newScope->start_paren = startParenthesis;

      // Add new scope to base
      add_child(currentScope, newScope);

      // New scope
      currentScope = newScope;

      // Start looking for keywords/operators
      currentScope->lookForKeywordOrOperator = 1;

      continue;
    }
    else if (c == ')') {
      numOfClosingParentheses++;

      TokenPosition closeParenthesis = { 0, i };

      currentScope->close_paren = closeParenthesis;

      //printf("parentheses pair: %d, %d\n", currentScope->start_paren.index, closeParenthesis.index);

      // Set statement for scope to be a non-behavioured scope if no statement has been set when reaching the closing parenthesis.
      if (currentScope->statement.statement_type == STATEMENT_TYPE_NULL) {
        currentScope->statement = (Statement) { STATEMENT_TYPE_SCOPE, OPERATOR_TYPE_NULL, "Scope" };
      }

      // Case: There are fewer closing the starting parentheses, go a scope up.
      if(numOfClosingParentheses < numOfStartingParentheses) {
        currentScope = currentScope->parent;
        numOfClosingParentheses--;
        numOfStartingParentheses--;
      }
      // Case: There are more closing than starting parentheses, syntax error.
      else if (numOfClosingParentheses > numOfStartingParentheses) {
        printf("SYNTAX ERROR: More closing parentheses than opening parentheses.\n");
      }
      // Case: There are equal number of closing and starting parentheses, root scope.
      else if (numOfClosingParentheses == numOfStartingParentheses) {
        currentScope = currentScope->parent;
        numOfClosingParentheses--;
        numOfStartingParentheses--;
      }
      continue;
    }
    else if (c == '\0') {
      printf("End of buffer\n");
      return NULL;
    }
  }
  print_tree(base, 0);
  return base;
}

