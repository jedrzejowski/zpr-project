#include(CTest)

enable_testing()

## Object

add_executable(test_lib_object
        test/lib/object.cpp
        src/lib/object.cpp)

add_test(lib_object test_lib_object)
target_link_libraries(test_lib_object ${LIBRARIES})

## BackWorkerQueue

add_executable(test_lib_backWorkerQueue
        test/lib/backWorkerQueue.cpp
        src/lib/backWorkerQueue.cpp)

add_test(lib_backWorkerQueue test_lib_backWorkerQueue)
target_link_libraries(test_lib_backWorkerQueue ${LIBRARIES})

