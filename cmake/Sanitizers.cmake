
function(add_sanitizer_flags)

    if (NOT ${ENABLE_SANITIZE_ADDR} AND NOT ${ENABLE_SANITIZE_UNDEF})
        message(STATUS "Sanitizers deactivated")
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "CLANG" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_options("-fno-omit-frame-pointer")
        add_link_options("-fno-omit-frame-pointer")

        if (${ENABLE_SANITIZE_ADDR})
            add_compile_options("-fsanitize=address")
            add_link_options("-fsanitize=address")
        endif()

        if (${ENABLE_SANITIZE_UNDEF})
            add_compile_options("-fsanitize=undefined")
            add_link_options("-fsanitize=undefined")
        endif()

        if (${ENABLE_SANITIZE_LEAK})
            add_compile_options("-fsanitize=leak")
            add_link_options("-fsanitize=leak")
        endif()

        if (${ENABLE_SANITIZE_THREAD})
            add_compile_options("-fsanitize=thread")
            add_link_options("-fsanitize=thread")
        endif()

    elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        if (${ENABLE_SANITIZE_ADDR})
            add_compile_options("/fsanitize=address")
        endif()

        if(${ENABLE_SANITIZE_UNDEF})
            message(STATUS "Undefined sanitizer is not supported by MSVC")
        endif()


    else()
        message(ERROR "Unsupported compiler for Sanitizers")
    endif()

endfunction(add_sanitizer_flags)
