cmake_minimum_required(VERSION 3.10)
project(SimpleWebScraper)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

add_executable(SimpleWebScraper src/main.cpp src/scraper.cpp)

target_include_directories(SimpleWebScraper PUBLIC
        path_to_vcpkg/installed/your_triplet/include
)

target_link_libraries(SimpleWebScraper PUBLIC
        path_to_vcpkg/installed/your_triplet/lib/libcurl.a
        path_to_vcpkg/installed/your_triplet/lib/libgumbo.a
        path_to_vcpkg/installed/your_triplet/lib/libz.a
        path_to_vcpkg/installed/your_triplet/lib/libssl.a
        path_to_vcpkg/installed/your_triplet/lib/libcrypto.a
)
