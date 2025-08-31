cmake_minimum_required(VERSION 3.10.0)
project(SistemaOperativo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Configurar rutas de include
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Archivos fuente
file(GLOB SOURCES
    "src/*.cpp"
    "*.cpp"  # main.cpp u otros en raíz
)

file(GLOB HEADER_FILES
    "include/*.h"
)

# Archivos de interfaz .ui
file(GLOB UI_FILES
    "ui/*.ui"
)

set_property(SOURCE ${UI_FILES} PROPERTY SKIP_AUTOUIC ON)


add_executable(SistemaOperativo
    ${SOURCES}
    ${UI_FILES}
    ${HEADER_FILES})

target_sources(${PROJECT_NAME} PRIVATE ${UI_GENERATED_FILES})

target_link_libraries(SistemaOperativo Qt6::Widgets Qt6::Core Qt6::Gui)

