#include <gtest/gtest.h>
#include <stdint.h>
#include "component_heap.h"
#include "heap_entry.h"

typedef struct{ComponentId componentId;} Type0;
typedef struct{ComponentId componentId;} Type1;

TEST(ComponentHeap, SingleType){
  // Arrange
  Heap heap;
  Entity entity = 0;
  std::vector<ComponentType> componentType = {0,1};
  (*heap.data())[componentType[0]][entity] = HeapEntry(new Type0{0},0);
  (*heap.data())[componentType[0]][entity+1] = HeapEntry(new Type0{1},1);
  (*heap.data())[componentType[1]][entity+2] = HeapEntry(new Type1{2},2);

  Heap::iterator itr = heap.begin(std::vector<ComponentType>{0});

  // Act, Assert
  ASSERT_EQ(
    itr,
    heap.begin(std::vector<ComponentType>{0}) 
  );
  EXPECT_EQ(
    (*itr)[0]->componentId,
    0
  );
  ASSERT_NE(
    ++itr,
    heap.end({std::vector<ComponentType>{0}})
  );
  EXPECT_EQ(
    (*itr)[0]->componentId,
    1
  );
  EXPECT_EQ(
    (*(itr++))[0]->componentId,
    1
  );
  EXPECT_EQ(
    itr,
    heap.end({std::vector<ComponentType>{0}})
  );

  // Arrange
  itr = heap.begin(std::vector<ComponentType>{2});

  // Act, Assert
  EXPECT_EQ(
    itr,
    heap.end(std::vector<ComponentType>{2})
  );
  EXPECT_NE(
    itr,
    heap.end(std::vector<ComponentType>{3})
  );
}

TEST(ComponentHeap, MultiType){
  // Arrange
  Heap heap;
  Entity entity = 0;
  std::vector<ComponentType> componentType = {0,1};
  (*heap.data())[componentType[0]][entity] = HeapEntry(new Type0{0},0);
  (*heap.data())[componentType[1]][entity] = HeapEntry(new Type1{1},1);
  (*heap.data())[componentType[0]][entity+1] = HeapEntry(new Type0{2},2);
  (*heap.data())[componentType[1]][entity+1] = HeapEntry(new Type1{3},3);
  (*heap.data())[componentType[0]][entity+2] = HeapEntry(new Type0{4},4);
  (*heap.data())[componentType[1]][entity+3] = HeapEntry(new Type1{5},5);

  Heap::iterator itr = heap.begin(componentType);

  // Act, Assert
  ASSERT_EQ(
    itr,   heap.begin(componentType)
  );
  EXPECT_EQ(
    (std::vector<ComponentId>{(*itr)[0]->componentId,(*itr)[1]->componentId}),
    (std::vector<ComponentId>{0,1})
  );
  ASSERT_NE(
    ++itr,
    heap.end(componentType)
  );
  EXPECT_EQ(
    (std::vector<ComponentId>{(*itr)[0]->componentId,(*itr)[1]->componentId}),
    (std::vector<ComponentId>{2,3})
  );
  auto heapVect = (*itr++);
  EXPECT_EQ(
    (std::vector<ComponentId>{heapVect[0]->componentId,heapVect[1]->componentId}),
    (std::vector<ComponentId>{2,3})
  );
  EXPECT_EQ(
    itr,
    heap.end(componentType)
  );

  //Arrange
  itr = heap.begin(std::vector<ComponentType>{1,2});

  // Act, Assert
  EXPECT_EQ(
    itr,
    heap.end(std::vector<ComponentType>{1,2})
  );
  EXPECT_NE(
    itr,
    heap.end(std::vector<ComponentType>{3,4,5})
  );
}