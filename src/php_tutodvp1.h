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

#ifndef PHP_tutodvp1_H
#define PHP_tutodvp1_H

extern zend_module_entry tutodvp1_module_entry;
#define phpext_tutodvp1_ptr &tutodvp1_module_entry

#ifdef PHP_WIN32
#	define PHP_tutodvp1_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_tutodvp1_API __attribute__ ((visibility("default")))
#else
#	define PHP_tutodvp1_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(tutodvp1);
PHP_MSHUTDOWN_FUNCTION(tutodvp1);
PHP_RINIT_FUNCTION(tutodvp1);
PHP_RSHUTDOWN_FUNCTION(tutodvp1);
PHP_MINFO_FUNCTION(tutodvp1);

static char* strrstr(const char* haystack, const char* needle);
static short at_pos(const char* haystack, const char* needle, short pos);

#define IS_FIRST_CHAR(haystack, needle) at_pos(haystack, needle, 0)
#define IS_LAST_CHAR(haystack, needle) at_pos(haystack, needle, 1)


PHP_FUNCTION(jp_set_include_path);
PHP_FUNCTION(jp_add_underscores);

#define INCLUDE_PATH_APPEND  (0)
#define INCLUDE_PATH_PREPEND (1)
#define INCLUDE_PATH_REPLACE (2)

#define JP_NUM_UNDERSCORES_DEFAULT ("2")
/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(tutodvp1)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(tutodvp1)
*/

/* In every utility function you add that needs to use variables 
   in php_tutodvp1_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as tutodvp1_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define tutodvp1_G(v) TSRMG(tutodvp1_globals_id, zend_tutodvp1_globals *, v)
#else
#define tutodvp1_G(v) (tutodvp1_globals.v)
#endif

#endif	/* PHP_tutodvp1_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
