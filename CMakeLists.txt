cmake_minimum_required(VERSION 2.8)
project(restHttp LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("CMAKE_CXX_COMPILER_ID :: ${CMAKE_CXX_COMPILER_ID}")

#load dependencies using conan package manager...
include(conanbuildinfo.cmake)
conan_basic_setup()

set(Boost_USE_STATIC_LIBS ON)
set(OPENSSL_USE_STATIC_LIBS ON)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    # using Clang
  set(BV 1.73.0)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  # using GCC
  set(BV 1.70.0)
  include(conanbuildinfo.cmake)
  message("CONAN_BOOST_ROOT ${CONAN_BOOST_ROOT} ${BV}")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    # using Visual Studio C++
  set(BV 1.67.0)
  set(crypt32_lib crypt32.lib)
endif()
message("CONAN_BOOST_ROOT ${CONAN_BOOST_ROOT}")
set(OPENSSL_ROOT_DIR ${CONAN_OPENSSL_ROOT})
set(OPENSSL_INCLUDE_DIR ${CONAN_INCLUDE_DIRS_OPENSSL})
set(OPEN_SSL_LIB_DIR ${CONAN_LIB_DIRS_OPENSSL})
message("Boost_INCLUDE_DIRS  ${Boost_INCLUDE_DIRS}")
find_package(Boost ${BV} REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED COMPONENTS Crypto SSL)
find_package(Boost ${BV} REQUIRED COMPONENTS system)


add_executable (${PROJECT_NAME}
        "src/main.cpp"
        "src/include/request/requestdata.h"
        "src/request/requestdata.cpp"
        "src/include/request/requestor.h"
        "src/request/requestor.cpp"
        "src/include/request/asyncrequestor.h"
        "src/request/asyncrequestor.cpp"
        "src/include/response/responsedata.h"
        "src/response/responsedata.cpp"
        )

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} Boost::system ${ws2_32_lib} OpenSSL::SSL OpenSSL::Crypto ${crypt32_lib})

if(WIN32)
    # We have to set _WIN32_WINNT for Asio
    if(${CMAKE_SYSTEM_VERSION} EQUAL 10) # Windows 10,
        add_definitions(-D _WIN32_WINNT=0x0A00)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.3) # Windows 8.1
        add_definitions(-D _WIN32_WINNT=0x0603)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.2) # Windows 8
        add_definitions(-D _WIN32_WINNT=0x0602)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.1) # Windows 7
        add_definitions(-D _WIN32_WINNT=0x0601)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.0) # Windows Vista
        add_definitions(-D _WIN32_WINNT=0x0600)
    else() # Windows XP (5.1)
        add_definitions(-D _WIN32_WINNT=0x0501)
    endif()
endif()
