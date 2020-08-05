#include <gtest/gtest.h>
#include "component_heap.h"
#include "heap_entry.h"

TEST(ComponentHeap, Insert){
  // Arrange
  Heap heap;
  Entity entity = 0;
  ComponentType componentType = 0;

  // Act
  heap.insert(entity, componentType, HeapEntry{});

  // Assert
  EXPECT_EQ(heap.data()->at(componentType).find(entity), heap.begin(componentType));
}

TEST(ComponentHeap, Erase){
  // Arrange
  Heap heap;
  Entity entity = 0;
  ComponentType componentType = 0;
  (*heap.data())[componentType][entity] = HeapEntry{entity, componentType};
  (*heap.data())[componentType][entity+1] = HeapEntry{entity+1, componentType};

  // Act
  heap.erase(entity, componentType);

  // Assert
  EXPECT_EQ(heap.data()->at(componentType).find(entity), heap.end(componentType));
  EXPECT_NO_THROW(heap.erase(-1, -1));
}

TEST(ComponentHeap, Find){
  // Arrange
  Heap heap;
  Entity entity = 0;
  ComponentType componentType = 0;
  (*heap.data())[componentType][entity] = HeapEntry{entity, componentType};
  (*heap.data())[componentType][entity+1] = HeapEntry{entity+1, componentType};

  // Act
  auto itr = heap.find(entity,componentType);
  auto notfoundItr = heap.find(entity+2,componentType);

  // Assert
  ASSERT_NE(itr, heap.end(componentType));
  EXPECT_EQ(itr->second, (HeapEntry{entity,componentType}));
  EXPECT_EQ(notfoundItr, heap.end(componentType));
}

TEST(ComponentHeap, Clear){
  // Arrange
  Heap heap;
  Entity entity = 0;
  ComponentType componentType = 0;
  (*heap.data())[componentType][entity] = HeapEntry{entity, componentType};
  (*heap.data())[componentType][entity+1] = HeapEntry{entity+1, componentType};

  // Act
  heap.clear();

  // Assert
  EXPECT_EQ(heap.data()->at(componentType).find(entity), heap.end(componentType));
}
