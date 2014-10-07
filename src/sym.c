#include "robvm.h"
#include "vm.h"

/**
 * Implementation of djb2 hash function
 */
unsigned long _rvm_vm_sym_hash(char *key) {
    unsigned long hash = 5381; // Magic
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % RVM_SYM_SIZE;
}

rvm_vm_sym_t *rvm_vm_sym_init(TALLOC_CTX *ctx, unsigned long size) {
    rvm_vm_sym_t *sym = talloc(ctx, rvm_vm_sym_t);
    if (!sym) {
        return NULL;
    }
    sym->size = size;
    sym->table = talloc_size(sym, sizeof(rvm_vm_sym_node_t) * size);
    if (!sym->table) {
        return NULL;
    }
    return sym;
}

rvm_value_t *rvm_vm_sym_get(rvm_vm_sym_t *sym, char *key) {
    if (!sym) {
        return NULL;
    }
    unsigned long idx = _rvm_vm_sym_hash(key);
    rvm_vm_sym_node_t *node = sym->table[idx];
    while (node) {
        if (strncmp(key, node->key, RVM_MAX_IDENT_LEN) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

bool rvm_vm_sym_put(rvm_vm_sym_t *sym, char *key, rvm_value_t *value) {
    if (!sym) {
        return false;
    }
    unsigned long idx = _rvm_vm_sym_hash(key);
    rvm_vm_sym_node_t *node = talloc(sym, rvm_vm_sym_node_t);
    node->value = value;
    node->key = talloc_strndup(sym, key, RVM_MAX_IDENT_LEN);
    node->next = sym->table[idx];
    sym->table[idx] = node;
    return true;
}

bool rvm_vm_sym_remove(rvm_vm_sym_t *sym, char *key) {
    if (!sym) {
        return false;
    }

    unsigned long idx = _rvm_vm_sym_hash(key);
    rvm_vm_sym_node_t *p = NULL,
                      *n = sym->table[idx];

    while (n) {
        if (strncmp(key, n->key, RVM_MAX_IDENT_LEN) == 0) {
            if (p) {
                p->next = n->next;
            }
            talloc_free(n->key);
            n->key = NULL;

            if (sym->table[idx] == n) {
                sym->table[idx] = NULL;
            }
            talloc_free(n);
            n = NULL;
            return true;
        }
        p = n;
        n = n->next;
    }
    return false;
}
