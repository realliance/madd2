#include <gtest/gtest.h>
#include "component_heap.h"
#include "heap_entry.h"

typedef struct{} Type0;
typedef struct{} Type1;

TEST(ComponentHeap, Insert){
  // Arrange
  Heap heap;
  Entity entity = 0;

  // Act
  heap.insert(entity, new Type0);
  heap.insert(entity, new Type1);

  // Assert
  ASSERT_EQ(
    heap.data()->size(),
    2
  );
  EXPECT_EQ(
    heap.data()->at(std::type_index(typeid(Type0))).at(entity).componentId,
    0
  );
    EXPECT_EQ(
    heap.data()->at(std::type_index(typeid(Type1))).at(entity).componentId,
    1
  );
  EXPECT_NO_THROW(heap.data()->at(std::type_index(typeid(Type0))).at(entity).to<Type0>());
}

TEST(ComponentHeap, Erase){
  // Arrange
  Heap heap;
  Entity entity = 0;
  std::type_index componentType = std::type_index(typeid(Type0));
  (*heap.data())[componentType][entity] = HeapEntry(new Type0, 0);
  (*heap.data())[componentType][entity+1] = HeapEntry(new Type0, 1);

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
  Heap heap;
  Entity entity = 0;
  std::type_index componentType = std::type_index(typeid(Type0));
  (*heap.data())[componentType][entity] = HeapEntry(new Type0, 0);
  (*heap.data())[componentType][entity+1] = HeapEntry(new Type0, 1);

  // Act
  heap.clear();

  // Assert
  EXPECT_EQ(
    heap.data()->size(),
    0
  );
}
