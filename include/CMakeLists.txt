set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd2
    PRIVATE
        "${DIR}/heap_entry.h"
        "${DIR}/component_heap.h"
        "${DIR}/types.h"
)
target_include_directories(madd2 PRIVATE "${madd2_SOURCE_DIR}/include")
