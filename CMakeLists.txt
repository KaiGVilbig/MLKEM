cmake_minimum_required(VERSION 3.10)

project(mlkem_lib)

set(CMAKE_CXX_STANDARD 17)

# Define the shared library
add_library(mlkem SHARED src/mlkem.cpp "include/random.h" "src/random.cpp" "include/ntt.h" "src/ntt.cpp" "src/sampling.cpp"   "include/byteEncode.h" "src/byteEncode.cpp" "include/kpke.h" "src/kpke.cpp"  "include/mlkem_internal.h" "src/mlkem_internal.cpp" "include/hash.h" "src/hash.cpp" "include/xof.h" "src/xof.cpp")

# Include directory
target_include_directories(mlkem PUBLIC include)

# Add OpenSSL library
find_package(OpenSSL REQUIRED)
message(STATUS "OpenSSL Version: ${OPENSSL_VERSION}")
message(STATUS "OpenSSL Include Dir: ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")
target_link_libraries(mlkem PRIVATE OpenSSL::Crypto)

# Add test executable
add_executable(mlkem_tests tests/test.cpp "src/random.cpp" "include/ntt.h" "src/ntt.cpp" "src/sampling.cpp"   "include/byteEncode.h" "src/byteEncode.cpp" "include/kpke.h" "src/kpke.cpp"  "include/mlkem_internal.h" "src/mlkem_internal.cpp" "include/hash.h" "src/hash.cpp" "include/xof.h" "src/xof.cpp")

target_include_directories(mlkem_tests PRIVATE include)
target_link_libraries(mlkem_tests PRIVATE mlkem)
target_link_libraries(mlkem_tests PRIVATE OpenSSL::Crypto)

# Set correct output file extensions
if(WIN32)
    set_target_properties(mlkem PROPERTIES SUFFIX ".dll")
else()
    set_target_properties(mlkem PROPERTIES SUFFIX ".so")
endif()
