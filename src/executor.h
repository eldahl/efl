#pragma once

#include "tree.h"

void Evaluate(ParsingTreeNode* node, int depth) {

	if (node->statement.statement_type == STATEMENT_TYPE_SCOPE) {

	}
	else if (node->statement.statement_type == STATEMENT_TYPE_OPERATOR) {

		if (node->statement.statement_sub_type == OPERATOR_TYPE_ADDITION) {

		}
		else if (node->statement.statement_sub_type == OPERATOR_TYPE_SUBTRACT) {

		}
		else if (node->statement.statement_sub_type == OPERATOR_TYPE_MULTIPLY) {

		}
		else if (node->statement.statement_sub_type == OPERATOR_TYPE_DIVISION) {

		}
	}
}
