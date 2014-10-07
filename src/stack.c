#include "robvm.h"
#include "ast.h"
#include "vm.h"

/**
 * Push stack
 */
bool rvm_vm_stack_push(rvm_vm_t *vm, rvm_value_t *value) {
    rvm_vm_stack_t *item = talloc(vm, rvm_vm_stack_t);
    if (!item) {
        return false;
    }
    item->value = value;
    item->next = vm->stack;
    vm->stack = item;
    return true;
}

/**
 * Pop stack
 */
rvm_vm_stack_t *rvm_vm_stack_pop(rvm_vm_t *vm) {
    rvm_vm_stack_t *item = vm->stack;
    if (vm->stack != NULL) {
        vm->stack = vm->stack->next;
    }
    return item;
}
