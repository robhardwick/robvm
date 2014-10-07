#ifndef ROBVM_AST_H
#define ROBVM_AST_H

/**
 * AST
 */
struct _rvm_ast_node_t {
    unsigned int type;
    rvm_value_t *value;
    rvm_ast_node_t *next;
    rvm_ast_node_t *children;
};

#endif
