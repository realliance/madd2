set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(maddv2
    PRIVATE
        "${DIR}/component_heap.h"
        "${DIR}/heap_entry.h"
        "${DIR}/types.h"
)
target_include_directories(maddv2 PRIVATE "${maddv2_SOURCE_DIR}/include")
