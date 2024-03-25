cmake_minimum_required(VERSION 3.15)
project(Lab_1_data_base_in_files_)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab_1_data_base_in_files_ main.cpp db/models/Product.cpp db/models/Product.h db/Functions.cpp db/Functions.h cli/Mode.cpp cli/Mode.h db/utils/Sorts.cpp db/utils/Sorts.h)