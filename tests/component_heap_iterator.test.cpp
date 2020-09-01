#include <gtest/gtest.h>
#include <stdint.h>
#include <typeindex>
#include <vector>
#include <tuple>
#include "component_heap.h"
#include "base_test_types.h"

TEST(ComponentHeap, SingleType){
  // Arrange
  ComponentHeap heap;
  Entity entity = 0;
  std::vector<std::type_index> componentType = {std::type_index(typeid(Type0)),std::type_index(typeid(Type1))};
  Type0 type0{0};
  Type0 type0_1{1};
  (*heap.data())[componentType[0]][entity]   = type0;
  (*heap.data())[componentType[0]][entity+1] = type0_1;
  (*heap.data())[componentType[1]][entity+2] = Type1{2};
  ComponentHeap::TypeSet typeset = heap.toTypeSet<Type0>();
  ComponentHeap::const_iterator itr = typeset.begin();

  // Act, Assert
  ASSERT_EQ(
    itr,
    typeset.begin()
  );
  EXPECT_EQ(
    std::get<0>(*itr),
    type0
  );
  ASSERT_NE(
    ++itr,
    typeset.end()
  );
  EXPECT_EQ(
    std::get<0>(*itr),
    type0_1
  );
  EXPECT_EQ(
    std::get<0>(*(itr++)),
    type0_1
  );
  EXPECT_EQ(
    itr,
    typeset.end()
  );
}

TEST(ComponentHeap, MultiType){
  // Arrange
  ComponentHeap heap;
  Entity entity = 0;
  std::vector<std::type_index> componentType = {
    std::type_index(typeid(Type0)),
    std::type_index(typeid(Type1)),
    std::type_index(typeid(Type2)),
    std::type_index(typeid(Type3))};
  (*heap.data())[componentType[0]][entity]   = Type0{0};
  (*heap.data())[componentType[1]][entity]   = Type1{1};
  (*heap.data())[componentType[2]][entity]   = Type2{2};
  (*heap.data())[componentType[3]][entity]   = Type3{3};

  (*heap.data())[componentType[0]][entity+1] = Type0{4};
  (*heap.data())[componentType[1]][entity+1] = Type1{5};
  (*heap.data())[componentType[2]][entity+1] = Type2{6};
  (*heap.data())[componentType[3]][entity+1] = Type3{7};

  (*heap.data())[componentType[0]][entity+2] = Type0{8};

  (*heap.data())[componentType[1]][entity+3] = Type1{9};

  (*heap.data())[componentType[0]][entity+4] = Type0{10};
  (*heap.data())[componentType[1]][entity+4] = Type1{11};
  (*heap.data())[componentType[2]][entity+4] = Type2{12};
  (*heap.data())[componentType[3]][entity+4] = Type3{13};

  {
    ComponentHeap::TypeSet typeset = heap.toTypeSet<Type0,Type1>();
    ComponentHeap::const_iterator itr = typeset.begin();
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
    type0 = {4};
    type1 = {5};
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

  {
    ComponentHeap::TypeSet typeset = heap.toTypeSet<Type0,Type1,Type2,Type3>();
    ComponentHeap::const_iterator itr = typeset.begin();
    Type0 type0;
    Type1 type1;
    Type2 type2;
    Type3 type3;

    // Act, Assert
    ASSERT_EQ(
      itr,
      typeset.begin()
    );
    type0 = {0};
    type1 = {1};
    type2 = {2};
    type3 = {3};
    EXPECT_EQ(
      *itr,
      (std::tuple<const Type0, const Type1, const Type2, const Type3>{type0,type1,type2,type3})
    );
    ASSERT_NE(
      ++itr,
      typeset.end()
    );
    type0 = {4};
    type1 = {5};
    type2 = {6};
    type3 = {7};
    EXPECT_EQ(
      *itr,
      (std::tuple<const Type0, const Type1, const Type2, const Type3>{type0,type1,type2,type3})
    );
    ASSERT_NE(
      ++itr,
      typeset.end()
    );
    type0 = {10};
    type1 = {11};
    type2 = {12};
    type3 = {13};
    EXPECT_EQ(
      *itr,
      (std::tuple<const Type0, const Type1, const Type2, const Type3>{type0,type1,type2,type3})
    );
    EXPECT_EQ(
      ++itr,
      typeset.end()
    );
  }
}
