#include "test/test_common_str.h"

#include "common/allocator_cbs.h"
#include "common/str.h"
#include "common/log.h"

#include <unistd.h>
#include <assert.h>


/*
bool str_valid(str str);
bool str_match(str a, str b);
bool str_contains(str haystack, str needle);
str str_sub(str src, size_t begin, size_t end);
str str_find_first(str haystack, str needle);
str str_find_last(str haystack, str needle);
str str_remove_prefix(str src, str prefix);
str str_remove_suffix(str src, str suffix);
*/
//--------------------------------------------------
void _test_str_valid()
{
 struct str str = {};
 assert(!str_valid(str));

 str = cstr("Hey");
 assert(str_valid(str));
}

//--------------------------------------------------
void _test_str_match()
{
 struct str str1 = cstr("test");
 struct str str2 = cstr("test");

 assert(str_match(str1, str2));

 struct str str = {};
 assert(!str_match(str, str2));

 str2 = cstr("est");
 assert(!str_match(str1, str2));
}

//--------------------------------------------------
void _test_str_contains()
{
 struct str big = cstr("big small");
 struct str small = cstr("small");

 assert(str_contains(big, small));
 assert(!str_contains(small, big));
}
 
//--------------------------------------------------
void _test_str_sub()
{
 struct str str1 = cstr("heyaaa");

 assert(str_match(cstr("hey"), str_sub(str1,0,3)));
 assert(str_match(cstr("aaa"), str_sub(str1,3,6)));

 struct str ret = str_sub(str1,3,1);
 assert(!str_valid(ret));

 ret = str_sub(str1, 1, 8);
 assert(!str_valid(ret));

 ret = str_sub(str1, 2, 1);
 assert(!str_valid(ret));

 ret = str_sub(str1, 1, 1);
 assert(!str_valid(ret));
}
 
//--------------------------------------------------
void _test_str_find_first()
{
 LOG_ERROR("unimplemented");
 assert(0);
}
 
//--------------------------------------------------
void _test_str_find_last()
{
 LOG_ERROR("unimplemented");
 assert(0);
}
 
//--------------------------------------------------
void _test_str_remove_prefix()
{
 LOG_ERROR("unimplemented");
 assert(0);
}
 
//--------------------------------------------------
void _test_str_remove_suffix()
{
 LOG_ERROR("unimplemented");
 assert(0);
}

//--------------------------------------------------
void test_common_str_run(struct allocator_cbs allocator)
{
 _test_str_valid();
 _test_str_match();
 _test_str_contains();
 _test_str_sub();
 //_test_str_find_first();
 //_test_str_find_last();
 //_test_str_remove_prefix();
 //_test_str_remove_suffix();
}
