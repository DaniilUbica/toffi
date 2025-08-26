cmake_minimum_required(VERSION 3.16)
project(toffi LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory(ubica_engine)

add_executable(${CMAKE_PROJECT_NAME}
    toffi/src/toffi.cpp
    toffi/src/Weapon/Bullet.cpp
    toffi/src/Enemies/EnemiesManager.cpp
    toffi/src/Enemies/Enemy.cpp
    toffi/src/Enemies/RangeEnemy.cpp
    toffi/src/Player/Player.cpp
    toffi/src/Weapon/RangeWeapon.cpp
	toffi/src/Weapon/MeleeWeapon.cpp
    toffi/src/Weapon/Weapon.cpp
    toffi/src/Textures/Textures.cpp
    toffi/src/Pickables/Heal.cpp
    toffi/src/Pickables/BulletWave.cpp
    toffi/src/Pickables/PickableSpawner.cpp
    toffi/src/Controllers/PlayerController.cpp
    toffi/src/Controllers/ViewController.cpp

    toffi/src/Weapon/Bullet.h
    toffi/src/Enemies/EnemiesManager.h
    toffi/src/Enemies/Enemy.h
    toffi/src/Enemies/RangeEnemy.h
    toffi/src/Player/Player.h
    toffi/src/Weapon/RangeWeapon.h
	toffi/src/Weapon/MeleeWeapon.h
    toffi/src/Weapon/Weapon.h
    toffi/src/Textures/Textures.h
    toffi/src/Pickables/Heal.h
    toffi/src/Pickables/BulletWave.h
    toffi/src/Pickables/PickableSpawner.h
    toffi/src/Controllers/PlayerController.h
    toffi/src/Controllers/ViewController.h
    toffi/src/Constants.h
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE UbicaEngine)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE toffi/src PRIVATE ubica_engine)

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

if(WIN32)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE_DIR:UbicaEngine>/sfml-system-2.dll
            $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE_DIR:UbicaEngine>/sfml-window-2.dll
            $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE_DIR:UbicaEngine>/sfml-graphics-2.dll
            $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE_DIR:UbicaEngine>/sfml-audio-2.dll
            $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    )
endif()