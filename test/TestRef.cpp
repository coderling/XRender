// Static Reflection by BOT Man, 2018

#ifndef STATIC_REFLECTION_H_
#define STATIC_REFLECTION_H_

#include <tuple>
#include <type_traits>

namespace detail {

template <typename Fn, typename Tuple, std::size_t... I>
inline constexpr void ForEachTuple(Tuple&& tuple,
                                   Fn&& fn,
                                   std::index_sequence<I...>) {
  using Expander = int[];
  (void)Expander{0, ((void)fn(std::get<I>(std::forward<Tuple>(tuple))), 0)...};
}

template <typename Fn, typename Tuple>
inline constexpr void ForEachTuple(Tuple&& tuple, Fn&& fn) {
  ForEachTuple(
      std::forward<Tuple>(tuple), std::forward<Fn>(fn),
      std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
}

template <typename T>
struct is_field_pointer : std::false_type {};

template <typename C, typename T>
struct is_field_pointer<T C::*> : std::true_type {};

template <typename T>
constexpr auto is_field_pointer_v = is_field_pointer<T>::value;

}  // namespace detail

template <typename T>
inline constexpr auto StructSchema() {
  return std::make_tuple();
}

#define DEFINE_STRUCT_SCHEMA(Struct, ...)        \
  template <>                                    \
  inline constexpr auto StructSchema<Struct>() { \
    using _Struct = Struct;                      \
    return std::make_tuple(__VA_ARGS__);         \
  }

#define DEFINE_STRUCT_FIELD(StructField, FieldName) \
  std::make_tuple(&_Struct::StructField, FieldName)

template <typename T, typename Fn>
inline constexpr void ForEachField(T&& value, Fn&& fn) {
  constexpr auto struct_schema = StructSchema<std::decay_t<T>>();
  static_assert(std::tuple_size<decltype(struct_schema)>::value != 0,
                "StructSchema<T>() for type T should be specialized to return "
                "FieldSchema tuples, like ((&T::field, field_name), ...)");

  detail::ForEachTuple(struct_schema, [&value, &fn](auto&& field_schema) {
    using FieldSchema = std::decay_t<decltype(field_schema)>;
    static_assert(
        std::tuple_size<FieldSchema>::value >= 2 &&
            detail::is_field_pointer_v<std::tuple_element_t<0, FieldSchema>>,
        "FieldSchema tuple should be (&T::field, field_name)");

    fn(value.*(std::get<0>(std::forward<decltype(field_schema)>(field_schema))),
       std::get<1>(std::forward<decltype(field_schema)>(field_schema)));
  });
}

#endif  // STATIC_REFLECTION_H_

// clang++ static_iostream.cc -std=c++14 -Wall -o s_iostream && ./s_iostream

#include <iostream>
#include <string>

struct SimpleStruct {
  bool bool_;
  int int_;
  double double_;
  std::string string_;
};

DEFINE_STRUCT_SCHEMA(SimpleStruct,
                     DEFINE_STRUCT_FIELD(bool_, "bool"),
                     DEFINE_STRUCT_FIELD(int_, "int"),
                     DEFINE_STRUCT_FIELD(double_, "double"),
                     DEFINE_STRUCT_FIELD(string_, "string"));

struct GenericFunctor {
  // ... context data

  template <typename Field, typename Name>
  void operator()(Field&& field, Name&& name) {
    std::cout << std::boolalpha << std::fixed << name << ": " << field
              << std::endl;
  }
};

namespace {

template <class... Fs>
struct overload_set;

template <class F1, class... Fs>
struct overload_set<F1, Fs...> : F1, overload_set<Fs...>::type {
  typedef overload_set type;

  overload_set(F1 head, Fs... tail)
      : F1(head), overload_set<Fs...>::type(tail...) {}

  using F1::operator();
  using overload_set<Fs...>::type::operator();
};

template <class F>
struct overload_set<F> : F {
  typedef F type;
  using F::operator();
};

template <class... Fs>
typename overload_set<Fs...>::type overload(Fs... x) {
  return overload_set<Fs...>(x...);
}

}  // namespace

int main() {
  ForEachField(SimpleStruct{true, 1, 1.0, "hello static reflection"},
               [](auto&& field, auto&& name) {
                 std::cout << std::boolalpha << std::fixed << name << ": "
                           << field << std::endl;
               });

  ForEachField(SimpleStruct{true, 1, 1.0, "hello static reflection"},
               GenericFunctor{/* ... context data */});

  ForEachField(SimpleStruct{true, 1, 1.0, "hello static reflection"},
               overload(
                   [](bool field, const char* name) {
                     std::cout << "b " << std::boolalpha << name << ": "
                               << field << std::endl;
                   },
                   [](int field, const char* name) {
                     std::cout << "i " << name << ": " << field << std::endl;
                   },
                   [](double field, const char* name) {
                     std::cout << "d " << std::fixed << name << ": " << field
                               << std::endl;
                   },
                   [](const std::string& field, const char* name) {
                     std::cout << "s " << name << ": " << field.c_str()
                               << std::endl;
                   }));
  return 0;
}