// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>

struct S1 {};
struct S2 { S2() = delete; };
struct S3 { S3(const S3&) = delete; };

// This should compile without problem
typedef yaul::variant<int>              T1;
typedef yaul::variant<int,float,char>   T2;
typedef yaul::variant<S1>               T3;
typedef yaul::variant<S2>               T4;
typedef yaul::variant<S3>               T5;
typedef yaul::variant<S1,S2>            T6;
typedef yaul::variant<S1,S2,S3>         T7;

int main() { return 0; }
