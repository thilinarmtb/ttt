cmake_minimum_required(VERSION 3.24)
project(ttt VERSION 0.0.1 DESCRIPTION "" LANGUAGES C)

option(ENABLE_DOCS "Enable Documentation" OFF)
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

# https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/RPATH-handling
# Use, i.e. don't skip the full RPATH for the build tree.
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
# When building, don't use the install RPATH.
set(CMAKE_SKIP_BUILD_RPATH FALSE)
# Set the library location.
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# Add the automatically determined parts of the RPATH which point to directories
# outside the build tree to the install RPATH.
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(SOURCES src/ttt-impl.c src/ttt.c)
add_library(ttt SHARED ${SOURCES})
set_target_properties(ttt PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1
  PUBLIC_HEADER include/ttt.h)
target_include_directories(ttt PRIVATE include)
target_compile_options(ttt PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>)

add_executable(ttt-driver bin/ttt-driver.c)
set_target_properties(ttt-driver PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(ttt-driver PRIVATE ttt)
target_include_directories(ttt-driver PRIVATE include)
target_compile_options(ttt-driver PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>)

if (ENABLE_DOCS)
  add_subdirectory ("docs")
endif()

# Add clang-format as a custom target if available.
find_program(CLANG_FORMAT NAMES clang-format)
if (CLANG_FORMAT)
  add_custom_target(format
    COMMAND ${CLANG_FORMAT} -i ${CMAKE_CURRENT_SOURCE_DIR}/*/*.[ch]
    COMMENT "Running clang-format ...")
  add_custom_target(format-check
    COMMAND ${CLANG_FORMAT} --dry-run -Werror -i ${CMAKE_CURRENT_SOURCE_DIR}/*/*.[ch]
    COMMENT "Running clang-format check ...")
endif()

# Add clang-tidy as a custom target if available.
find_program(CLANG_TIDY NAMES clang-tidy)
if (CLANG_TIDY)
  add_custom_target(tidy
    COMMAND ${CLANG_TIDY} -p ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*/*.[ch]
    COMMENT "Running clang-tidy ...")
endif()

# Turn on AddressSanitizer if ENABLE_ASAN is set.
if (ENABLE_ASAN)
  include(CheckLinkerFlag)
  check_linker_flag(C -fsanitize=address HAS_ADDRESS_SANITIZER)
  if (HAS_ADDRESS_SANITIZER)
    target_compile_options(ttt PRIVATE -fsanitize=address)
    target_link_options(ttt PRIVATE -fsanitize=address)
    target_compile_options(ttt-driver PRIVATE -fsanitize=address)
    target_link_options(ttt-driver PRIVATE -fsanitize=address)
  else()
    message(FATAL_ERROR "AddressSanitizer is enabled but not supported.")
  endif()
endif()

install(TARGETS ttt ttt-driver RUNTIME DESTINATION bin LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)
