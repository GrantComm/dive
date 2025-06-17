#
# Copyright 2025 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(gfxr_ext)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /MP")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
  file(GLOB_RECURSE NATVIS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.natvis")
else()
  set(NATVIS_FILES "")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
  set(Python3_FIND_REGISTRY "NEVER")
endif()
if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
  find_program (Python3_EXECUTABLE python3)
else()
  find_package (Python3 COMPONENTS Interpreter)
endif()

if (NOT Python3_EXECUTABLE)
  message(FATAL_ERROR "python3 not found")
endif()

file(GLOB_RECURSE HDR_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(FILTER SRC_FILES EXCLUDE REGEX "_tests.cpp$")

add_library(${PROJECT_NAME} STATIC ${HDR_FILES} ${SRC_FILES}
  ${COMMON_HDR_FILES} ${COMMON_SRC_FILES} ${PM4_GENERATED_SRC_FILE} ${NATVIS_FILES} ${FREEDRENO_SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE gfxrecon_decode)
target_include_directories(${PROJECT_NAME} PRIVATE ${THIRDPARTY_DIRECTORY}/gfxreconstruct/framework)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  target_link_libraries(${PROJECT_NAME} PRIVATE dl)
  target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
  target_link_libraries(${PROJECT_NAME} PRIVATE z)
  target_link_libraries(${PROJECT_NAME} PRIVATE tinfo)
endif()

if (MSVC)
  # 4100: unreferenced formal parameter
  # 4201: prevent nameless struct/union
  # 4127: conditional expression is constant
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4100 /wd4201 /wd4127)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-braces -Wno-sign-compare -fPIC
    $<$<COMPILE_LANGUAGE:C>:-Wno-override-init>
  )
endif()
