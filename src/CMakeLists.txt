cmake_minimum_required(VERSION 3.5)

project(Pixel-Art-Drawing)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL REQUIRED)

if(WIN32)

    set(SOURCES
        main.cpp 
        MainWindow.cpp
        Config.cpp
        DialogPixelSetting.cpp
        Canvas.cpp
        MyOpenGLWidget.cpp
        GrayWhiteButton.cpp
        )

    set(HEADERS
        MainWindow.h
        Config.h
        DialogPixelSetting.h
        Canvas.h
        MyOpenGLWidget.h
        GrayWhiteButton.h
        )

    set(FORMS
        MainWindow.ui
        DialogPixelSetting.ui
        )

    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${FORMS})
    target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        OpenGL::GL)

    target_compile_definitions(${PROJECT_NAME} PRIVATE
        PROJECT_VERSION="${VERSION}"
    )
    
endif()
