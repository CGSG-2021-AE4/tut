cmake_minimum_required(VERSION 3.20)

# Setup vcpkg
# set(CMAKE_TOOLCHAIN_FILE X:/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE FILEPATH "")
# Create project
project(tut)

# Add files
file(GLOB_RECURSE APP_SOURCE
  "src/*.cpp"
)

# Add executable
add_executable(${PROJECT_NAME} ${APP_SOURCE})

# Add include dir
target_include_directories(${PROJECT_NAME} PUBLIC ./src/)

# Setup language
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

# Setup libs
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
  $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)
find_package(SDL2_ttf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
  $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)

