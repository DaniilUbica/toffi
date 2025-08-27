cmake_minimum_required(VERSION 3.16)
project(toffi LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(ENGINE_UNIT_NAME UbicaEngine)

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

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${ENGINE_UNIT_NAME})
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

install(TARGETS ${CMAKE_PROJECT_NAME})
