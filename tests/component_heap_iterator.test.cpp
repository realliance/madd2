#include <gtest/gtest.h>
#include "component_heap.h"
#include "heap_entry.h"

TEST(ComponentHeap, SingleType){
  // Arrange
  Heap heap;
  Entity entity = 0;
  std::vector<ComponentType> componentType = {0,1};
  (*heap.data())[componentType[0]][entity] = HeapEntry{0, componentType[0]};
  (*heap.data())[componentType[0]][entity+1] = HeapEntry{1, componentType[0]};
  (*heap.data())[componentType[1]][entity+2] = HeapEntry{2, componentType[1]};

  Heap::iterator itr = heap.begin(std::vector<ComponentType>{0});

  ASSERT_EQ(  itr,   heap.begin(std::vector<ComponentType>{0}));
  EXPECT_EQ( *itr,   (std::vector{HeapEntry{0, componentType[0]}}));
  ASSERT_NE(++itr, heap.end({std::vector<ComponentType>{0}}));
  EXPECT_EQ( *itr,   (std::vector{HeapEntry{1, componentType[0]}}));
  EXPECT_EQ(*(itr++),  (std::vector{HeapEntry{1, componentType[0]}}));
  EXPECT_EQ(  itr,   heap.end({std::vector<ComponentType>{0}}));

  itr = heap.begin(std::vector<ComponentType>{2});

  EXPECT_EQ(itr, heap.end(std::vector<ComponentType>{2}));
  EXPECT_NE(itr, heap.end(std::vector<ComponentType>{3}));
}

TEST(ComponentHeap, MultiType){
  // Arrange
  Heap heap;
  Entity entity = 0;
  std::vector<ComponentType> componentType = {0,1};
  (*heap.data())[componentType[0]][entity] = HeapEntry{entity, componentType[0]};
  (*heap.data())[componentType[1]][entity] = HeapEntry{entity, componentType[1]};
  (*heap.data())[componentType[0]][entity+1] = HeapEntry{entity+1, componentType[0]};
  (*heap.data())[componentType[1]][entity+1] = HeapEntry{entity+1, componentType[1]};
  (*heap.data())[componentType[0]][entity+2] = HeapEntry{entity+2, componentType[0]};
  (*heap.data())[componentType[1]][entity+3] = HeapEntry{entity+3, componentType[1]};

  Heap::iterator itr = heap.begin(componentType);

  ASSERT_EQ(  itr,   heap.begin(componentType));
  EXPECT_EQ( *itr,   (std::vector{HeapEntry{0, componentType[0]},HeapEntry{0, componentType[1]}}));
  ASSERT_NE(++itr, heap.end(componentType));
  EXPECT_EQ( *itr,   (std::vector{HeapEntry{1, componentType[0]},HeapEntry{1, componentType[1]}}));
  EXPECT_EQ(*(itr++),  (std::vector{HeapEntry{1, componentType[0]},HeapEntry{1, componentType[1]}}));
  EXPECT_EQ(  itr,   heap.end(componentType));

  itr = heap.begin(std::vector<ComponentType>{1,2});

  EXPECT_EQ(itr, heap.end(std::vector<ComponentType>{1,2}));
  EXPECT_NE(itr, heap.end(std::vector<ComponentType>{3,4,5}));
}