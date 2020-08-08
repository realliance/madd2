#include <gtest/gtest.h>
#include "component_heap.h"
#include "heap_entry.h"

typedef struct{} Type0;
typedef struct{} Type1;

TEST(ComponentHeap, Insert){
  // Arrange
  Heap heap;
  Entity entity = 0;
  ComponentType componentType = 0;
  HeapEntry component = HeapEntry(new Type0, 0);

  // Act
  heap.insert(entity, componentType, new Type0);

  // Assert
  ASSERT_EQ(
    heap.data()->at(componentType).size(),
    1
  );
}

TEST(ComponentHeap, Erase){
  // Arrange
  Heap heap;
  Entity entity = 0;
  ComponentType componentType = 0;
  (*heap.data())[componentType][entity] = std::move(HeapEntry(new Type0, 0));
  (*heap.data())[componentType][entity+1] = std::move(HeapEntry(new Type0, 1));

  // Act
  heap.erase(entity, componentType);

  // Assert
  EXPECT_EQ(
    heap.data()->at(componentType).find(entity),
    heap.data()->at(componentType).end()
  );
  EXPECT_NO_THROW(heap.erase(-1, -1));
}

TEST(ComponentHeap, Clear){
  // Arrange
  Heap heap;
  Entity entity = 0;
  ComponentType componentType = 0;
  (*heap.data())[componentType][entity] = std::move(HeapEntry(new Type0, 0));
  (*heap.data())[componentType][entity+1] = std::move(HeapEntry(new Type0, 1));

  // Act
  heap.clear();

  // Assert
  EXPECT_EQ(
    heap.data()->size(),
    0
  );
}
