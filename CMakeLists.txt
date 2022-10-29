cmake_minimum_required(VERSION 3.23)
project(ProjectOmega)

set(CMAKE_CXX_STANDARD 20)


set(LIBS SDL2.lib SDL2main.lib SDL2_Image.lib)
set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/vendor)

list(APPEND CMAKE_PREFIX_PATH "${SPDLOG_DIR}")

find_package(spdlog REQUIRED)

add_executable(ProjectOmegaExe src/omega/core/common.h
        src/omega/core/game.h
        src/omega/ecs/component.h
        src/omega/ecs/entity.h
        src/omega/ecs/spritecomponent.h
        src/omega/util/util.h src/omega/core/game.cpp
        src/omega/ecs/component.cpp
        src/omega/ecs/entity.cpp
        src/omega/ecs/spritecomponent.cpp
        src/omega/main.cpp src/omega/util/math.h src/omega/core/types.h)

target_link_directories(ProjectOmegaExe PRIVATE ${PROJECT_SOURCE_DIR}/vendor/SDL2)
target_link_libraries(ProjectOmegaExe PRIVATE ${LIBS} spdlog::spdlog)
# ${PROJECT_SOURCE_DIR}/vendor/spdlog/include
target_include_directories(ProjectOmegaExe PUBLIC ${PROJECT_SOURCE_DIR}/vendor/SDL2/include ${PROJECT_SOURCE_DIR}/src)