// RUN: %clang_cc1 -fno-rtti -emit-llvm-only -triple i686-pc-win32 -fdump-record-layouts -fsyntax-only -cxx-abi microsoft %s 2>/dev/null \
// RUN:            | FileCheck %s
// RUN: %clang_cc1 -fno-rtti -emit-llvm-only -triple x86_64-pc-win32 -fdump-record-layouts -fsyntax-only -cxx-abi microsoft %s 2>/dev/null \
// RUN:            | FileCheck %s -check-prefix CHECK-X64

extern "C" int printf(const char *fmt, ...);
__declspec(align(4096)) char buffer[4096];

struct AT {};

struct V : AT {
	char c;
	V() {
		printf("V   - this: %d\n", (int)((char*)this - buffer));
	}
};

struct AT0 {
	union { struct { int a; AT t; } y; int b; } x;
	char c;
	AT0() {
		printf("AT0 - this: %d\n", (int)((char*)this - buffer));
	}
};

struct AT1 : V {
	int a;
	AT1() {
		printf("AT1 - this: %d\n", (int)((char*)this - buffer));
	}
};

struct AT2 {
	AT0 t;
	char AT2FieldName0;
	AT2() {
		printf("AT2 - this: %d\n", (int)((char*)this - buffer));
		printf("AT2 - Fiel: %d\n", (int)((char*)&AT2FieldName0 - buffer));
	}
};

struct AT3 : AT2, AT1 {
	AT3() {
		printf("AT3 - this: %d\n", (int)((char*)this - buffer));
	}
};

// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK-NEXT:    0 | struct AT3
// CHECK-NEXT:    0 |   struct AT2 (base)
// CHECK-NEXT:    0 |     struct AT0 t
// CHECK-NEXT:    0 |       union AT0::<anonymous at {{.*}} x
// CHECK-NEXT:    0 |         struct AT0::<anonymous at {{.*}} y
// CHECK-NEXT:    0 |           int a
// CHECK-NEXT:    4 |           struct AT t (empty)
// CHECK:         0 |         int b
// CHECK:         8 |       char c
// CHECK:        12 |     char AT2FieldName0
// CHECK-NEXT:   20 |   struct AT1 (base)
// CHECK-NEXT:   20 |     struct V (base)
// CHECK-NEXT:   20 |       struct AT (base) (empty)
// CHECK-NEXT:   20 |       char c
// CHECK-NEXT:   24 |     int a
// CHECK-NEXT:      | [sizeof=28, align=4
// CHECK-NEXT:      |  nvsize=28, nvalign=4]
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64-NEXT:    0 | struct AT3
// CHECK-X64-NEXT:    0 |   struct AT2 (base)
// CHECK-X64-NEXT:    0 |     struct AT0 t
// CHECK-X64-NEXT:    0 |       union AT0::<anonymous at {{.*}} x
// CHECK-X64-NEXT:    0 |         struct AT0::<anonymous at {{.*}} y
// CHECK-X64-NEXT:    0 |           int a
// CHECK-X64-NEXT:    4 |           struct AT t (empty)
// CHECK-X64:         0 |         int b
// CHECK-X64:         8 |       char c
// CHECK-X64:        12 |     char AT2FieldName0
// CHECK-X64-NEXT:   20 |   struct AT1 (base)
// CHECK-X64-NEXT:   20 |     struct V (base)
// CHECK-X64-NEXT:   20 |       struct AT (base) (empty)
// CHECK-X64-NEXT:   20 |       char c
// CHECK-X64-NEXT:   24 |     int a
// CHECK-X64-NEXT:      | [sizeof=28, align=4
// CHECK-X64-NEXT:      |  nvsize=28, nvalign=4]

struct BT0 {
	BT0() {
		printf("BT0 - this: %d\n", (int)((char*)this - buffer));
	}
};

struct BT2 : BT0 {
	char BT2FieldName0;
	BT2() {
		printf("BT2 - this: %d\n", (int)((char*)this - buffer));
		printf("BT2 - Fiel: %d\n", (int)((char*)&BT2FieldName0 - buffer));
	}
};

struct BT3 : BT0, BT2 {
	BT3() {
		printf("BT3 - this: %d\n", (int)((char*)this - buffer));
	}
};

// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK-NEXT:    0 | struct BT3
// CHECK-NEXT:    0 |   struct BT0 (base) (empty)
// CHECK-NEXT:    1 |   struct BT2 (base)
// CHECK-NEXT:    1 |     struct BT0 (base) (empty)
// CHECK-NEXT:    1 |     char BT2FieldName0
// CHECK-NEXT:      | [sizeof=2, align=1
// CHECK-NEXT:      |  nvsize=2, nvalign=1]
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64-NEXT:    0 | struct BT3
// CHECK-X64-NEXT:    0 |   struct BT0 (base) (empty)
// CHECK-X64-NEXT:    1 |   struct BT2 (base)
// CHECK-X64-NEXT:    1 |     struct BT0 (base) (empty)
// CHECK-X64-NEXT:    1 |     char BT2FieldName0
// CHECK-X64-NEXT:      | [sizeof=2, align=1
// CHECK-X64-NEXT:      |  nvsize=2, nvalign=1]

struct T0 : AT {
	T0() {
		printf("T0 (this) : %d\n", (char*)this - buffer);
	}
};

struct T1 : T0 {
	char a;
	T1() {
		printf("T1 (this) : %d\n", (char*)this - buffer);
		printf("T1 (fiel) : %d\n", (char*)&a - buffer);
	}
};

struct T2 : AT {
	char a;
	T2() {
		printf("T2 (this) : %d\n", (char*)this - buffer);
		printf("T2 (fiel) : %d\n", (char*)&a - buffer);
	}
};

struct __declspec(align(1)) T3 : virtual T1, virtual T2 {
	T3() {
		printf("T3 (this) : %d\n", (char*)this - buffer);
	}
};

// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK: *** Dumping AST Record Layout
// CHECK-NEXT:    0 | struct T3
// CHECK-NEXT:    0 |   (T3 vbtable pointer)
// CHECK-NEXT:    4 |   struct T1 (virtual base)
// CHECK-NEXT:    4 |     struct T0 (base) (empty)
// CHECK-NEXT:    4 |       struct AT (base) (empty)
// CHECK-NEXT:    4 |     char a
// CHECK-NEXT:   12 |   struct T2 (virtual base)
// CHECK-NEXT:   12 |     struct AT (base) (empty)
// CHECK-NEXT:   12 |     char a
// CHECK-NEXT:      | [sizeof=16, align=4
// CHECK-NEXT:      |  nvsize=4, nvalign=4]
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64: *** Dumping AST Record Layout
// CHECK-X64-NEXT:    0 | struct T3
// CHECK-X64-NEXT:    0 |   (T3 vbtable pointer)
// CHECK-X64-NEXT:    8 |   struct T1 (virtual base)
// CHECK-X64-NEXT:    8 |     struct T0 (base) (empty)
// CHECK-X64-NEXT:    8 |       struct AT (base) (empty)
// CHECK-X64-NEXT:    8 |     char a
// CHECK-X64-NEXT:   16 |   struct T2 (virtual base)
// CHECK-X64-NEXT:   16 |     struct AT (base) (empty)
// CHECK-X64-NEXT:   16 |     char a
// CHECK-X64-NEXT:      | [sizeof=24, align=8
// CHECK-X64-NEXT:      |  nvsize=8, nvalign=8]

int a[
sizeof(AT3) +
sizeof(BT3) +
sizeof(T3)];
