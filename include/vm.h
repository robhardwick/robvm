#ifndef ROBVM_VM_H
#define ROBVM_VM_H

/**
 * VM Stack
 */
struct _rvm_vm_stack_t {
    rvm_value_t *value;
    rvm_vm_stack_t *next;
};

/**
 * VM Symbol Table
 */
struct _rvm_vm_sym_node_t {
    char *key;
    rvm_value_t *value;
    struct _rvm_vm_sym_node_t *next;
};
typedef struct _rvm_vm_sym_node_t rvm_vm_sym_node_t;

struct _rvm_vm_sym_t {
    rvm_vm_sym_node_t **table;
    unsigned long size;
};

/**
 * VM
 */
struct _rvm_vm_t {
    rvm_vm_stack_t *stack;
    rvm_vm_sym_t *sym;
    unsigned int depth;
};

#endif
