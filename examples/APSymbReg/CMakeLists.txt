cmake_minimum_required(VERSION 2.8)
project(APSymbReg)

# try setting dir manually if environment variable is not set
set(BOOST_ROOT "C:/misc/boost_1_81_0")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")

find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

set(SOURCE_FILES
        main.cpp
        SymbRegEvalOp.cpp
        SymbRegEvalOpAP.cpp
        utility/expression_evaluation.cpp
        utility/fileparser.cpp
        utility/measures.cpp
        utility/utility.cpp)

include_directories(../../)
add_executable(APSymbReg ${SOURCE_FILES})

if (MINGW)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(APSymbReg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../debug/libECF.a)
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_link_libraries(APSymbReg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../release/libECF.a)
    else ()
        target_link_libraries(APSymbReg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../test/libECF.a)
    endif ()
else ()
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(APSymbReg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../debug/ECF.lib)
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_link_libraries(APSymbReg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../release/ECF.lib)
    else ()
        target_link_libraries(APSymbReg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../test/ECF.lib)
    endif ()
endif ()
