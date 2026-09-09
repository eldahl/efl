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
      Evaluate(eNode, node->children[i]);
    }
  } else if (node->statement.statement_type == STATEMENT_TYPE_OPERATOR &&
             (node->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER ||
              node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) &&
             (node->arg_rhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER ||
              node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER)) {
    EvalTreeNode *eNode = et_create_node();
    eNode->statement = node->statement;
    eNode->arg_lhs = node->arg_lhs;
    eNode->arg_rhs = node->arg_rhs;
    double lhs_dou = 0;
    double rhs_dou = 0;
    int lhs_int = 0;
    int rhs_int = 0;
    if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
      lhs_int = *(int *)(node->arg_lhs.argument_data);
    } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
      lhs_dou = *(double *)(node->arg_lhs.argument_data);
    }
    if (node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
      rhs_int = *(int *)(node->arg_rhs.argument_data);
    } else if (node->arg_rhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
      rhs_dou = *(double *)(node->arg_rhs.argument_data);
    }

    if (node->statement.statement_sub_type == OPERATOR_TYPE_ADDITION) {
      if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
          node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
        eNode->result.argument_data =
            argument_from_integer_number(lhs_int + rhs_int);
        eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
        printf("%d + %d = %d\n", lhs_int, rhs_int, lhs_int + rhs_int);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_dou + rhs_dou);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%f + %f = %f\n", lhs_dou, rhs_dou, lhs_dou + rhs_dou);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_dou + rhs_int);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%f + %d = %f\n", lhs_dou, rhs_int, lhs_dou + rhs_int);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_int + rhs_dou);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%d + %f = %f\n", lhs_int, rhs_dou, lhs_int + rhs_dou);
      }
    } else if (node->statement.statement_sub_type == OPERATOR_TYPE_SUBTRACT) {
      if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
          node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
        eNode->result.argument_data =
            argument_from_integer_number(lhs_int - rhs_int);
        eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
        printf("%d - %d = %d\n", lhs_int, rhs_int, lhs_int - rhs_int);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_dou - rhs_dou);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%f - %f = %f\n", lhs_dou, rhs_dou, lhs_dou - rhs_dou);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_dou - rhs_int);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%f - %d = %f\n", lhs_dou, rhs_int, lhs_dou - rhs_int);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_int - rhs_dou);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%d - %f = %f\n", lhs_int, rhs_dou, lhs_int - rhs_dou);
      }
    } else if (node->statement.statement_sub_type == OPERATOR_TYPE_MULTIPLY) {
      if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
          node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
        eNode->result.argument_data =
            argument_from_integer_number(lhs_int * rhs_int);
        eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
        printf("%d * %d = %d\n", lhs_int, rhs_int, lhs_int * rhs_int);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_dou * rhs_dou);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%f * %f = %f\n", lhs_dou, rhs_dou, lhs_dou * rhs_dou);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_dou * rhs_int);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%f * %d = %f\n", lhs_dou, rhs_int, lhs_dou * rhs_int);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_int * rhs_dou);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%d * %f = %f\n", lhs_int, rhs_dou, lhs_int * rhs_dou);
      }
    } else if (node->statement.statement_sub_type == OPERATOR_TYPE_DIVISION) {
      if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
          node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
        eNode->result.argument_data =
            argument_from_integer_number(lhs_int / rhs_int);
        eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
        printf("%d / %d = %d\n", lhs_int, rhs_int, lhs_int / rhs_int);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_dou / rhs_dou);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%f / %f = %f\n", lhs_dou, rhs_dou, lhs_dou / rhs_dou);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_dou / rhs_int);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%f / %d = %f\n", lhs_dou, rhs_int, lhs_dou / rhs_int);
      } else if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
                 node->arg_rhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
        eNode->result.argument_data =
            argument_from_double_number(lhs_int / rhs_dou);
        eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
        printf("%d / %f = %f\n", lhs_int, rhs_dou, lhs_int / rhs_dou);
      }
    }
    et_add_child(evalTree, eNode);
  } else if (node->statement.statement_type == STATEMENT_TYPE_OPERATOR &&
             (node->arg_lhs.argument_type == ARGUMENT_TYPE_FUNCTION ||
              node->arg_rhs.argument_type == ARGUMENT_TYPE_FUNCTION)) {

    if (node->child_count == 1) {
      EvalTreeNode *eNode = et_create_node();
      eNode->statement = node->statement;
      eNode->arg_lhs = node->arg_lhs;
      eNode->arg_rhs = node->arg_rhs;

      // Evaluate the one scope
      Evaluate(eNode, node->children[0]);

      if (eNode->children[0]->result.argument_type ==
              ARGUMENT_TYPE_INTEGER_NUMBER ||
          eNode->children[0]->result.argument_type ==
              ARGUMENT_TYPE_DOUBLE_NUMBER) {
        double lhs_dou = 0;
        double rhs_dou = 0;
        int lhs_int = 0;
        int rhs_int = 0;
        if (eNode->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER ||
            eNode->arg_lhs.argument_type == ARGUMENT_TYPE_DOUBLE_NUMBER) {
          if (eNode->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
            lhs_int = *(int *)(node->arg_lhs.argument_data);
          } else if (eNode->arg_lhs.argument_type ==
                     ARGUMENT_TYPE_DOUBLE_NUMBER) {
            lhs_dou = *(double *)(node->arg_lhs.argument_data);
          }

          if (eNode->children[0]->result.argument_type ==
              ARGUMENT_TYPE_INTEGER_NUMBER) {
            rhs_int = *(int *)(eNode->children[0]->result.argument_data);
          } else if (eNode->children[0]->result.argument_type ==
                     ARGUMENT_TYPE_DOUBLE_NUMBER) {
            rhs_dou = *(double *)(eNode->children[0]->result.argument_data);
          }
        } else if (eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_INTEGER_NUMBER ||
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER) {
          if (node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
            rhs_int = *(int *)(node->arg_rhs.argument_data);
          } else if (node->arg_rhs.argument_type ==
                     ARGUMENT_TYPE_DOUBLE_NUMBER) {
            rhs_dou = *(double *)(node->arg_rhs.argument_data);
          }

          if (eNode->children[0]->result.argument_type ==
              ARGUMENT_TYPE_INTEGER_NUMBER) {
            lhs_int = *(int *)(eNode->children[0]->result.argument_data);
          } else if (eNode->children[0]->result.argument_type ==
                     ARGUMENT_TYPE_DOUBLE_NUMBER) {
            lhs_dou = *(double *)(eNode->children[0]->result.argument_data);
          }
        }

        if (node->statement.statement_sub_type == OPERATOR_TYPE_ADDITION) {
          if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
              node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
            eNode->result.argument_data =
                argument_from_integer_number(lhs_int + rhs_int);
            eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
            printf("%d + %d = %d\n", lhs_int, rhs_int, lhs_int + rhs_int);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_dou + rhs_dou);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%f + %f = %f\n", lhs_dou, rhs_dou, lhs_dou + rhs_dou);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_INTEGER_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_dou + rhs_int);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%f + %d = %f\n", lhs_dou, rhs_int, lhs_dou + rhs_int);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_INTEGER_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_int + rhs_dou);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%d + %f = %f\n", lhs_int, rhs_dou, lhs_int + rhs_dou);
          }
        } else if (node->statement.statement_sub_type ==
                   OPERATOR_TYPE_SUBTRACT) {
          if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
              node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
            eNode->result.argument_data =
                argument_from_integer_number(lhs_int - rhs_int);
            eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
            printf("%d - %d = %d\n", lhs_int, rhs_int, lhs_int - rhs_int);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_dou - rhs_dou);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%f - %f = %f\n", lhs_dou, rhs_dou, lhs_dou - rhs_dou);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_INTEGER_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_dou - rhs_int);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%f - %d = %f\n", lhs_dou, rhs_int, lhs_dou - rhs_int);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_INTEGER_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_int - rhs_dou);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%d - %f = %f\n", lhs_int, rhs_dou, lhs_int - rhs_dou);
          }
        } else if (node->statement.statement_sub_type ==
                   OPERATOR_TYPE_MULTIPLY) {
          if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
              node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
            eNode->result.argument_data =
                argument_from_integer_number(lhs_int * rhs_int);
            eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
            printf("%d * %d = %d\n", lhs_int, rhs_int, lhs_int * rhs_int);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_dou * rhs_dou);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%f * %f = %f\n", lhs_dou, rhs_dou, lhs_dou * rhs_dou);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_INTEGER_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_dou * rhs_int);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%f * %d = %f\n", lhs_dou, rhs_int, lhs_dou * rhs_int);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_INTEGER_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_int * rhs_dou);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%d * %f = %f\n", lhs_int, rhs_dou, lhs_int * rhs_dou);
          }
        } else if (node->statement.statement_sub_type ==
                   OPERATOR_TYPE_DIVISION) {
          if (node->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
              node->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
            eNode->result.argument_data =
                argument_from_integer_number(lhs_int / rhs_int);
            eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
            printf("%d / %d = %d\n", lhs_int, rhs_int, lhs_int / rhs_int);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_dou / rhs_dou);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%f / %f = %f\n", lhs_dou, rhs_dou, lhs_dou / rhs_dou);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_INTEGER_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_dou / rhs_int);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%f / %d = %f\n", lhs_dou, rhs_int, lhs_dou / rhs_int);
          } else if (node->arg_lhs.argument_type ==
                         ARGUMENT_TYPE_INTEGER_NUMBER &&
                     node->arg_rhs.argument_type ==
                         ARGUMENT_TYPE_DOUBLE_NUMBER) {
            eNode->result.argument_data =
                argument_from_double_number(lhs_int / rhs_dou);
            eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
            printf("%d / %f = %f\n", lhs_int, rhs_dou, lhs_int / rhs_dou);
          }
        }
      }
      et_add_child(evalTree, eNode);
      // if (eNode->children[0]->result.argument_type == ARGUMENT_TYPE_FUNCTION
      // ||
      //     eNode->children[1]->result.argument_type == ARGUMENT_TYPE_FUNCTION)
      //     {
      // }
    } else if (node->child_count == 2) {
      EvalTreeNode *eNode = et_create_node();
      eNode->statement = node->statement;
      eNode->arg_lhs = node->arg_lhs;
      eNode->arg_rhs = node->arg_rhs;

      // Evaluate the two scope
      if (node->arg_lhs.argument_type == ARGUMENT_TYPE_FUNCTION &&
          node->arg_rhs.argument_type == ARGUMENT_TYPE_FUNCTION) {
        Evaluate(eNode, node->arg_lhs.argument_node);
        Evaluate(eNode, node->arg_rhs.argument_node);
      } else {
        printf("UNHANDLED");
        return;
      }

      double lhs_dou = 0;
      double rhs_dou = 0;
      int lhs_int = 0;
      int rhs_int = 0;
      if (eNode->children[0]->result.argument_type ==
          ARGUMENT_TYPE_INTEGER_NUMBER) {
        lhs_int = *(int *)(eNode->children[0]->result.argument_data);
      } else if (eNode->children[0]->result.argument_type ==
                 ARGUMENT_TYPE_DOUBLE_NUMBER) {
        lhs_dou = *(double *)(eNode->children[0]->result.argument_data);
      }
      if (eNode->children[1]->result.argument_type ==
          ARGUMENT_TYPE_INTEGER_NUMBER) {
        rhs_int = *(int *)(eNode->children[1]->result.argument_data);
      } else if (eNode->children[1]->result.argument_type ==
                 ARGUMENT_TYPE_DOUBLE_NUMBER) {
        rhs_dou = *(double *)(eNode->children[1]->result.argument_data);
      }

      if (eNode->statement.statement_sub_type == OPERATOR_TYPE_ADDITION) {
        if (eNode->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
            eNode->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
          eNode->result.argument_data =
              argument_from_integer_number(lhs_int + rhs_int);
          eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
          printf("%d + %d = %d\n", lhs_int, rhs_int, lhs_int + rhs_int);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_dou + rhs_dou);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%f + %f = %f\n", lhs_dou, rhs_dou, lhs_dou + rhs_dou);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_INTEGER_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_dou + rhs_int);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%f + %d = %f\n", lhs_dou, rhs_int, lhs_dou + rhs_int);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_INTEGER_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_int + rhs_dou);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%d + %f = %f\n", lhs_int, rhs_dou, lhs_int + rhs_dou);
        }
      } else if (eNode->statement.statement_sub_type ==
                 OPERATOR_TYPE_SUBTRACT) {
        if (eNode->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
            eNode->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
          eNode->result.argument_data =
              argument_from_integer_number(lhs_int - rhs_int);
          eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
          printf("%d - %d = %d\n", lhs_int, rhs_int, lhs_int - rhs_int);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_dou - rhs_dou);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%f - %f = %f\n", lhs_dou, rhs_dou, lhs_dou - rhs_dou);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_INTEGER_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_dou - rhs_int);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%f - %d = %f\n", lhs_dou, rhs_int, lhs_dou - rhs_int);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_INTEGER_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_int - rhs_dou);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%d - %f = %f\n", lhs_int, rhs_dou, lhs_int - rhs_dou);
        }
      } else if (eNode->statement.statement_sub_type ==
                 OPERATOR_TYPE_MULTIPLY) {
        if (eNode->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
            eNode->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
          eNode->result.argument_data =
              argument_from_integer_number(lhs_int * rhs_int);
          eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
          printf("%d * %d = %d\n", lhs_int, rhs_int, lhs_int * rhs_int);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_dou * rhs_dou);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%f * %f = %f\n", lhs_dou, rhs_dou, lhs_dou * rhs_dou);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_INTEGER_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_dou * rhs_int);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%f * %d = %f\n", lhs_dou, rhs_int, lhs_dou * rhs_int);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_INTEGER_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_int * rhs_dou);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%d * %f = %f\n", lhs_int, rhs_dou, lhs_int * rhs_dou);
        }
      } else if (eNode->statement.statement_sub_type ==
                 OPERATOR_TYPE_DIVISION) {
        if (eNode->arg_lhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER &&
            eNode->arg_rhs.argument_type == ARGUMENT_TYPE_INTEGER_NUMBER) {
          eNode->result.argument_data =
              argument_from_integer_number(lhs_int / rhs_int);
          eNode->result.argument_type = ARGUMENT_TYPE_INTEGER_NUMBER;
          printf("%d / %d = %d\n", lhs_int, rhs_int, lhs_int / rhs_int);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_dou / rhs_dou);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%f / %f = %f\n", lhs_dou, rhs_dou, lhs_dou / rhs_dou);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_INTEGER_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_dou / rhs_int);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%f / %d = %f\n", lhs_dou, rhs_int, lhs_dou / rhs_int);
        } else if (eNode->arg_lhs.argument_type ==
                       ARGUMENT_TYPE_INTEGER_NUMBER &&
                   eNode->arg_rhs.argument_type ==
                       ARGUMENT_TYPE_DOUBLE_NUMBER) {
          eNode->result.argument_data =
              argument_from_double_number(lhs_int / rhs_dou);
          eNode->result.argument_type = ARGUMENT_TYPE_DOUBLE_NUMBER;
          printf("%d / %f = %f\n", lhs_int, rhs_dou, lhs_int / rhs_dou);
        }
      }

      et_add_child(evalTree, eNode);
    }
  }
}
