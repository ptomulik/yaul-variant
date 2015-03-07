// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>

// We don't check at compile time for a type uniqueness in variant, because
// the cost would be O(N^2). Most operations would continue to work correctly
// even if there are repeated types.
typedef yaul::variant<int,int> T;

int main() { return 0; }
