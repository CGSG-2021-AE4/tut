cmake_minimum_required(VERSION 3.20)
project(tut)

add_executable(${PROJECT_NAME}
  "src/main.cpp"
  "src/anim/input/input.cpp"
  "src/utility/resource.h"
  "src/utility/image.h"
  "src/utility/async.h"
  "src/def.h"
  "src/anim/anim.h"
  "src/anim/windows/windows.h"
  "src/tut.h"
  "src/anim/context.h" "src/units/unit_test.h")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)


target_include_directories(${PROJECT_NAME}
  PUBLIC "X:/SDL2-2.30.3/include"
  PUBLIC "${PORJECT_SOURCE_DIR}src"
)

target_link_libraries(${PROJECT_NAME} "X:/SDL2-2.30.3/lib/x64/SDL2main.lib" "X:/SDL2-2.30.3/lib/x64/SDL2.lib" )
