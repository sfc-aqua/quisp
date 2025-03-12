/**

MIT License

Copyright (c) 2016 Gabor Marton

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

// copy of https://github.com/martong/access_private/tree/c65d54b17bf7b212cb4df867edf143f2ebb0186a
// clang-format off

#include <utility>
#include <type_traits>

#if __cplusplus == 201103L
namespace std {
  template <bool B, class T = void>
  using enable_if_t = typename enable_if<B, T>::type;
  template <class T>
  using remove_reference_t = typename remove_reference<T>::type;
} // std
#endif

// Unnamed namespace is used to avoid duplicate symbols if the macros are used
// in several translation units. See test1.
namespace {
  namespace private_access_detail {

    // @tparam TagType, used to declare different "get" funciton overloads for
    // different members/statics
    template <typename PtrType, PtrType PtrValue, typename TagType>
    struct private_access {
      // Normal lookup cannot find in-class defined (inline) friend functions.
      friend PtrType get(TagType) { return PtrValue; }
    };

  } // namespace private_access_detail
} // namespace

// Used macro naming conventions:
// The "namespace" of this macro library is PRIVATE_ACCESS, i.e. all
// macro here has this prefix.
// All implementation macro, which are not meant to be used directly have the
// PRIVATE_ACCESS_DETAIL prefix.
// Some macros have the ABCD_IMPL form, which means they contain the
// implementation details for the specific ABCD macro.

#define PRIVATE_ACCESS_DETAIL_CONCATENATE_IMPL(x, y) x##y
#define PRIVATE_ACCESS_DETAIL_CONCATENATE(x, y)                                \
  PRIVATE_ACCESS_DETAIL_CONCATENATE_IMPL(x, y)

// @param PtrTypeKind E.g if we have "class A", then it can be "A::*" in case of
// members, or it can be "*" in case of statics.
#define PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE(Tag, Class, Type, Name,           \
                                             PtrTypeKind)                      \
  namespace {                                                                  \
    namespace private_access_detail {                                          \
      /* Tag type, used to declare different get funcitons for different       \
       * members                                                               \
       */                                                                      \
      struct Tag {};                                                           \
      /* Explicit instantiation */                                             \
      template struct private_access<decltype(&Class::Name), &Class::Name,     \
                                     Tag>;                                     \
      /* We can build the PtrType only with two aliases */                     \
      /* E.g. using PtrType = int(int) *; would be illformed */                \
      using PRIVATE_ACCESS_DETAIL_CONCATENATE(Alias_, Tag) = Type;             \
      using PRIVATE_ACCESS_DETAIL_CONCATENATE(PtrType_, Tag) =                 \
          PRIVATE_ACCESS_DETAIL_CONCATENATE(Alias_, Tag) PtrTypeKind;          \
      /* Declare the friend function, now it is visible in namespace scope.    \
       * Note,                                                                 \
       * we could declare it inside the Tag type too, in that case ADL would   \
       * find                                                                  \
       * the declaration. By choosing to declare it here, the Tag type remains \
       * a                                                                     \
       * simple tag type, it has no other responsibilities. */                 \
      PRIVATE_ACCESS_DETAIL_CONCATENATE(PtrType_, Tag) get(Tag);               \
    }                                                                          \
  }

#define PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE_FIELD(Tag, Class, Type, Name)     \
  PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE(Tag, Class, Type, Name, Class::*)       \
  namespace {                                                                  \
    namespace access_private {                                                 \
      Type &Name(Class &&t) { return t.*get(private_access_detail::Tag{}); }   \
      Type &Name(Class &t) { return t.*get(private_access_detail::Tag{}); }    \
      /* The following usings are here to avoid duplicate const qualifier      \
       * warnings                                                              \
       */                                                                      \
      using PRIVATE_ACCESS_DETAIL_CONCATENATE(X, Tag) = Type;                  \
      using PRIVATE_ACCESS_DETAIL_CONCATENATE(Y, Tag) =                        \
          const PRIVATE_ACCESS_DETAIL_CONCATENATE(X, Tag);                     \
      PRIVATE_ACCESS_DETAIL_CONCATENATE(Y, Tag) & Name(const Class &t) {       \
        return t.*get(private_access_detail::Tag{});                           \
      }                                                                        \
    }                                                                          \
  }

#define PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE_FUN(Tag, Class, Type, Name)       \
  PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE(Tag, Class, Type, Name, Class::*)       \
  namespace {                                                                  \
    namespace call_private {                                                   \
      /* We do perfect forwarding, but we want to restrict the overload set    \
       * only for objects which have the type Class. */                        \
      template <typename Obj,                                                  \
                std::enable_if_t<std::is_same<std::remove_reference_t<Obj>,    \
                                              Class>::value> * = nullptr,      \
                typename... Args>                                              \
      auto Name(Obj &&o, Args &&... args) -> decltype(                         \
          (std::forward<Obj>(o).*                                              \
           get(private_access_detail::Tag{}))(std::forward<Args>(args)...)) {  \
        return (std::forward<Obj>(o).*get(private_access_detail::Tag{}))(      \
            std::forward<Args>(args)...);                                      \
      }                                                                        \
    }                                                                          \
  }

#define PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE_STATIC_FIELD(Tag, Class, Type,    \
                                                          Name)                \
  PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE(Tag, Class, Type, Name, *)              \
  namespace {                                                                  \
    namespace access_private_static {                                          \
      namespace Class {                                                        \
        Type &Name() { return *get(private_access_detail::Tag{}); }            \
      }                                                                        \
    }                                                                          \
  }

#define PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE_STATIC_FUN(Tag, Class, Type,      \
                                                        Name)                  \
  PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE(Tag, Class, Type, Name, *)              \
  namespace {                                                                  \
    namespace call_private_static {                                            \
      namespace Class {                                                        \
        template <typename... Args>                                            \
        auto Name(Args &&... args) -> decltype(                                \
            get(private_access_detail::Tag{})(std::forward<Args>(args)...)) {  \
          return get(private_access_detail::Tag{})(                            \
              std::forward<Args>(args)...);                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }

#define PRIVATE_ACCESS_DETAIL_UNIQUE_TAG                                       \
  PRIVATE_ACCESS_DETAIL_CONCATENATE(PrivateAccessTag, __COUNTER__)

#define ACCESS_PRIVATE_FIELD(Class, Type, Name)                                \
  PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE_FIELD(PRIVATE_ACCESS_DETAIL_UNIQUE_TAG, \
                                             Class, Type, Name)

#define ACCESS_PRIVATE_FUN(Class, Type, Name)                                  \
  PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE_FUN(PRIVATE_ACCESS_DETAIL_UNIQUE_TAG,   \
                                           Class, Type, Name)

#define ACCESS_PRIVATE_STATIC_FIELD(Class, Type, Name)                         \
  PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE_STATIC_FIELD(                           \
      PRIVATE_ACCESS_DETAIL_UNIQUE_TAG, Class, Type, Name)

#define ACCESS_PRIVATE_STATIC_FUN(Class, Type, Name)                           \
  PRIVATE_ACCESS_DETAIL_ACCESS_PRIVATE_STATIC_FUN(                             \
      PRIVATE_ACCESS_DETAIL_UNIQUE_TAG, Class, Type, Name)

