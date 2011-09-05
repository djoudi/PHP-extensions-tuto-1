<?php

assert(function_exists('jp_set_include_path')) or exit();
assert(function_exists('jp_add_underscores')) or exit();

set_include_path('');
jp_set_include_path('foo');
/* or jp_set_include_path('foo', INCLUDE_PATH_OVERWRITE); */
assert(get_include_path() == 'foo');

jp_set_include_path('bar', INCLUDE_PATH_APPEND);
assert(get_include_path() == 'foo:bar');

jp_set_include_path('baz', INCLUDE_PATH_PREPEND);
assert(get_include_path() == 'baz:foo:bar');

assert(jp_set_include_path('') == 'baz:foo:bar');


assert(ini_get('jp.num_underscores') == 2);

$str = "foobar";
jp_add_underscores($str);
assert($str == '__foobar__');

$str2 = 'baz';
jp_add_underscores($str2, 4);
assert($str2 == '____baz____');