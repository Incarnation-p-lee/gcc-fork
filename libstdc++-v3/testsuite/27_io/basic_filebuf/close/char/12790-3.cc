// Copyright (C) 2003-2025 Free Software Foundation, Inc.
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

// { dg-require-fileio "" }

// 27.8.1.3 filebuf member functions

#include <locale>
#include <fstream>
#include <testsuite_hooks.h>

class Cvt : public std::codecvt<char, char, std::mbstate_t>
{
public:
  mutable bool unshift_called;

  Cvt()
  : unshift_called(false)
  { }

protected:
  bool
  do_always_noconv() const throw()
  { return false; }

  int
  do_encoding() const throw()
  { return -1; }

  std::codecvt_base::result
  do_unshift(std::mbstate_t&, char* to, char*, char*& to_next) const
  {
    unshift_called = true;
    to_next = to;
    return codecvt_base::error;
  }
};

// libstdc++/12790
// basic_filebuf::close() should fail if codecvt::unshift() fails
void test01()
{
  using namespace std;

  const char* name = "tmp_close_12790";

  Cvt* cvt = new Cvt;
  locale loc(locale::classic(), cvt);

  filebuf fb;
  fb.pubimbue(loc);

  fb.open(name, ios_base::out);
  fb.sputc('a');

  VERIFY( !cvt->unshift_called );
  filebuf* ret = fb.close();
  VERIFY( cvt->unshift_called );
  VERIFY( !ret );
}

int main()
{
  test01();
  return 0;
}
