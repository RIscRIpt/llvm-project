// RUN: %clang_cc1 %s -fsyntax-only -Wmicrosoft -verify -fms-extensions

using size_t = __SIZE_TYPE__;

void f() {
 const char a[] = __FUNCTION__; // expected-warning{{initializing an array from a '__FUNCTION__' predefined identifier is a Microsoft extension}}
 const char b[] = __FUNCDNAME__; // expected-warning{{initializing an array from a '__FUNCDNAME__' predefined identifier is a Microsoft extension}}
 const char c[] = __FUNCSIG__; // expected-warning{{initializing an array from a '__FUNCSIG__' predefined identifier is a Microsoft extension}}
 const char d[] = __func__; // expected-warning{{initializing an array from a '__func__' predefined identifier is a Microsoft extension}}
 const char e[] = __PRETTY_FUNCTION__; // expected-warning{{initializing an array from a '__PRETTY_FUNCTION__' predefined identifier is a Microsoft extension}}
 const wchar_t f[] = L__FUNCTION__; // expected-warning{{initializing an array from a 'L__FUNCTION__' predefined identifier is a Microsoft extension}}
 const wchar_t g[] = L__FUNCSIG__; // expected-warning{{initializing an array from a 'L__FUNCSIG__' predefined identifier is a Microsoft extension}}
}

// Test concatenation

void eat_const_char_p(const char*);
void eat_const_wchar_p(const wchar_t*);

void test_concat() {
  eat_const_char_p("s" __FUNCTION__); // expected-warning{{concatenation of predefined identifier '__FUNCTION__' is a Microsoft extension}}
  eat_const_char_p("s" __FUNCDNAME__); // expected-warning{{concatenation of predefined identifier '__FUNCDNAME__' is a Microsoft extension}}
  eat_const_char_p("s" __FUNCSIG__); // expected-warning{{concatenation of predefined identifier '__FUNCSIG__' is a Microsoft extension}}

  eat_const_char_p(__FUNCTION__ "s"); // expected-warning{{concatenation of predefined identifier '__FUNCTION__' is a Microsoft extension}}
  eat_const_char_p(__FUNCDNAME__ "s"); // expected-warning{{concatenation of predefined identifier '__FUNCDNAME__' is a Microsoft extension}}
  eat_const_char_p(__FUNCSIG__ "s"); // expected-warning{{concatenation of predefined identifier '__FUNCSIG__' is a Microsoft extension}}

  eat_const_char_p("s" __FUNCTION__ "s"); // expected-warning{{concatenation of predefined identifier '__FUNCTION__' is a Microsoft extension}}
  eat_const_char_p("s" __FUNCDNAME__ "s"); // expected-warning{{concatenation of predefined identifier '__FUNCDNAME__' is a Microsoft extension}}
  eat_const_char_p("s" __FUNCSIG__ "s"); // expected-warning{{concatenation of predefined identifier '__FUNCSIG__' is a Microsoft extension}}
}

void test_wide_concat() {
  eat_const_wchar_p(L"s" L__FUNCTION__); // expected-warning{{concatenation of predefined identifier 'L__FUNCTION__' is a Microsoft extension}}
  eat_const_wchar_p(L"s" L__FUNCSIG__); // expected-warning{{concatenation of predefined identifier 'L__FUNCSIG__' is a Microsoft extension}}

  eat_const_wchar_p(L__FUNCTION__ L"s"); // expected-warning{{concatenation of predefined identifier 'L__FUNCTION__' is a Microsoft extension}}
  eat_const_wchar_p(L__FUNCSIG__ L"s"); // expected-warning{{concatenation of predefined identifier 'L__FUNCSIG__' is a Microsoft extension}}

  eat_const_wchar_p(L"s" L__FUNCTION__ L"s"); // expected-warning{{concatenation of predefined identifier 'L__FUNCTION__' is a Microsoft extension}}
  eat_const_wchar_p(L"s" L__FUNCSIG__ L"s"); // expected-warning{{concatenation of predefined identifier 'L__FUNCSIG__' is a Microsoft extension}}
}

const char* test_return() {
  return __FUNCTION__ "s" __FUNCSIG__; // expected-warning{{concatenation of predefined identifier '__FUNCTION__' is a Microsoft extension}} \
                                       // expected-warning{{concatenation of predefined identifier '__FUNCSIG__' is a Microsoft extension}}
}

void test_struct_init_fn() {
  struct test_struct_init {
    const char* str;
  } struct_init = { "struct: " __FUNCSIG__ }; // expected-warning{{concatenation of predefined identifier '__FUNCSIG__' is a Microsoft extension}}
}

constexpr size_t operator""_len(const char*, size_t len) {
    return len;
}

void test_udliteral() {
    static_assert(__FUNCTION__ ""_len == 14); // expected-warning{{concatenation of predefined identifier '__FUNCTION__' is a Microsoft extension}}
}
