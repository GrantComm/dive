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

# --- DivePlugin Sample ---
# This is a plugin demonstrating the IDivePlugin interface.
# It still needs Qt Widgets because it modifies a Qt UI (MainWindow).
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_library(dive_plugin_sample SHARED plugin_sample.h plugin_sample.cpp)

target_link_libraries(
    dive_plugin_sample
    PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets dive_plugin_abi_includes
)

set_property(TARGET dive_plugin_sample PROPERTY AUTOMOC ON)

target_include_directories(
    dive_plugin_sample
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}/dive_core
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

if(APPLE)
    set_target_properties(
        dive_plugin_sample
        PROPERTIES
            MACOSX_RPATH ON
            # Look for frameworks relative to the executable.
            INSTALL_RPATH "@loader_path/../../Frameworks"
            BUILD_WITH_INSTALL_RPATH TRUE
    )

    # On macOS, libraries linked from package managers like Homebrew often have hardcoded
    # absolute paths. To make the plugin portable, we need to modify these paths
    # within the built binary to use @rpath, so they resolve using the RPATH settings above.

    # Common base path for Qt 5 libraries installed via Homebrew.
    set(MY_QT5_HOMEBREW_LIB_PATH "/opt/homebrew/opt/qt@5/lib")

    # List of Qt frameworks to re-path.
    set(QT_FRAMEWORKS "QtCore" "QtGui" "QtWidgets")

    # Loop through the frameworks and add custom commands to update their paths.
    foreach(FRAMEWORK ${QT_FRAMEWORKS})
        set(ORIGINAL_FRAMEWORK_PATH
            "${MY_QT5_HOMEBREW_LIB_PATH}/${FRAMEWORK}.framework/Versions/5/${FRAMEWORK}"
        )
        set(NEW_FRAMEWORK_PATH
            "@rpath/${FRAMEWORK}.framework/Versions/5/${FRAMEWORK}"
        )

        add_custom_command(
            TARGET dive_plugin_sample
            POST_BUILD
            COMMAND
                ${CMAKE_INSTALL_NAME_TOOL} -change "${ORIGINAL_FRAMEWORK_PATH}"
                "${NEW_FRAMEWORK_PATH}" "$<TARGET_FILE:dive_plugin_sample>"
            COMMENT
                "Updating ${FRAMEWORK} library path in $<TARGET_FILE_NAME:dive_plugin_sample>"
            VERBATIM
        )
    endforeach()
else()
    set_target_properties(
        dive_plugin_sample
        PROPERTIES
            INSTALL_RPATH "$ORIGIN/../../host"
            BUILD_WITH_INSTALL_RPATH TRUE
            CXX_EXTENSIONS ON
            FOLDER "plugins"
    )
endif()

install(
    TARGETS dive_plugin_sample
    DESTINATION "${DIVE_HOST_PLUGINS_INSTALL_DIR}"
)
