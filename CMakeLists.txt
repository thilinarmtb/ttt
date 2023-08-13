cmake_minimum_required(VERSION 3.23)
project(xxx VERSION 0.0.1 DESCRIPTION "" LANGUAGES C)

option(ENABLE_DOCS "Enable Documentation" OFF)

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

set(SOURCES src/xxx-impl.c)
add_library(xxx SHARED ${SOURCES})
set_target_properties(xxx PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1
  PUBLIC_HEADER include/xxx.h)
target_include_directories(xxx PRIVATE include)
target_compile_options(xxx PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>)

add_executable(xxx-driver bin/xxx-driver.c)
set_target_properties(xxx-driver PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(xxx-driver PRIVATE xxx)
target_include_directories(xxx-driver PRIVATE include)
target_compile_options(xxx-driver PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>)

if (ENABLE_DOCS)
  add_subdirectory ("docs")
endif()

find_program(CLANG_FORMAT NAMES clang-format)
if (CLANG_FORMAT)
  add_custom_target(format COMMAND ${CLANG_FORMAT} -i
    ${CMAKE_CURRENT_SOURCE_DIR}/*/*.[ch]
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running clang-format ...")
endif()

install(TARGETS xxx xxx-driver RUNTIME DESTINATION bin LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)

# Add clang-tidy to target properties if available.
find_program(CLANG_TIDY NAMES clang-tidy)
if (CLANG_TIDY)
  set_target_properties(xxx PROPERTIES C_CLANG_TIDY "${CLANG_TIDY}")
  set_target_properties(xxx-driver PROPERTIES C_CLANG_TIDY "${CLANG_TIDY}")
endif()

# Add AddressSanitizer if the build type is Debug.
if (CMAKE_BUILD_TYPE MATCHES Debug)
  include(CheckCCompilerFlag)
  check_c_compiler_flag("-fsanitize=address" HAS_ADDRESS_SANITIZER)
  if (HAS_ADDRESS_SANITIZER)
    target_compile_options(xxx PRIVATE -fsanitize=address)
    target_link_options(xxx PRIVATE -fsanitize=address)
    target_compile_options(xxx-driver PRIVATE -fsanitize=address)
    target_link_options(xxx-driver PRIVATE -fsanitize=address)
  endif()
endif()
