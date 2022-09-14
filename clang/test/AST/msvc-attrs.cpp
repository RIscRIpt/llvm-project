// RUN: %clang_cc1 -fms-extensions -DMSX -ast-dump %s | FileCheck %s
// RUN: not %clang_cc1 -Werror=ignored-attributes -ast-dump %s 2>&1 | grep "2 errors generated"

// CHECK: VarDecl 0x{{[0-9a-f]+}} <{{.*}}:[[@LINE+3]]:24, col:47> col:47 no_tls_guard_var
// CHECK-NEXT: MSNoTlsGuardAttr 0x{{[0-9a-f]+}} <col:3, col:9>
// CHECK-NEXT: ThreadAttr 0x{{[0-9a-f]+}} <col:35>
[[msvc::no_tls_guard]] __declspec(thread) int no_tls_guard_var;
