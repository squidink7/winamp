		if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
    mark_as_advanced(CLANG_TIDY_EXECUTABLE)
		
    if (${CLANG_TIDY_EXECUTABLE})
message(FATAL_ERROR "Clang-tidy not found")
    else()
message(STATUS "Enabling clang-tidy")
set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};-warnings-as-errors=*")
    endif()
		else()
    message(FATAL_ERROR "Clang-tidy is not supported when building for windows")
		endif()
		