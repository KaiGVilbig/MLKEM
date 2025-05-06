cmake_minimum_required(VERSION 3.10)
project(mlkem_lib)
set(CMAKE_CXX_STANDARD 17)

# Include BoringSSL as a subproject
add_subdirectory(external/boringssl)

# Find OpenSSL
find_package(OpenSSL REQUIRED)
message(STATUS "OpenSSL Version: ${OPENSSL_VERSION}")
message(STATUS "OpenSSL Include Dir: ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")

# Use BoringSSL if found
if(TARGET BoringSSL::ssl AND TARGET BoringSSL::crypto) # Check for the targets
    message(STATUS "BoringSSL Found as a subproject.")
    set(BORINGSSL_FOUND TRUE)
    set(BoringSSL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/boringssl/include) # set the include dirs
else()
    message(WARNING "BoringSSL not found as a subproject.  Will attempt to find system-installed BoringSSL.")
    find_package(BoringSSL QUIET)
    if(BoringSSL_FOUND)
         message(STATUS "BoringSSL Found: ${BoringSSL_LIBRARIES}")
         message(STATUS "BoringSSL Include Dir: ${BoringSSL_INCLUDE_DIR}")
         include_directories(${BoringSSL_INCLUDE_DIR})
    endif()
endif()

# Create a library for BoringSSL-based randomness
if(BORINGSSL_FOUND)
    add_library(boringssl_rand STATIC
        src/boringssl_rand.cpp
        include/boringssl_rand.h
    )
    target_link_libraries(boringssl_rand PRIVATE BoringSSL::ssl BoringSSL::crypto)
    target_include_directories(boringssl_rand PUBLIC ${BoringSSL_INCLUDE_DIR}) # Use the defined include
endif()

# Define the shared library
add_library(mlkem SHARED
    src/mlkem.cpp
    src/random.cpp
    src/ntt.cpp
    src/sampling.cpp
    src/byteEncode.cpp
    src/kpke.cpp
    src/mlkem_internal.cpp
    src/hash.cpp
    src/xof.cpp
    include/random.h
    include/ntt.h
    include/byteEncode.h
    include/kpke.h
    include/mlkem_internal.h
    include/hash.h
    include/xof.h
    tests/test.h
)

# Include directory
target_include_directories(mlkem PUBLIC include)
if(BORINGSSL_FOUND)
    target_link_libraries(mlkem PRIVATE boringssl_rand)
endif()
target_link_libraries(mlkem PRIVATE OpenSSL::Crypto)

# Add test executable
add_executable(mlkem_tests
    tests/test.cpp
    src/random.cpp
    src/ntt.cpp
    src/sampling.cpp
    src/byteEncode.cpp
    src/kpke.cpp
    src/mlkem_internal.cpp
    src/hash.cpp
    src/xof.cpp
    include/random.h
    include/ntt.h
    include/byteEncode.h
    include/kpke.h
    include/mlkem_internal.h
    include/hash.h
    include/xof.h
    tests/test.h
)

target_include_directories(mlkem_tests PRIVATE include)
if(BORINGSSL_FOUND)
    target_link_libraries(mlkem_tests PRIVATE boringssl_rand)
endif()
target_link_libraries(mlkem_tests PRIVATE mlkem OpenSSL::Crypto)
message(STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

# Set correct output file extensions
if(WIN32)
    set_target_properties(mlkem PROPERTIES SUFFIX ".dll")
else()
    set_target_properties(mlkem PROPERTIES SUFFIX ".so")
endif()
