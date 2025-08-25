cmake_minimum_required(VERSION 3.16)
project(toffi LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.x)
FetchContent_MakeAvailable(SFML)

add_executable(${CMAKE_PROJECT_NAME}
    toffi/toffi.cpp
    toffi/src/Animation.cpp
    toffi/src/Bullet.cpp
    toffi/src/Character.cpp
    toffi/src/EnemiesManager.cpp
    toffi/src/Enemy.cpp
    toffi/src/RangeEnemy.cpp
    toffi/src/GameObject.cpp
    toffi/src/HealthBar.cpp
    toffi/src/Player.cpp
    toffi/src/PlayerController.cpp
    toffi/src/RangeWeapon.cpp
	toffi/src/MeleeWeapon.cpp
    toffi/src/Textures.cpp
    toffi/src/Timer.cpp
    toffi/src/ViewController.cpp
    toffi/src/Weapon.cpp
    toffi/src/World.cpp
    toffi/src/Pickable.cpp
    toffi/src/Heal.cpp
    toffi/src/BulletWave.cpp
    toffi/src/PickableSpawner.cpp
    toffi/src/ParticleSystem.cpp
    toffi/include/Engine/Helpers.hpp

    toffi/include/Bullet.h
    toffi/include/Player.h
    toffi/include/Textures.h
    toffi/include/Enemies/EnemiesManager.h
    toffi/include/Enemies/Enemy.h
    toffi/include/Enemies/RangeEnemy.h
    toffi/include/Engine/Animation.h
    toffi/include/Engine/Character.h
    toffi/include/Engine/Constants.h
    toffi/include/Engine/GameObject.h
    toffi/include/Engine/PlayerController.h
    toffi/include/Engine/Timer.h
    toffi/include/Engine/ViewController.h
    toffi/include/Engine/World.h
    toffi/include/Engine/Pickable.h
	toffi/include/Engine/PickableSpawner.h
    toffi/include/Engine/ParticleSystem.h
    toffi/include/UI/HealthBar.h
    toffi/include/Weapon/RangeWeapon.h
	toffi/include/Weapon/MeleeWeapon.h
    toffi/include/Weapon/Weapon.h
    toffi/include/Pickables/Heal.h
    toffi/include/Pickables/BulletWave.h
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-graphics)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-audio)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-window)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-system)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE toffi/include)

set(RESOURCES
    ${CMAKE_SOURCE_DIR}/toffi/Assets/enemies/eye_flight.png
    ${CMAKE_SOURCE_DIR}/toffi/Assets/enemies/spider.png
    ${CMAKE_SOURCE_DIR}/toffi/Assets/level_1/border.png
    ${CMAKE_SOURCE_DIR}/toffi/Assets/level_1/background.png
    ${CMAKE_SOURCE_DIR}/toffi/Assets/player/idle.png
    ${CMAKE_SOURCE_DIR}/toffi/Assets/player/run.png
    ${CMAKE_SOURCE_DIR}/toffi/Assets/bullet.png
    ${CMAKE_SOURCE_DIR}/toffi/Assets/sword.png
	${CMAKE_SOURCE_DIR}/toffi/Assets/heart.png
)

foreach(Assets ${RESOURCES})
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${Assets}
        bin
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    )
endforeach()

if(WIN32)
    add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
        VERBATIM)
endif()

install(TARGETS ${CMAKE_PROJECT_NAME})
