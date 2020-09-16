set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd2
    PRIVATE
        "${DIR}/component_heap.cpp"
        "${DIR}/component_heap_iterator_base.cpp"
        "${DIR}/madd.cpp"
        "${DIR}/status.cpp"
)
