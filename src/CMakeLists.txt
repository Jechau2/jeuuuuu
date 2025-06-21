set(SOURCES
    main.cpp
    inventory.cpp
    jeu.cpp
    menu.cpp
    monstre.cpp
    objet.cpp
    parametre.cpp
    personage.cpp
    ui_helpers.cpp
)

add_executable(jeuuuuu ${SOURCES})

target_include_directories(jeuuuuu PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(jeuuuuu PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)
