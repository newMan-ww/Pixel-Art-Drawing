cmake_minimum_required(VERSION 3.5)

project(Pixel-Art-Drawing)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(WIN32)

    set(SOURCES
        main.cpp 
        MainWindow.cpp
        )

    set(HEADERS
        MainWindow.h
        )

    set(FORMS
        MainWindow.ui
        )

    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${FORMS})
    target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)

    target_compile_definitions(${PROJECT_NAME} PRIVATE
        PROJECT_VERSION="${VERSION}"
    )
    
endif()
