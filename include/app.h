#ifndef RVM_APP_H
#define RVM_APP_H

struct _rvm_app_t {
    rvm_ast_node_t *root;
    rvm_vm_t *vm;
};

#endif
