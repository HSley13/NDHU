cmake_minimum_required(VERSION 3.29.2)
project(BankingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 6.7.0 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE ON)

target_link_libraries(${PROJECT_NAME} PRIVATE database_library)

add_subdirectory(database/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                            COMMAND ${CMAKE_COMMAND} -E copy
                            $<TARGET_FILE:${PROJECT_NAME}>
                            ${CMAKE_SOURCE_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
                    )
