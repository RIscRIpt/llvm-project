// RUN: %clang_cc1 -fms-extensions -fc++-abi=microsoft -triple=x86_64-pc-windows-msvc -std=c++20 -ast-dump %s | FileCheck %s
// RUN: not %clang_cc1 -Werror=ignored-attributes -ast-dump %s 2> %t.stderr.txt
// RUN: FileCheck -check-prefix CHECK-DIAG-NO-MSX %s < %t.stderr.txt

struct Empty {};

struct StructWithNUAField {
  // CHECK: FieldDecl 0x{{[0-9a-f]+}} <line:[[@LINE+2]]:31, col:37> col:37 e 'Empty':'Empty'
  // CHECK-NEXT: MSNoUniqueAddressAttr
  [[msvc::no_unique_address]] Empty e;
  int f1;
};

// CHECK-DIAG-NO-MSX: msvc-attrs.cpp:[[@LINE+1]]:1: error: static assertion failed due to requirement 'sizeof(StructWithNUAField) == sizeof(int)' 
static_assert(sizeof(StructWithNUAField) == sizeof(int));
