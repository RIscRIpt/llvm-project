// RUN: %clang_cc1 -fms-extensions -DMSX -ast-dump %s | FileCheck %s
// RUN: not %clang_cc1 -Werror=ignored-attributes -ast-dump %s 2>&1 | grep "5 errors generated"

// CHECK: VarDecl 0x{{[0-9a-f]+}} <{{.*}}:[[@LINE+3]]:24, col:47> col:47 no_tls_guard_var
// CHECK-NEXT: MSNoTlsGuardAttr 0x{{[0-9a-f]+}} <col:3, col:9>
// CHECK-NEXT: ThreadAttr 0x{{[0-9a-f]+}} <col:35>
[[msvc::no_tls_guard]] __declspec(thread) int no_tls_guard_var;

// CHECK: MSKnownSemanticsAttr 0x{{[0-9a-f]+}} <col:10, col:16>
// CHECK-NEXT: CXXRecordDecl 0x{{[0-9a-f]+}} <col:1, col:34> col:34
struct [[msvc::known_semantics]] Struct {};

// CHECK: TypeAliasDecl 0x{{[0-9a-f]+}} <line:[[@LINE+3]]:1, col:39> col:7 Int 'int'
// CHECK-NEXT: BuiltinType 0x{{[0-9a-f]+}} 'int'
// CHECK-NEXT: MSKnownSemanticsAttr 0x{{[0-9a-f]+}} <col:13, col:19>
using Int [[msvc::known_semantics]] = int;

struct Dtor {
  // CHECK: CXXDestructorDecl 0x{{[0-9a-f]+}} <line:[[@LINE+3]]:23, col:32> col:23 ~Dtor 'void () noexcept'
  // CHECK-NEXT: CompoundStmt 0x{{[0-9a-f]+}} <col:31, col:32>
  // CHECK-NEXT: MSNoopDtorAttr 0x{{[0-9a-f]+}} <col:5, col:11>
  [[msvc::noop_dtor]] ~Dtor() {}
};
