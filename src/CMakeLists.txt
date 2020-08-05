set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(maddv2
    PRIVATE
        "${DIR}/component_heap.cpp"
        "${DIR}/component_heap_iterator.cpp"
        "${DIR}/heap_entry.cpp"
)
