//
// Created by ZhouP on 4/29/2019.
//

#ifndef CPPSANDBOX_LEETCODE_TESTCPP17_H_
#define CPPSANDBOX_LEETCODE_TESTCPP17_H_

#include <set>
#include <map>
#include <ostream>
#include <memory>
#include <cstddef>

// { autofold
struct S {
  int n;
  std::string s;
  float d;
  bool operator<(const S& rhs) const
  {
    // compares n to rhs.n,
    // then s to rhs.s,
    // then d to rhs.d
    return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
  }

  friend std::ostream& operator<< (std::ostream& out, const S& as){
    out << as.n << ',' << as.s << ',' << as.d << std::endl;
    return out;
  }
};
// }


class SimpleType
{
 private:
  int a { 1 };    // << wow!
  int b { 1 };    // << wow2!
  std::string name { "string" }; // wow3!

 public:
  SimpleType() {
    std::cout << "SimpleType::ctor, {" << a << ", " << b << ", \"" << name << "\"}\n";
  }
  SimpleType(int aa, int bb) : a(aa), b(bb) {
    std::cout << "SimpleType::ctor(aa, bb), {" << a << ", " << b << ", \"" << name << "\"}\n";
  }
  ~SimpleType() { std::cout << "SimpleType::destructor\n"; }
};

class AdvancedType
{
 private:
  SimpleType simple;

 public:
  AdvancedType() {
    std::cout << "AdvancedType::ctor\n";
  }
  AdvancedType(int a) : simple(a, a) {
    std::cout << "AdvancedType::ctor(a)\n";
  }
  ~AdvancedType() { std::cout << "AdvancedType::destructor\n"; }
};

struct MyClass
{
  inline static const int sValue = 777;
};

template <typename T>
auto get_value(T t) {
  if constexpr (std::is_pointer_v<T>)
    return *t;
  else
    return t;
}

//sum function

auto SumCpp11(){
  return 0;
}

template<typename T1, typename... T>
auto SumCpp11(T1 s, T... ts){
  return s + SumCpp11(ts...);
}

template<typename ...Args> auto sum(Args ...args)
{
  return (args + ... + 0);
}

template<typename ...Args> auto sum2(Args ...args)
{
  return (args + ...);
}

template <auto value> constexpr auto TConstant = value;


struct X {
  const int n; // note: X has a const member
  int m;
};

struct Y {
  int z;
};

struct A {
  virtual int transmogrify();
};

struct B : A {
  int transmogrify() override { new(this) A; return 2; }
};

int A::transmogrify() { new(this) B; return 1; }

static_assert(sizeof(B) == sizeof(A));


struct Foo {
  int count = std::uncaught_exceptions();
  ~Foo() {
    std::cout << (count == std::uncaught_exceptions()
                  ? "~Foo() called normally\n"
                  : std::to_string(count) + " ~Foo() called during stack unwinding\n");

//    try
//    {
//      throw std::runtime_error("destructor expection");
//    }
//    catch (const std::exception& e) {
//      std::cout << "Exception caught: " << e.what() << '\n';
//    }
  }
};


int test_exception()
{
  Foo f;
  try {
    Foo f;
    std::cout << "Exception thrown\n";
    throw std::runtime_error("test exception 1");
    throw std::runtime_error("test exception 2");
  } catch (const std::exception& e) {
    std::cout << "Exception caught: " << e.what() << '\n';
  }
}

int test_launder()
{
//  X *p = new X{3, 4};
//  const int a = p->n;
//  X* np = new (p) X{5, 6};    // p does not point to new object because X::n is const; np does
//  const int b = p->n; // undefined behavior
//  const int c = p->m; // undefined behavior (even though m is non-const, p can't be used)
//  const int d = std::launder(p)->n; // OK, std::launder(p) points to new object
//  const int e = np->n; // OK



//  alignas(Y)
  std::byte s[sizeof(Y)];
  Y* q = new(&s) Y{2};
  const int f = reinterpret_cast<Y*>(&s)->z; // Class member access is undefined behavior:
  // reinterpret_cast<Y*>(&s) has value "pointer to s"
  // and does not point to a Y object
  const int g = q->z; // OK
  const int h = std::launder(reinterpret_cast<Y*>(&s))->z; // OK

  A i;
  int n = i.transmogrify();
  // int m = i.transmogrify(); // undefined behavior
  int m = std::launder(&i)->transmogrify(); // OK
//  assert(m + n == 3);
}

void test_cpp17features() {
//
//  SimpleType simpleObj;
//  AdvancedType advObj;
//  AdvancedType advObj2(10);
//  std::cout << "MyClass::sValue is " << MyClass::sValue << std::endl;
//
//  std::set<S> mySet;
//  S value{42, "Test", 3.14};
//  auto [iter, inserted] = mySet.insert(value);
//  if (inserted)
//    std::cout << value << std::endl;
//
//  const std::map<std::string, std::string> capitals {
//      { "Poland", "Warsaw"},
//      { "USA", "Washington"},
//      { "France", "Paris"},
//      { "UK", "London"},
//      { "Germany", "Berlin"}
//  };
//  for (auto & [k, v] : capitals)
//  {
//    std::cout << k << "'s capital is " << v << std::endl;
//  }
//
//  std::vector<int> values = {1, 3, 4, 5, 7};
//  if (auto iter = std::find(values.begin(), values.end(), 3); iter != values.end()) {
//    std::cout << "find value in vector " << *iter << std::endl;
//  } else {
//    std::cout << "didn't find value in vector " << std::distance(values.begin(), iter) << std::endl;
//  }
//
//  auto pi = std::make_unique<int>(9);
//  int i = 9;
//
//  std::cout << get_value(pi.get()) << "\n";
//  std::cout << get_value(i) << "\n";
//
//
//  std::cout << sum(1, 2, 3, 4, 5, 6, 7) << "\n";
//  std::cout << sum2(1, 2, 3, 4, 5, 6, 7) << "\n";
//  std::cout << SumCpp11(1, 2, 3, 4, 5, 6, 7) << "\n";
//
//
//  std::pair d(0, 0.0);
//  std::tuple t(1, 2, 3);
//
//  std::cout << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << "\n";
//
//  // ^^^^
//  constexpr auto const MySuperConst = TConstant <100>;
//  std::cout << "MySuperConst is of value " << MySuperConst << std::endl;

//  test_launder();
//  test_exception();

  typedef std::pair<int, int> IntPair;
  typedef std::vector<IntPair> VecIntPairs;
  typedef std::tuple<int, int, int> IntTuple;
  typedef std::vector<IntTuple> VecIntTuples;

  VecIntPairs pairs;
  pairs.emplace_back(1, 2);
  pairs.emplace_back(3, 4);
  pairs.emplace_back(2, 4);

  for (auto [s, e] : pairs)
  {
    std::cout << s << "," << e << std::endl;
  }

  VecIntTuples tuples;
  tuples.emplace_back(1, 2, 3);
  tuples.emplace_back(3, 4, 5);
  tuples.emplace_back(2, 4, 8);

  for (auto [s, m, e] : tuples)
  {
    std::cout << s << "," << m << ","<< e << std::endl;
  }
}
#endif //CPPSANDBOX_LEETCODE_TESTCPP17_H_
