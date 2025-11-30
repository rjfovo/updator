cmake_minimum_required(VERSION 3.16)

project(cutefish-updator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Quick DBus)
find_package(Qt6 COMPONENTS LinguistTools REQUIRED)

# QApt - 注意：QApt只支持Qt5，在Qt6中需要寻找替代方案
# 可能的替代方案：
# 1. 使用系统命令调用APT工具 (apt, apt-get)
# 2. 使用libapt库直接与APT系统交互
# 3. 使用其他Qt6兼容的包管理库
# find_package(QApt REQUIRED)  # 暂时注释掉，需要实现替代方案

set(PROJECT_SOURCES
    main.cpp
    updatorhelper.cpp
    upgradeablemodel.cpp
    qml.qrc
)

add_executable(cutefish-updator
  ${PROJECT_SOURCES}
)

target_link_libraries(cutefish-updator
  PRIVATE
  Qt6::Core
  Qt6::Quick
  Qt6::DBus
  # QApt::Main  # 暂时注释掉，需要实现替代方案
)

file(GLOB TS_FILES translations/*.ts)

set(QM_FILES "")
foreach(_ts ${TS_FILES})
    get_filename_component(_name ${_ts} NAME_WE)
    set(_qm ${CMAKE_CURRENT_BINARY_DIR}/${_name}.qm)

    add_custom_command(
        OUTPUT ${_qm}
        COMMAND Qt6::lrelease ${_ts} -qm ${_qm}
        DEPENDS ${_ts}
        COMMENT "Generating ${_qm}"
    )

    list(APPEND QM_FILES ${_qm})
endforeach()

add_custom_target(translations ALL DEPENDS ${QM_FILES})
add_dependencies(cutefish-updator translations)

install(TARGETS cutefish-updator RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${QM_FILES} DESTINATION /usr/share/cutefish-updator/translations)

install(FILES
    cutefish-updator.desktop
    DESTINATION /usr/share/applications/
    COMPONENT Runtime
)
