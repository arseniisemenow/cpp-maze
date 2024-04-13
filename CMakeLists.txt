cmake_minimum_required(VERSION 3.5)

project(Maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(src)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt6_add_resources(STYLE_RESOURCES res/styles/styles.qrc)
    qt6_add_resources(MEDIA_RESOURCES res/icons/media.qrc)
elseif (${QT_VERSION_MAJOR} EQUAL 5)
    qt5_add_resources(STYLE_RESOURCES res/styles/styles.qrc)
    qt5_add_resources(MEDIA_RESOURCES res/icons/media.qrc)
endif ()

set(MODEL_SOURCES
        src/Model/Model.cc
        src/Model/Model.h
        src/Model/MazeLoader/MazeLoader.cc
        src/Model/MazeLoader/MazeLoader.h
        src/Model/MazeSolver/MazeSolver.cc
        src/Model/MazeSolver/MazeSolver.h
        src/Model/MazeSolver/DirectionType.h
        src/Model/MazeGenerator/MazeGenerator.cc
        src/Model/MazeGenerator/MazeGenerator.h
        src/Model/MazeSaver/MazeSaver.cc
        src/Model/MazeSaver/MazeSaver.h
)
set(CONTROLLER_SOURCES
        src/Controller/Controller.cc
        src/Controller/Controller.h
)

set(VIEW_SOURCES
        src/View/View.cc
        src/View/View.h
        src/View/View.ui
        src/View/GridWidget/GridWidget.cc
        src/View/GridWidget/GridWidget.h
        src/View/common/constants.h
        src/View/EventHandler/EventHandler.h
        src/View/FileHandler/FileHandler.h
        src/View/MenuBar/MenuBar.cc
        src/View/MenuBar/MenuBar.h
        src/View/modal_widgets/AboutWindow/AboutWindow.h
        src/View/modal_widgets/AboutWindow/AboutWindow.cc
        src/View/modal_widgets/AboutWindow/AboutWindow.ui
        src/View/modal_widgets/FileDialog/FileDialog.h
        src/View/modal_widgets/FileDialog/FileDialog.cc
        src/View/common/macro.h
        src/View/styles/global_styles.h
        src/View/styles/styles.h
        src/View/styles/styles.cc
        src/View/InputManager/InputManager.cc
        src/View/InputManager/InputManager.h
        src/View/SpinBox/SpinBoxPushButton.cc
        src/View/SpinBox/SpinBoxLineEdit.cc
        src/View/SpinBox/SpinBox.cc
)

set(PROJECT_SOURCES
        ${STYLE_RESOURCES}
        ${MEDIA_RESOURCES}
        ${MODEL_SOURCES}
        ${CONTROLLER_SOURCES}
        ${VIEW_SOURCES}
        src/main.cc
        src/common/MazeData.h
        src/common/constants.h
        src/common/LoadResult.h
        src/Model/MazeGenerator/CustomFigures/CustomFigures.h
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Maze
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET Maze APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(Maze SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(Maze
                ${PROJECT_SOURCES}
        )
    endif ()
endif ()

target_link_libraries(Maze PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Maze PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Maze)
endif ()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(tests
        ${MODEL_SOURCES}
        ${CONTROLLER_SOURCES}
        tests/tests.cc
        tests/maze_loader_tests.cc
        tests/maze_generator_tests.cc
        tests/maze_solver_tests.cc
        tests/maze_saver_tests.cc
)

target_link_libraries(tests gtest_main)
