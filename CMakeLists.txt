cmake_minimum_required(VERSION 3.23)
project(ProjectOmega)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
#set(LIBS SDL2.lib SDL2main.lib SDL2_Image.lib)
#set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/vendor)

#list(APPEND CMAKE_PREFIX_PATH "${SPDLOG_DIR}")

#find_package(spdlog REQUIRED)

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/SDL)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/SDL_Image)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/spdlog)

add_executable(ProjectOmegaExe src/omega/common.h
        src/omega/core/game.h
        src/omega/ecs/component.h
        src/omega/ecs/entity.h
        src/omega/ecs/spritecomponent.h
        src/omega/util/util.h src/omega/core/game.cpp
        src/omega/ecs/component.cpp
        src/omega/ecs/entity.cpp
        src/omega/ecs/spritecomponent.cpp
        src/omega/main.cpp "src/omega/util/maths.h" src/omega/core/types.h src/omega/debug/logger.cpp src/omega/debug/logger.h src/omega/ecs/anim_sprite_component.cpp src/omega/ecs/anim_sprite_component.h src/omega/ecs/background_sprite_component.cpp src/omega/ecs/background_sprite_component.h src/omega/ecs/ship.cpp src/omega/ecs/ship.h "src/omega/util/maths.cpp" src/omega/ecs/move_component.cpp src/omega/ecs/move_component.h src/omega/ecs/asteroid.cpp src/omega/ecs/asteroid.h src/omega/util/util.cpp src/omega/ecs/circle_component.cpp src/omega/ecs/circle_component.h)

#target_link_directories(ProjectOmegaExe PRIVATE ${PROJECT_SOURCE_DIR}/vendor/SDL2)
target_link_libraries(ProjectOmegaExe PRIVATE spdlog SDL2 SDL2main SDL2_image)
# ${PROJECT_SOURCE_DIR}/vendor/spdlog/include
target_include_directories(ProjectOmegaExe PUBLIC ${PROJECT_SOURCE_DIR}/vendor/spdlog/include ${PROJECT_SOURCE_DIR}/vendor/SDL/include ${PROJECT_SOURCE_DIR}/src)

target_compile_definitions(ProjectOmegaExe PRIVATE _CRT_SECURE_NO_WARNINGS PUBLIC $<$<CONFIG:Debug>:O_DEBUG>)

if (MSVC)
    target_compile_options(ProjectOmegaExe PRIVATE "/Zc:preprocessor")
endif ()
if (WIN32)
    target_compile_definitions(ProjectOmegaExe PRIVATE O_WINDOWS)
elseif (UNIX)
    target_compile_definitions(ProjectOmegaExe PRIVATE O_UNIX)
endif ()
