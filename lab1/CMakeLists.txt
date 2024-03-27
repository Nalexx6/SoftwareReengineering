cmake_minimum_required(VERSION 3.15)
project(Lab_1_data_base_in_files_)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab_1_data_base_in_files_ main.cpp db/models/Product.cpp db/models/Product.h db/service/ProductsService.cpp db/service/ProductsService.h cli/Mode.cpp cli/Mode.h utils/Sorts.cpp utils/Sorts.h
        cli/commands/Commands.cpp
        cli/commands/Commands.h)