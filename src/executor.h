#pragma once

#include "eval_tree.h"
#include "tree.h"

void Evaluate(EvalTreeNode *evalTree, ParsingTreeNode *node) {

  if (evalTree == NULL)
    return;

  // Build AST
  if (node->statement.statement_type == STATEMENT_TYPE_SCOPE) {
    if (strcmp(node->statement.statement_identifier, "Main Context") == 0) {
      evalTree->statement = node->statement;
      // Evaluate all children
      for (int i = 0; i < node->child_count; i++) {
        Evaluate(evalTree, node->children[i]);
      }
      return;
    }
    // Scope
    EvalTreeNode *eNode = et_create_node();
    eNode->statement = node->statement;
    eNode->arg_lhs = node->arg_lhs;
    eNode->arg_rhs = node->arg_rhs;
    et_add_child(evalTree, eNode);
    // Evaluate all children
    for (int i = 0; i < node->child_count; i++) {
      Evaluate(evalTree, node->children[i]);
    }
  } else if (node->statement.statement_type == STATEMENT_TYPE_OPERATOR &&
             node->arg_lhs.argument_type == ARGUMENT_TYPE_NUMBER &&
             node->arg_rhs.argument_type == ARGUMENT_TYPE_NUMBER) {
    EvalTreeNode *eNode = et_create_node();
    eNode->statement = node->statement;
    eNode->arg_lhs = node->arg_lhs;
    eNode->arg_rhs = node->arg_rhs;
    int lhs = (int)*(node->arg_lhs.argument_data);
    int rhs = (int)*(node->arg_rhs.argument_data);
    if (node->statement.statement_sub_type == OPERATOR_TYPE_ADDITION) {
      printf("%d + %d = %d\n", lhs, rhs, lhs + rhs);
      eNode->result.argument_type = ARGUMENT_TYPE_NUMBER;
      eNode->result.argument_data = argument_from_number(lhs + rhs);
    } else if (node->statement.statement_sub_type == OPERATOR_TYPE_SUBTRACT) {
      printf("%d - %d = %d\n", lhs, rhs, lhs - rhs);
      eNode->result.argument_type = ARGUMENT_TYPE_NUMBER;
      eNode->result.argument_data = argument_from_number(lhs - rhs);
    } else if (node->statement.statement_sub_type == OPERATOR_TYPE_MULTIPLY) {
      printf("%d * %d = %d\n", lhs, rhs, lhs * rhs);
      eNode->result.argument_type = ARGUMENT_TYPE_NUMBER;
      eNode->result.argument_data = argument_from_number(lhs * rhs);
    } else if (node->statement.statement_sub_type == OPERATOR_TYPE_DIVISION) {
      printf("%d / %d = %d\n", lhs, rhs, lhs / rhs);
      eNode->result.argument_type = ARGUMENT_TYPE_NUMBER;
      eNode->result.argument_data = argument_from_number(lhs / rhs);
    }
    et_add_child(evalTree, eNode);
  } else if (node->statement.statement_type == STATEMENT_TYPE_OPERATOR &&
             (node->arg_lhs.argument_type == ARGUMENT_TYPE_FUNCTION ||
              node->arg_rhs.argument_type == ARGUMENT_TYPE_FUNCTION)) {
    EvalTreeNode *eNode = et_create_node();
    eNode->statement = node->statement;
    eNode->arg_lhs = node->arg_lhs;
    eNode->arg_rhs = node->arg_rhs;

    if (node->child_count > 1) {
      printf("UNHANDLED: more than one child node for operator statement.");
      exit(0);
    }

    // Evaluate the one scope
    if (node->child_count == 1)
      Evaluate(eNode, node->children[0]);

    if (eNode->children[0]->result.argument_type == ARGUMENT_TYPE_NUMBER) {
      int lhs = 0;
      int rhs = 0;
      if (eNode->arg_lhs.argument_type == ARGUMENT_TYPE_NUMBER) {
        lhs = (int)*(eNode->arg_lhs.argument_data);
        rhs = (int)*(eNode->children[0]->result.argument_data);
      }
      if (eNode->arg_rhs.argument_type == ARGUMENT_TYPE_NUMBER) {
        lhs = (int)*(eNode->children[0]->result.argument_data);
        rhs = (int)*(eNode->arg_rhs.argument_data);
      }
      if (eNode->statement.statement_sub_type == OPERATOR_TYPE_ADDITION) {
        printf("%d + %d = %d\n", lhs, rhs, lhs + rhs);
        eNode->result.argument_type = ARGUMENT_TYPE_NUMBER;
        eNode->result.argument_data = argument_from_number(lhs + rhs);
      }
      if (eNode->statement.statement_sub_type == OPERATOR_TYPE_SUBTRACT) {
        printf("%d - %d = %d\n", lhs, rhs, lhs - rhs);
        eNode->result.argument_type = ARGUMENT_TYPE_NUMBER;
        eNode->result.argument_data = argument_from_number(lhs - rhs);
      }
      if (eNode->statement.statement_sub_type == OPERATOR_TYPE_MULTIPLY) {
        printf("%d * %d = %d\n", lhs, rhs, lhs * rhs);
        eNode->result.argument_type = ARGUMENT_TYPE_NUMBER;
        eNode->result.argument_data = argument_from_number(lhs * rhs);
      }
      if (eNode->statement.statement_sub_type == OPERATOR_TYPE_DIVISION) {
        printf("%d / %d = %d\n", lhs, rhs, lhs / rhs);
        eNode->result.argument_type = ARGUMENT_TYPE_NUMBER;
        eNode->result.argument_data = argument_from_number(lhs / rhs);
      }
    }
    et_add_child(evalTree, eNode);
    // if (eNode->children[0]->result.argument_type == ARGUMENT_TYPE_FUNCTION
    // ||
    //     eNode->children[1]->result.argument_type == ARGUMENT_TYPE_FUNCTION)
    //     {
    // }
  }
}
