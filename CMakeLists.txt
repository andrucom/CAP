﻿# CMakeList.txt: проект CMake для CAP; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CAP")


if (MSVC)
    # Для Visual Studio (начиная с VS 2015)
    add_compile_options("/utf-8")
else()
    # Для GCC, Clang и других Unix-компиляторов
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

add_executable (CAP "CAP.cpp"  "third_party/CAPL/capl.cpp")
target_link_libraries(CAP PRIVATE lfreist-hwinfo::hwinfo)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CAP PROPERTY CXX_STANDARD 20)

endif()

if (WIN32)
    target_link_libraries(CAP PRIVATE kernel32)
endif()

set(target_h capl.h)
set(target_cpp capl.cpp)

add_subdirectory(third_party/hwinfo)
include_directories(third_party/hwinfo/include)