file(GLOB TESTS test_???_*.c)

foreach(test ${TESTS})
  string(REPLACE "${CMAKE_SOURCE_DIR}/tests/" "" temp ${test})
  string(REPLACE ".c" "" test_exe ${temp})
  add_executable(${test_exe} ${test})
  target_link_libraries(${test_exe} ttt)
  target_include_directories(${test_exe} PRIVATE ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests)
  target_compile_options(${test_exe} PRIVATE
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>)
  if (SUPPORTS_ADDRESS_SANITIZER)
    target_compile_options(${test_exe} PRIVATE -fsanitize=address)
    target_link_options(${test_exe} PRIVATE -fsanitize=address)
  endif()
  install (TARGETS ${test_exe} RUNTIME DESTINATION
    ${CMAKE_INSTALL_PREFIX}/tests)
endforeach()
