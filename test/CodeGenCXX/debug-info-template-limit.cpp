// RUN: %clang_cc1 -emit-llvm -fno-standalone-debug -cxx-abi itanium -g %s -o - | FileCheck %s

// Check that this pointer type is TC<int>
// CHECK: ![[LINE:[0-9]+]] = {{.*}}"TC<int>", {{.*}} metadata !"_ZTS2TCIiE"} ; [ DW_TAG_class_type ]
// CHECK: metadata !"_ZTS2TCIiE"} ; [ DW_TAG_pointer_type ]{{.*}}[from _ZTS2TCIiE]

template<typename T>
class TC {
public:
  TC(const TC &) {}
  TC() {}
};

TC<int> tci;
