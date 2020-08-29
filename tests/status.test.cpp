#include <gtest/gtest.h>
#include <string>
#include "status.h"

TEST(HeapEntry, StatusCodeToStr){
  //Arrange
  std::string failure = StatusCodeToStr(StatusCode::LAST_STATUS_CODE);
  for(size_t i = 0; i < StatusCode::LAST_STATUS_CODE; i++){
    ASSERT_NE(
      //Act
      StatusCodeToStr(static_cast<StatusCode>(i)),
      //Assert
      failure
    );
  }
}
