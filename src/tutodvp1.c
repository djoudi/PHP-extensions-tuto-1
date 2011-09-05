/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: julien PAULI (jpauli@php.net)                                |
  +----------------------------------------------------------------------+
*/

/* $Id: header 252479 2008-02-07 19:39:50Z iliaa $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_tutodvp1.h"

/* ZEND_DECLARE_MODULE_GLOBALS(tutodvp1) */

/* True global resources - no need for thread safety here */
static int le_tutodvp1;

ZEND_BEGIN_ARG_INFO(arginfo_jp_add_underscores, 0)
    ZEND_ARG_INFO(1, str)
ZEND_END_ARG_INFO();

PHP_INI_MH(OnUpdateNumUnderscores)
{
    if (new_value_length == 0) {
        return FAILURE;
    }

}

/* php.ini entries */
PHP_INI_BEGIN()
PHP_INI_ENTRY("jp.num_underscores", JP_NUM_UNDERSCORES_DEFAULT, PHP_INI_ALL, OnUpdateNumUnderscores)
PHP_INI_END()

/* {{{ tutodvp1_functions[]
 *
 * Every user visible function must have an entry in tutodvp1_functions[].
 */
const zend_function_entry tutodvp1_functions[] = {
    PHP_FE(jp_set_include_path,     NULL)
    PHP_FE(jp_add_underscores, arginfo_jp_add_underscores)
    {NULL, NULL, NULL}      /* Must be the last line in tutodvp1_functions[] */
};
/* }}} */

/* {{{ tutodvp1_module_entry
 */
zend_module_entry tutodvp1_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "tutodvp1",
    tutodvp1_functions,
    PHP_MINIT(tutodvp1),
    PHP_MSHUTDOWN(tutodvp1),
    PHP_RINIT(tutodvp1),            /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(tutodvp1),        /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(tutodvp1),
#if ZEND_MODULE_API_NO >= 20010901
    "0.1", /* Replace with version number for your extension */
#endif
        STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_tutodvp1
ZEND_GET_MODULE(tutodvp1)
#endif

/* {{{ php_tutodvp1_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_tutodvp1_init_globals(zend_tutodvp1_globals *tutodvp1_globals)
{
        tutodvp1_globals->global_value = 0;
        tutodvp1_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(tutodvp1)
{
    REGISTER_INI_ENTRIES();

    REGISTER_LONG_CONSTANT("INCLUDE_PATH_APPEND", 0, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("INCLUDE_PATH_PREPEND", 1, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("INCLUDE_PATH_REPLACE", 2, CONST_CS | CONST_PERSISTENT);
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(tutodvp1)
{
    UNREGISTER_INI_ENTRIES();
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(tutodvp1)
{
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(tutodvp1)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(tutodvp1)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "tutodvp1 support", "enabled");
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}
/* }}} */

/*
 * looks for needle in haystack at pos at_pos
 * at_pos = 0 for the first occurence
 * at_pos = 1 for the last occurence
 *
 */
static short at_pos(const char* haystack, const char* needle, short pos_type)
{
    char *result;
    result = pos_type ? strrstr(haystack, needle) : strstr(haystack, needle);
    if(!result) {
        return 0;
    }
    if (pos_type) {
        return strlen(haystack) - (int)(result-haystack) == strlen(needle);
    } else {
        return haystack == result;
    }
}

/*
 * strrstr implementation
 */
static char* strrstr(const char* haystack, const char* needle)
{
    char *r = NULL;

    if (!needle[0]) {
        return 0;
    }

    while (1) {
        char *p = strstr(haystack, needle);
        if (!p) {
            return r;
        }
        r = p;
        haystack = p + 1;
    }
}

/* {{{ proto string jp_set_include_path(string arg, int path_type) */
PHP_FUNCTION(jp_set_include_path)
{
    char *new_value, *new_include_path, *old_value, *path_separator;
    int new_value_len;
    zval *z_path_separator;
    long options = INCLUDE_PATH_REPLACE;
    int i;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &new_value, &new_value_len, &options) == FAILURE) {
        return;
    }

    MAKE_STD_ZVAL(z_path_separator);

    old_value = INI_STR("include_path");
    if (old_value) {
        RETVAL_STRING(old_value, 1);
    } else {
        RETVAL_FALSE;
    }

        if (zend_get_constant("PATH_SEPARATOR", sizeof("PATH_SEPARATOR")-1, z_path_separator)) {
            path_separator = Z_STRVAL_P(z_path_separator);
        } else {
            zval_ptr_dtor(&z_path_separator);
            zend_error(E_ERROR, "Could not find PATH_SEPARATOR constant");
        }

        switch (options) {
        case INCLUDE_PATH_REPLACE:
            new_include_path = (char*) ecalloc(sizeof(char), new_value_len + 1);
            snprintf(new_include_path, new_value_len + 1, "%s", new_value);
        break;

        case INCLUDE_PATH_APPEND:
            i = new_value_len + strlen(old_value) + Z_STRLEN_P(z_path_separator) + 1 /* ending \0 */;
            if (!IS_LAST_CHAR(old_value, path_separator)) {
                new_include_path = (char*) ecalloc(sizeof(char), i);
                snprintf(new_include_path, i, "%s%s%s", old_value, path_separator, new_value);
            } else {
                i-= Z_STRLEN_P(z_path_separator); /* path_separator is not included, get it out of buffer length */
                new_include_path = (char*) ecalloc(sizeof(char), i);
                snprintf(new_include_path, i, "%s%s", old_value, new_value);
            }
        break;

        case INCLUDE_PATH_PREPEND:
            i = new_value_len + strlen(old_value) + Z_STRLEN_P(z_path_separator) + 1 /* ending \0 */;
            if (!IS_FIRST_CHAR(old_value, path_separator)) {
                new_include_path = (char*) ecalloc(sizeof(char), i);
                snprintf(new_include_path, i, "%s%s%s", new_value, path_separator, old_value);
            } else {
                i-= Z_STRLEN_P(z_path_separator); /* path_separator is not included, get it out of buffer length */
                new_include_path = (char*) ecalloc(sizeof(char), i);
                snprintf(new_include_path, i, "%s%s", new_value, old_value);
            }
        break;
    }
        if (zend_alter_ini_entry_ex("include_path", sizeof("include_path"), new_include_path, strlen(new_include_path), PHP_INI_USER, PHP_INI_STAGE_RUNTIME, 0 TSRMLS_CC) == FAILURE) {
            zval_ptr_dtor(&return_value);
            efree(new_include_path);
            zval_ptr_dtor(&z_path_separator);
            RETURN_FALSE;
        }
        efree(new_include_path);
        zval_ptr_dtor(&z_path_separator);
}

PHP_FUNCTION(jp_add_underscores)
{
    int i, j, string_len, num_underscores = 0;
    zval *thestring;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &thestring, &num_underscores) == FAILURE) {
        return;
    }

    if (ZEND_NUM_ARGS() == 1) {
        num_underscores = INI_INT("jp.num_underscores");
    }

    if(num_underscores <= 0) {
        zend_error(E_WARNING, "num_underscores cannot be negative");
        return;
    }

    string_len = Z_STRLEN_P(thestring);

    Z_STRLEN_P(thestring) += 2 * num_underscores;
    Z_STRVAL_P(thestring) = (char *)erealloc(Z_STRVAL_P(thestring), Z_STRLEN_P(thestring) * sizeof(char) + 1);

    for (i = string_len; i >= 0; i--) { /* Center the string in buffer */
        Z_STRVAL_P(thestring)[i + num_underscores] = Z_STRVAL_P(thestring)[i];
    }

    for(i = 0; i < num_underscores; i++) { /* Add leading and trailing underscores */
        Z_STRVAL_P(thestring)[i] = Z_STRVAL_P(thestring)[i + string_len + num_underscores] = '_';
    }

    Z_STRVAL_P(thestring)[Z_STRLEN_P(thestring)] = '\0';
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
