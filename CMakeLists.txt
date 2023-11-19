cmake_minimum_required(VERSION 3.25)
project(pr1)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()


#task 1
add_executable(t1_t1 t1/t1_t1.cpp)
add_executable(t1_t2 t1/t2_t2.cpp)
add_executable(t1_t3 t1/t3_t3.cpp)
add_executable(t1_t4 t1/t4_t4.cpp)
add_executable(t1_t5 t1/t5_t5.cpp)

#task 2
add_executable(t2_t1 t2/t2_t1.cpp)
add_executable(t2_t2_1 t2/t2_t2.cpp)
add_executable(t2_t2_2 t2/t2_t2_2.cpp)
add_executable(main t2/main.cpp)