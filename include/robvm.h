#ifndef ROBVM_H
#define ROBVM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <talloc.h>

/**
 * Constants
 */
#define RVM_NAME            "rvm"

#define RVM_LOG_DEBUG       0x00
#define RVM_LOG_INFO        0x01
#define RVM_LOG_WARN        0x02
#define RVM_LOG_ERR         0x03

#define RVM_AST_ROOT        0x01
#define RVM_AST_IDENTIFIER  0x02
#define RVM_AST_STRING      0x03
#define RVM_AST_INTEGER     0x04
#define RVM_AST_FLOAT       0x05
#define RVM_AST_ASSIGN      0x06
#define RVM_AST_ADD         0x07
#define RVM_AST_SUBTRACT    0x08
#define RVM_AST_MULTIPLY    0x09
#define RVM_AST_DIVIDE      0x0A

#define RVM_TYPE_IDENTIFIER 0x01
#define RVM_TYPE_STRING     0x02
#define RVM_TYPE_INTEGER    0x03
#define RVM_TYPE_FLOAT      0x04

#define RVM_SYM_SIZE        64
#define RVM_MAX_IDENT_LEN   32

/**
 * Macros
 */
#ifdef DEBUG
#define PDEBUG(...) rvm_log(RVM_LOG_DEBUG, __VA_ARGS__)
#else
#define PDEBUG(...)
#endif

/**
 * Value type
 */
typedef struct {
    unsigned int type;
    union {
        long i;
        double f;
        char *s;
    } v;
} rvm_value_t;

/**
 * AST
 */
typedef struct _rvm_ast_node_t rvm_ast_node_t;

rvm_ast_node_t *rvm_ast_init(TALLOC_CTX *ctx, unsigned int type, char *value);
void rvm_ast_append(rvm_ast_node_t *parent, rvm_ast_node_t *node);

/**
 * VM
 */
typedef struct _rvm_vm_t rvm_vm_t;

rvm_vm_t *rvm_vm_init(TALLOC_CTX *ctx);
bool rvm_vm_execute(rvm_vm_t *vm, rvm_ast_node_t *root);

/**
 * VM Stack
 */
typedef struct _rvm_vm_stack_t rvm_vm_stack_t;

bool rvm_vm_stack_push(rvm_vm_t *vm, rvm_value_t *value);
rvm_vm_stack_t *rvm_vm_stack_pop(rvm_vm_t *vm);

/**
 * VM Symbol Table
 */
typedef struct _rvm_vm_sym_t rvm_vm_sym_t;

rvm_vm_sym_t *rvm_vm_sym_init(TALLOC_CTX *ctx, unsigned long size);
rvm_value_t *rvm_vm_sym_get(rvm_vm_sym_t *sym, char *key);
bool rvm_vm_sym_put(rvm_vm_sym_t *sym, char *key, rvm_value_t *value);
bool rvm_vm_sym_remove(rvm_vm_sym_t *sym, char *key);

/**
 * App
 */
typedef struct _rvm_app_t rvm_app_t;

rvm_app_t *rvm_app_init(void);
bool rvm_app_interactive(rvm_app_t *app);
bool rvm_app_file(rvm_app_t *app, char *filename);
void rvm_app_free(rvm_app_t *app);

/**
 * Util
 */
void rvm_log(unsigned int type, const char *fmt, ...);
bool rvm_empty_string(char *s);
char *rvm_value_string(rvm_value_t *value);

#endif
