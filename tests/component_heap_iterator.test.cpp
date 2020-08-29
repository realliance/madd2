#include <gtest/gtest.h>
#include <stdint.h>
#include <typeindex>
#include <vector>
#include <tuple>
#include "component_heap.h"

typedef struct{int data;} Type0;
typedef struct{int data;} Type1;
typedef struct{int data;} Type2;
inline bool operator==(const Type0& lhs, const Type0& rhs){ return lhs.data == rhs.data;}
inline bool operator==(const Type1& lhs, const Type1& rhs){ return lhs.data == rhs.data;}
inline bool operator==(const Type2& lhs, const Type2& rhs){ return lhs.data == rhs.data;}
std::ostream& operator<< (std::ostream &os, const Type0& type){
  os << "Type0: " << type.data;
  return os;
}
std::ostream& operator<< (std::ostream &os, const Type1& type){
  os << "Type1: " << type.data;
  return os;
}
std::ostream& operator<< (std::ostream &os, const Type2& type){
  os << "Type2: " << type.data;
  return os;
}

TEST(ComponentHeap, SingleType){
  // Arrange
  ComponentHeap heap;
  Entity entity = 0;
  std::vector<std::type_index> componentType = {std::type_index(typeid(Type0)),std::type_index(typeid(Type1))};
  (*heap.data())[componentType[0]][entity]   = Type0{0};
  (*heap.data())[componentType[0]][entity+1] = Type0{1};
  (*heap.data())[componentType[1]][entity+2] = Type1{2};

  {
    ComponentHeap::TypeSet typeset = heap.toTypeSet<Type0>();
    ComponentHeap::iterator itr = typeset.begin();

    // Act, Assert
    ASSERT_EQ(
      itr,
      typeset.begin()
    );
    EXPECT_EQ(
      std::get<0>(*itr),
      Type0{0}
    );
    ASSERT_NE(
      ++itr,
      typeset.end()
    );
    EXPECT_EQ(
      std::get<0>(*itr),
      Type0{1}
    );
    EXPECT_EQ(
      std::get<0>(*(itr++)),
      Type0{1}
    );
    EXPECT_EQ(
      itr,
      typeset.end()
    );
  }
}

TEST(ComponentHeap, MultiType){
  // Arrange
  ComponentHeap heap;
  Entity entity = 0;
  std::vector<std::type_index> componentType = {std::type_index(typeid(Type0)),std::type_index(typeid(Type1))};
  (*heap.data())[componentType[0]][entity]   = Type0{0};
  (*heap.data())[componentType[1]][entity]   = Type1{1};
  (*heap.data())[componentType[0]][entity+1] = Type0{2};
  (*heap.data())[componentType[1]][entity+1] = Type1{3};
  (*heap.data())[componentType[0]][entity+2] = Type0{4};
  (*heap.data())[componentType[1]][entity+3] = Type1{5};

  {
    ComponentHeap::TypeSet typeset = heap.toTypeSet<Type0,Type1>();
    ComponentHeap::iterator itr = typeset.begin();
    Type0 type0;
    Type1 type1;

    // Act, Assert
    ASSERT_EQ(
      itr,
      typeset.begin()
    );
    type0 = {0};
    type1 = {1};
    EXPECT_EQ(
      *itr,
      (std::tuple<const Type0, const Type1>{type0,type1})
    );
    ASSERT_NE(
      ++itr,
      typeset.end()
    );
    type0 = {2};
    type1 = {3};
    EXPECT_EQ(
      *itr,
      (std::tuple<const Type0, const Type1>{type0,type1})
    );
    EXPECT_EQ(
      *itr++,
      (std::tuple<const Type0, const Type1>{type0,type1})
    );
    EXPECT_EQ(
      itr,
      typeset.end()
    );
  }
}
