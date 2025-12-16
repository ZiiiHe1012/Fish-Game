cmake_minimum_required(VERSION 3.28)
project(Fish)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Fish src/main.cpp
        src/MyGame.cpp
        src/MyGame.h
        src/Items/Item.cpp
        src/Items/Item.h
        src/Items/Characters/Character.cpp
        src/Items/Characters/Character.h
        src/Items/Characters/Link.cpp
        src/Items/Characters/Link.h
        src/Scenes/Scene.cpp
        src/Scenes/Scene.h
        src/Scenes/BattleScene.cpp
        src/Scenes/BattleScene.h
        assets/assets.qrc
        src/Items/Maps/Map.cpp
        src/Items/Maps/Map.h
        src/Items/Maps/Battlefield.cpp
        src/Items/Maps/Battlefield.h
        src/Items/Fish/Fish.cpp
        src/Items/Fish/Fish.h
        src/Items/Fish/PlayerFish.cpp
        src/Items/Fish/PlayerFish.h
        src/Items/Fish/SmallFish.cpp
        src/Items/Fish/SmallFish.h
        src/Items/Fish/BigFish.cpp
        src/Items/Fish/BigFish.h
)
        
target_link_libraries(Fish
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

