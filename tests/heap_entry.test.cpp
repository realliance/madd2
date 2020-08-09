#include <gtest/gtest.h>
#include "component_heap.h"
#include "heap_entry.h"

struct testObject{
  int a;
  float b;
};

inline bool operator==(const testObject& lhs, const testObject& rhs){
    return lhs.a == rhs.a && lhs.b == rhs.b;
}

TEST(HeapEntry, to_simple){
  // Arrange
  HeapEntry heapEntry(new int(7),0);

  // Act
  int ret = heapEntry.to<int>();
  
  // Assert
  ASSERT_EQ(
    ret,
    7
  );
}

TEST(HeapEntry, to_object){
  // Arrange
  HeapEntry heapEntry(new testObject{2,3.5},0);

  // Act
  heapEntry.to<testObject>();
  
  // Assert
  ASSERT_EQ(
    heapEntry.to<testObject>(),
    (testObject{2,3.5})
  );
}