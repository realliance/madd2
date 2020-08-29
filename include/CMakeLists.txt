set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd2
    PRIVATE
        "${DIR}/component_heap.h"
        "${DIR}/component_heap_iterator_base.h"
        "${DIR}/madd.h"
        "${DIR}/madd_base.h"
        "${DIR}/maybe.h"
        "${DIR}/system.h"
        "${DIR}/status.h"
)
target_include_directories(madd2 PRIVATE "${madd2_SOURCE_DIR}/include")
