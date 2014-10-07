#include "robvm.h"
#include "ast.h"
#include "vm.h"

#define RVM_TAB_WIDTH   2
#define RVM_WHITESPACE  "                                "

const char *node_types[] = {
    "UNKNOWN",
    "ROOT",
    "IDENTIFIER",
    "STRING",
    "INTEGER",
    "FLOAT",
    "ASSIGN",
    "ADD",
    "SUBTRACT",
    "MULTIPLY",
    "DIVIDE",
};

/**
 * Create VM object
 */
rvm_vm_t *rvm_vm_init(TALLOC_CTX *ctx) {
    rvm_vm_t *vm = talloc(ctx, rvm_vm_t);
    if (!vm) {
        return NULL;
    }

    vm->sym = rvm_vm_sym_init(vm, RVM_SYM_SIZE);
    if (!vm->sym) {
        return NULL;
    }

    vm->stack = NULL;
    vm->depth = 0;
    return vm;
}

/**
 * Execute AST node
 */
bool _rvm_vm_execute_node(rvm_vm_t *vm, rvm_ast_node_t *node) {
    if (!node) {
        return true;
    }

    // Debug
    PDEBUG("%.*s%s (0x%X): %s",
        vm->depth * RVM_TAB_WIDTH, RVM_WHITESPACE,
        node_types[node->type],
        node->type,
        rvm_value_string(node->value)
    );

    // Process children
    vm->depth++;
    if (!_rvm_vm_execute_node(vm, node->children)) {
        return false;
    }
    vm->depth--;

    // Execute
    switch (node->type) {

        // Push identifier/value on stack
        case RVM_AST_IDENTIFIER:
        case RVM_AST_STRING:
        case RVM_AST_INTEGER:
        case RVM_AST_FLOAT:
            if (!rvm_vm_stack_push(vm, node->value)) {
                rvm_log(RVM_LOG_WARN, "Unable to push value onto stack");
                return false;
            }
            break;

        // Perform numerical addition
        case RVM_AST_ADD:
            break;

        // TODO
        case RVM_AST_SUBTRACT:
        case RVM_AST_MULTIPLY:
        case RVM_AST_DIVIDE:
            break;

        // Assign value to an identifier
        case RVM_AST_ASSIGN: {
            rvm_vm_stack_t *value = rvm_vm_stack_pop(vm),
                           *id = rvm_vm_stack_pop(vm);

            if (!value) {
                rvm_log(RVM_LOG_WARN, "No value in assignment statement");
                return false;
            } else if (!id) {
                rvm_log(RVM_LOG_WARN, "No lvalue in assignment statement");
                return false;
            } else if (id->value->type != RVM_TYPE_IDENTIFIER) {
                rvm_log(RVM_LOG_WARN, "Non-identifier lvalue used in assignment");
                return false;
            }

            if (!rvm_vm_sym_put(vm->sym, id->value->v.s, value->value)) {
                return false;
            }

            PDEBUG("[VM] %s = %s",
                rvm_value_string(id->value),
                rvm_value_string(value->value)
            );
            break;
         }

        case RVM_AST_ROOT:
            PDEBUG("[ROOT]");
            //rvm_vm_stack_t *value = rvm_vm_stack_pop(v);
            break;

        default:
            // Unknown node type
            rvm_log(RVM_LOG_ERR, "Unknown node type (0x%X)", node->type);
            return false;

    }

    // Process siblings
    return _rvm_vm_execute_node(vm, node->next);
}

/**
 * Execute AST node tree
 */
bool rvm_vm_execute(rvm_vm_t *vm, rvm_ast_node_t *root) {
    vm->depth = 0;
    return _rvm_vm_execute_node(vm, root);
}
