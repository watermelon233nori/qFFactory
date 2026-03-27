cmake_minimum_required(VERSION 3.16)

project(qFFactory VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler-specific flags to treat C++ standard violations as errors
# and warn everything
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -Wall -Wextra")
endif()

# For MSVC
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive- /std:c++17 /Wall")
endif()


find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

qt_standard_project_setup()

qt_add_executable(qFFactory
    src/logger/loghelper.cpp
    src/task/taskwindow.cpp
    src/task/taskwindow.ui
    src/main.cpp
    src/application.cpp
    src/mainwindow.cpp
    src/instancemanager.cpp
    src/mainwindow.ui
)

target_link_libraries(qFFactory PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(qFFactory PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    # WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS qFFactory
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
