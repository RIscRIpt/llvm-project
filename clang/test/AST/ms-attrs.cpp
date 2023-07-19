// RUN: %clang_cc1 -fms-compatibility -fms-compatibility-version=19.33 -std=c++20 -ast-dump -verify %s | FileCheck %s
// expected-no-diagnostics

// [[msvc::constexpr]] tests

// MSConstexprDocs (1)
// CHECK: used f1 'bool ()'
// CHECK: MSConstexprAttr 0x{{[0-9a-f]+}} <col:3, col:9>
[[msvc::constexpr]] bool f1() { return true; }

// MSConstexprDocs (2)
// CHECK: used constexpr f2 'bool ()'
// CHECK: AttributedStmt 0x{{[0-9a-f]+}} <col:23, col:53>
// CHECK-NEXT: MSConstexprAttr 0x{{[0-9a-f]+}} <col:25, col:31>
// CHECK-NEXT: ReturnStmt 0x{{[0-9a-f]+}} <col:43, col:53>
constexpr bool f2() { [[msvc::constexpr]] return f1(); }

static_assert(f2());

constexpr bool f3() { [[msvc::constexpr]] return f1() || f1() && f1(); }
static_assert(f3());

[[msvc::constexpr]] int f4(int x) { [[msvc::constexpr]] return x > 1 ? 1 + f4(x / 2) : 0; }
constexpr bool f5() { [[msvc::constexpr]] return f4(32) == 5; }
static_assert(f5());

[[msvc::constexpr]] int f6(int x)
{
    switch (x)
    {
        case 42: return 1337;
        default:
                 if (x < 0) [[msvc::constexpr]] return f4(-x);
                 else return x;
    }
}

constexpr bool f7() { [[msvc::constexpr]] return f6(f6(42) - 1337 + f6(-32) - 5 + (f6(1) ? f6(0) : f6(2))) == f6(0); }
static_assert(f7());

constexpr bool f8() { return true; }
[[msvc::constexpr]] bool f9() { return f8(); }
constexpr bool f10() { [[msvc::constexpr]] return f9(); }
static_assert(f10());

struct S1 {
    [[msvc::constexpr]] virtual bool vm() { return true; }
    constexpr bool cm() { [[msvc::constexpr]] return vm(); }
};
static_assert(S1{}.cm());

/*
// TODO: Add support for [[msvc::constexpr]] constructor
struct S2 {
    [[msvc::constexpr]] S2() {}
    [[msvc::constexpr]] bool value() { return true; }
    static constexpr bool check() { [[msvc::constexpr]] return S2{}.value(); }
};
static_assert(S2::check());
*/
