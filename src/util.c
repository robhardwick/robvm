#include "robvm.h"

const char *log_types[] = {
    "debug",
    "info",
    "warn",
    "error",
};

/**
 * Output log message
 */
void rvm_log(unsigned int type, const char *fmt, ...) {
    fprintf(stderr, "[%s] ", log_types[type]);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);
}

/**
 * Check if a string is empty (only contains whitespace)
 */
bool rvm_empty_string(char *s) {
    while (*s) {
        if (!isspace(*s)) {
            return false;
        }
        s++;
    }
    return true;
}

/**
 * Return value as string
 */
char *rvm_value_string(rvm_value_t *value) {
    switch (value->type) {
        case RVM_TYPE_IDENTIFIER:
        case RVM_TYPE_STRING:
            return value->v.s;

        case RVM_TYPE_INTEGER:
            return talloc_asprintf(value, "%ld", value->v.i);

        case RVM_TYPE_FLOAT:
            return talloc_asprintf(value, "%g", value->v.f);
    }
    return "NULL";
}
