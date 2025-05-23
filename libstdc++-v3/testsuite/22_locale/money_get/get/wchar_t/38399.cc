// Copyright (C) 2008-2025 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// 22.2.6.1.1 money_get members

#include <locale>
#include <sstream>
#include <testsuite_hooks.h>

class my_moneypunct : public std::moneypunct<wchar_t>
{
protected:
  //this should disable fraction part of monetary value
  int do_frac_digits() const { return 0; }
};

// libstdc++/38399
void test01()
{
  using namespace std;

  locale loc(locale(), new my_moneypunct());
  wstringstream ss(L"123.455");
  ss.imbue(loc);
  wstring digits;
  ios_base::iostate err;
  istreambuf_iterator<wchar_t> iter = 
    use_facet<money_get<wchar_t> >(loc).get(ss, 0, false, ss, err, digits);
  
  wstring rest = wstring(iter, istreambuf_iterator<wchar_t>());
  VERIFY( digits == L"123" );
  VERIFY( rest == L".455" );
}

int main()
{
  test01();
  return 0;
}
