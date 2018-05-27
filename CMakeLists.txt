cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++") 

project(RestHttp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  set(BV 1.65.0)
  set(ws2_32_lib ws2_32)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(BV 1.67.0)
  # using Visual Studio C++
  include(conanbuildinfo.cmake)
  conan_basic_setup()
endif()

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost ${BV} REQUIRED COMPONENTS system)

add_executable (resthttp "main.cpp" "requestor.cpp" "requestdata.cpp" "responsedata.cpp")
message("Boost_INCLUDE_DIRS  ${Boost_INCLUDE_DIRS}")
target_include_directories(resthttp PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(resthttp Boost::system ${ws2_32_lib})

set(OUTDIR "../../RestHttpx")

include_directories(${CMKAKE_CURRENT_SOURCES_DIR})


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTDIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTDIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTDIR}/bin")
set(CMAKE_BINARY_DIR "${OUTDIR}/out")


message("CMKAKE_CURRENT_SOURCES_DIR dir is ${CMKAKE_CURRENT_SOURCES_DIR}")

set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard
#use latest standard and enable all warnings..
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

#add_library (resthttp STATIC "requester.cpp" "requestdata.cpp")
#STATIC|SHARED|MODULE
#There are three types of library that you can build:
#   STATIC builds a static library, i.e. a library that gets embedded into whichever executable decides to use it.
#  SHARED builds a shared library (.so on Linux, .dll on Windows).
#  MODULE builds a plugin library — something that you do not link against, but can load dynamically at runtime. 

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
