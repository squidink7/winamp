			include(CheckCXXCompilerFlag)
			include(CheckCXXSourceRuns)
			
			set(ALLOWED_BUILD_TYPES Debug Release RelWithDebInfo MinSizeRel)
			set(ALL_SAN_FLAGS "")
			
            # No sanitizers when cross compiling to prevent stuff like this: https://github.com/whoshuu/cpr/issues/582
			if(NOT CMAKE_CROSSCOMPILING)
        # Thread sanitizer
        set(THREAD_SAN_FLAGS "-fsanitize=thread")
        set(PREV_FLAG ${CMAKE_REQUIRED_FLAGS})
        set(CMAKE_REQUIRED_FLAGS "${THREAD_SAN_FLAGS}")
        check_cxx_source_runs("int main() { return 0; }" THREAD_SANITIZER_AVAILABLE)
        set(CMAKE_REQUIRED_FLAGS ${PREV_FLAG})
        if(THREAD_SANITIZER_AVAILABLE)
    list(APPEND ALLOWED_BUILD_TYPES ThreadSan)
    # Do not add Thread sanitizer to all sanitizer because it is incompatible with other sanitizer
        endif()
        set(CMAKE_C_FLAGS_THREADSAN "${CMAKE_C_FLAGS_DEBUG} ${THREAD_SAN_FLAGS}" CACHE INTERNAL "Flags used by the C compiler during thread sanitizer builds." FORCE)
        set(CMAKE_CXX_FLAGS_THREADSAN "${CMAKE_CXX_FLAGS_DEBUG} ${THREAD_SAN_FLAGS}" CACHE INTERNAL "Flags used by the C++ compiler during thread sanitizer builds." FORCE)
        set(CMAKE_SHARED_LINKER_FLAGS_THREADSAN "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE INTERNAL "Flags used for the linker during thread sanitizer builds" FORCE)
			
        # Address sanitizer
        set(ADDR_SAN_FLAGS "-fsanitize=address")
        set(PREV_FLAG ${CMAKE_REQUIRED_FLAGS})
        set(CMAKE_REQUIRED_FLAGS "${ADDR_SAN_FLAGS}")
        check_cxx_source_runs("int main() { return 0; }" ADDRESS_SANITIZER_AVAILABLE)
        set(CMAKE_REQUIRED_FLAGS ${PREV_FLAG})
        if(ADDRESS_SANITIZER_AVAILABLE)
    list(APPEND ALLOWED_BUILD_TYPES AddrSan)
    set(ALL_SAN_FLAGS "${ALL_SAN_FLAGS} ${ADDR_SAN_FLAGS}")
        endif()
        set(CMAKE_C_FLAGS_ADDRSAN "${CMAKE_C_FLAGS_DEBUG} ${ADDR_SAN_FLAGS} -fno-omit-frame-pointer -fno-optimize-sibling-calls" CACHE INTERNAL "Flags used by the C compiler during address sanitizer builds." FORCE)
        set(CMAKE_CXX_FLAGS_ADDRSAN "${CMAKE_CXX_FLAGS_DEBUG} ${ADDR_SAN_FLAGS} -fno-omit-frame-pointer -fno-optimize-sibling-calls" CACHE INTERNAL "Flags used by the C++ compiler during address sanitizer builds." FORCE)
        set(CMAKE_SHARED_LINKER_FLAGS_ADDRSAN "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE INTERNAL "Flags used for the linker during address sanitizer builds" FORCE)
			
        # Leak sanitizer
        set(LEAK_SAN_FLAGS "-fsanitize=leak")
        check_cxx_compiler_flag(${LEAK_SAN_FLAGS} LEAK_SANITIZER_AVAILABLE)
        if(LEAK_SANITIZER_AVAILABLE)
    list(APPEND ALLOWED_BUILD_TYPES LeakSan)
    set(ALL_SAN_FLAGS "${ALL_SAN_FLAGS} ${LEAK_SAN_FLAGS}")
        endif()
        set(CMAKE_C_FLAGS_LEAKSAN "${CMAKE_C_FLAGS_DEBUG} ${LEAK_SAN_FLAGS} -fno-omit-frame-pointer" CACHE INTERNAL "Flags used by the C compiler during leak sanitizer builds." FORCE)
        set(CMAKE_CXX_FLAGS_LEAKSAN "${CMAKE_CXX_FLAGS_DEBUG} ${LEAK_SAN_FLAGS} -fno-omit-frame-pointer" CACHE INTERNAL "Flags used by the C++ compiler during leak sanitizer builds." FORCE)
        set(CMAKE_SHARED_LINKER_FLAGS_LEAKSAN "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE INTERNAL "Flags used for the linker during leak sanitizer builds" FORCE)
			
        # Undefined behavior sanitizer
        set(UDEF_SAN_FLAGS "-fsanitize=undefined")
        check_cxx_compiler_flag(${UDEF_SAN_FLAGS} UNDEFINED_BEHAVIOUR_SANITIZER_AVAILABLE)
        if(UNDEFINED_BEHAVIOUR_SANITIZER_AVAILABLE)
    list(APPEND ALLOWED_BUILD_TYPES UdefSan)
    set(ALL_SAN_FLAGS "${ALL_SAN_FLAGS} ${UDEF_SAN_FLAGS}")
        endif()
        set(CMAKE_C_FLAGS_UDEFSAN "${CMAKE_C_FLAGS_DEBUG} ${UDEF_SAN_FLAGS}" CACHE INTERNAL "Flags used by the C compiler during undefined behaviour sanitizer builds." FORCE)
        set(CMAKE_CXX_FLAGS_UDEFSAN "${CMAKE_CXX_FLAGS_DEBUG} ${UDEF_SAN_FLAGS}" CACHE INTERNAL "Flags used by the C++ compiler during undefined behaviour sanitizer builds." FORCE)
        set(CMAKE_SHARED_LINKER_FLAGS_UDEFSAN "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE INTERNAL "Flags used for the linker during undefined behaviour sanitizer builds" FORCE)
			
        # All sanitizer (without thread sanitizer)
        if(NOT ALL_SAN_FLAGS STREQUAL "")
    set(PREV_FLAG ${CMAKE_REQUIRED_FLAGS})
    set(CMAKE_REQUIRED_FLAGS "${ALL_SAN_FLAGS}")
    check_cxx_source_runs("int main() { return 0; }" ALL_SANITIZERS_AVAILABLE)
    set(CMAKE_REQUIRED_FLAGS ${PREV_FLAG})
    if(ALL_SANITIZERS_AVAILABLE)
list(APPEND ALLOWED_BUILD_TYPES AllSan)
    endif()
        endif()
			
        set(CMAKE_C_FLAGS_ALLSAN "${CMAKE_C_FLAGS_DEBUG} ${ALL_SAN_FLAGS} -fno-omit-frame-pointer -fno-optimize-sibling-calls" CACHE INTERNAL "Flags used by the C compiler during most possible sanitizer builds." FORCE)
        set(CMAKE_CXX_FLAGS_ALLSAN "${CMAKE_CXX_FLAGS_DEBUG} ${ALL_SAN_FLAGS} -fno-omit-frame-pointer -fno-optimize-sibling-calls" CACHE INTERNAL "Flags used by the C++ compiler during most possible sanitizer builds." FORCE)
        set(CMAKE_SHARED_LINKER_FLAGS_ALLSAN "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE INTERNAL "Flags used for the linker during most possible sanitizer builds" FORCE)
			endif()
			