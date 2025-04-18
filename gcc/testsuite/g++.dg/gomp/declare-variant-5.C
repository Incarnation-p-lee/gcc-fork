// Test parsing of #pragma omp declare variant
// { dg-do compile }

int fn0 (int) { return 0; }
int fn20 (int) { return 0; }

#pragma omp declare variant (fn0) match (user={condition(0)})
extern "C"		// { dg-error "not immediately followed by function declaration or definition" }
{
  int fn5 (int a) { return 0; }
}

#pragma omp declare variant (fn0) match (user={condition(0)}) // { dg-error "not immediately followed by function declaration or definition" }
namespace N1
{
  int fn6 (int a) { return 0; }
}

#pragma omp declare variant (fn0) match (user={condition(0)})
struct A
{			// { dg-error "not immediately followed by function declaration or definition" }
  int fn7 (int a) { return 0; }
};

#pragma omp declare variant (fn0) match (user={condition(0)})
template <typename T>
struct B
{			// { dg-error "not immediately followed by function declaration or definition" }
  int fn8 (int a) { return 0; }
};

struct C
{
#pragma omp declare variant (fn0) match (user={condition(0)}) // { dg-error "not immediately followed by function declaration or definition" }
  public:		 // { dg-error "expected unqualified-id before" }
    int fn9 (int a) { return 0; }
};

int t;

#pragma omp declare variant (fn0) match (user={condition(0)})
#pragma omp declare variant (fn20) match (implementation={vendor(unknown)})
#pragma omp threadprivate(t)	// { dg-error "not immediately followed by function declaration or definition" }
int fn10 (int a) { return 0; }

struct D
{
  int d;
  int fn11 (int a) { return 0; }
  #pragma omp declare variant (fn11) match (user={condition(sizeof (e) == sizeof (this->e))}) // { dg-error "has no member named" }
  template <int N>	// { dg-error "was not declared" "" { target *-*-* } .-1 }
  int fn12 (int a) { return 0; }
  int e;
};

#pragma omp declare variant (1 + 2) match (user={condition(0)}) // { dg-error "before numeric constant" }
int fn13 (int) { return 0; }

#pragma omp declare variant (t) match (user={condition(0)})	// { dg-error "'t' cannot be used as a function" }
int fn14 (int) { return 0; }

long fn15 (char, short) { return 0; }

#pragma omp declare variant (fn15) match (implementation={vendor(unknown)})      // { dg-error "variant 'long int fn15\\\(char, short int\\\)' and base 'int fn16\\\(int, long long int\\\)' have incompatible types" }
int fn16 (int, long long) { return 0; }

#pragma omp declare variant (memcpy) match (implementation={vendor(llvm)})      // { dg-error "'memcpy' was not declared in this scope" }
void *fn17 (void *, const void *, __SIZE_TYPE__) { return (void *) 0; }

#pragma omp declare variant (__builtin_memmove) match (implementation={vendor(gnu)})    // { dg-error "variant '\[^'\n\r]*' is a built-in" }
void *fn18 (void *, const void *, __SIZE_TYPE__) { return (void *) 0; }

struct E { int e; };

void fn19 (E, int) {}

#pragma omp declare variant (fn19)match(user={condition(0)})	// { dg-error {could not convert 'i' from 'int' to 'E'} }
void fn20 (int i, E e) {}

struct F { operator int () const { return 42; } int f; };
void fn21 (int, F) {}

#pragma omp declare variant ( fn21 ) match (user = { condition ( 1 - 1 ) } )	// { dg-error "variant 'void fn21\\\(int, F\\\)' and base 'void fn22\\\(F, F\\\)' have incompatible types" }
void fn22 (F, F) {}

#pragma omp declare variant (fn19) match (user={condition(0)})		// { dg-error {could not convert 'f' from 'F' to 'E'} }
void fn23 (F f, int i) {}

void fn24 (int);
struct U { int u; };
struct T
{
  void fn25 (int) {}
  int t;
};
struct S : public U, T
{
  #pragma omp declare variant (fn25) match (user={condition(true)})	// { dg-error "variant 'void T::fn25\\\(int\\\)' and base 'void S::fn26\\\(int\\\)' have incompatible types" }
  void fn26 (int) {}
  #pragma omp declare variant (fn24) match (user={condition(true)})	// { dg-error "variant 'void fn24\\\(int\\\)' and base 'void S::fn27\\\(int\\\)' have incompatible types" }
  void fn27 (int) {}
  void fn28 (int);
  struct s;
};
#pragma omp declare variant (fn25) match (user={condition(true)})	// { dg-error "variant 'void T::fn25\\\(int\\\)' and base 'void S::fn28\\\(int\\\)' have incompatible types" }
void S::fn28 (int)
{
}

void fn30 (int) throw () {}
#pragma omp declare variant (fn30) match (user={condition(true)})	// { dg-error "variant 'void fn30\\\(int\\\)' and base 'void fn31\\\(int\\\)' have incompatible types" "" { target c++17 } }
void fn31 (int) {}

struct W
{
  int fn32 (int) const { return 0; }
  #pragma omp declare variant (fn32) match (user={condition(true)})	// { dg-error "variant 'int W::fn32\\\(int\\\) const' and base 'int W::fn33\\\(int\\\)' have incompatible types" }
  int fn33 (int) { return 0; }
  int fn34 (int) volatile { return 0; }
  #pragma omp declare variant (fn34) match (user={condition(true)})	// { dg-error "variant 'int W::fn34\\\(int\\\) volatile' and base 'int W::fn35\\\(int\\\) const volatile' have incompatible types" }
  int fn35 (int) const volatile { return 0; }				// { dg-error "passing 'const volatile W' as 'this' argument discards qualifiers" "" { target *-*-* } .-1 }
  int fn36 (int) { return 0; }
  #pragma omp declare variant (fn36) match (user={condition(true)})	// { dg-error "variant 'int W::fn36\\\(int\\\)' and base 'int W::fn37\\\(int\\\) volatile' have incompatible types" }
  int fn37 (int) volatile { return 0; }					// { dg-error "passing 'volatile W' as 'this' argument discards qualifiers" "" { target *-*-* } .-1 }
  int fn38 (int) throw () { return 0; }
  #pragma omp declare variant (fn38) match (user={condition(true)})	// { dg-error "variant 'int W::fn38\\\(int\\\)' and base 'int W::fn39\\\(int\\\)' have incompatible types" "" { target c++17 } }
  int fn39 (int) { return 0; }
  int fn40 (int) { return 0; }
  #pragma omp declare variant (fn40) match (user={condition(true)})	// { dg-error "variant 'int W::fn40\\\(int\\\)' and base 'int W::fn41\\\(int\\\)' have incompatible types" "" { target c++17 } }
  int fn41 (int) throw () { return 0; }
};
