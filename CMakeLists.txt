cmake_minimum_required(VERSION 3.16)

project(CpuSchedulingSimulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appCpuSchedulingSimulator
    main.cpp
)

qt_add_qml_module(appCpuSchedulingSimulator
    URI CpuSchedulingSimulator
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES scheduling.h scheduling.cpp
        SOURCES fcfs.h fcfs.cpp
        SOURCES schedulingmanager.h schedulingmanager.cpp
        SOURCES processlist.h processlist.cpp
        QML_FILES Navigation/NavigationBar.qml
        QML_FILES Navigation/NavigationButton.qml
        QML_FILES NewWindow1.qml
        QML_FILES Input/ProcessInput.qml
        QML_FILES ListComponent/HeaderComponent.qml
        QML_FILES ListComponent/ViewDelegate.qml
        QML_FILES Input/InputTool.qml
        SOURCES GanttChart.h
        QML_FILES NewWindow2.qml
        SOURCES GanttChart.cpp
        SOURCES sjf.h sjf.cpp
        SOURCES schedulingoutput.h schedulingoutput.cpp
)
qt_add_resources(appCpuSchedulingSimulator "global_resources"
    PREFIX "/"
    FILES
        delete_icon.png
        edit_icon.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCpuSchedulingSimulator PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCpuSchedulingSimulator
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set(QT_QML_GENERATE_QMLLS_INI ON)

target_link_libraries(appCpuSchedulingSimulator
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appCpuSchedulingSimulator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
