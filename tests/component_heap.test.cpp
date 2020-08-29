#include <gtest/gtest.h>
#include "component_heap.h"

typedef struct{} Type0;
typedef struct{} Type1;
inline bool operator==(const Type0& lhs, const Type0& rhs){ return true;}
inline bool operator==(const Type1& lhs, const Type1& rhs){ return true;}

TEST(ComponentHeap, Insert){
  // Arrange
  ComponentHeap heap;
  Entity entity = 0;

  // Act
  heap.insert(entity, Type0{});
  heap.insert(entity, Type1{});

  // Assert
  ASSERT_EQ(
    heap.data()->size(),
    2
  );
  EXPECT_EQ(
    std::any_cast<Type0>(heap.data()->at(std::type_index(typeid(Type0))).at(entity)),
    Type0{}
  );
  EXPECT_EQ(
    std::any_cast<Type1>(heap.data()->at(std::type_index(typeid(Type1))).at(entity)),
    Type1{}
  );
}

TEST(ComponentHeap, Erase){
  // Arrange
  ComponentHeap heap;
  Entity entity = 0;
  std::type_index componentType = std::type_index(typeid(Type0));
  (*heap.data())[componentType][entity] = Type0{};
  (*heap.data())[componentType][entity+1] = Type0{};

  // Act
  heap.erase<Type0>(entity);

  // Assert
  EXPECT_EQ(
    heap.data()->at(componentType).find(entity),
    heap.data()->at(componentType).end()
  );
  EXPECT_NO_THROW(heap.erase<Type1>(-1));
}

TEST(ComponentHeap, Clear){
  // Arrange
  ComponentHeap heap;
  Entity entity = 0;
  std::type_index componentType = std::type_index(typeid(Type0));
  (*heap.data())[componentType][entity] = Type0{};
  (*heap.data())[componentType][entity+1] = Type0{};

  // Act
  heap.clear();

  // Assert
  EXPECT_EQ(
    heap.data()->size(),
    0
  );
}
