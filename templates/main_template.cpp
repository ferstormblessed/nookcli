#include <iostream>
#include "imgui-SFML.h"
#include "NOOK/core/Coordinator.h"
#include "NOOK/core/ResourceManager.h"
#include "NOOK/Utils/Config.h"
#include "NOOK/Utils/utils.h"
#include "NOOK/Utils/Register.h"
#include "NOOK/Games/InfiniteRunner.h"
#include "NOOK/Games/Pong.h"

NOOK::Coordinator gCoordinator;
NOOK::ResourceManager resourceManager;
NOOK::Config config;
NOOK::GAME_STATE gameState = NOOK::PLAY_STATE;

int main(int argc, char* argv[]) {
    std::cout << "INFO: INITIALIZING ENGINE" << std::endl;
    // ------------ COORDINATOR -----------
    gCoordinator.init();
    // ------------ COORDINATOR -----------

    // ------------ LOAD CONFIG ------------
    if (argc < 2) {
        std::cerr << "ERROR: Need to pass configuration file as command line argument." << std::endl;
        std::cerr << "ERROR: example --> ./executable config.txt" << std::endl;
        return 1;
    }
    config = NOOK::loadConfigFromFile(argv[1]);
    // ------------ LOAD CONFIG ------------

    // ------------ WORLD BOX2D ------------
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, config.GRAVITY};
    b2WorldId worldId = b2CreateWorld(&worldDef);
    b2World_SetHitEventThreshold(worldId, config.HIT_THRESHOLD);
    // ------------ WORLD BOX2D ------------

    // ------------ RESOURCE MANAGER ------------
    resourceManager.m_assetsPath = config.ASSETS_PATH;
    resourceManager.m_fontsDirectory = config.FONTS_DIRECTORY;
    resourceManager.m_soundsDirectory = config.AUDIO_DIRECTORY;
    resourceManager.m_textureDirectory = config.SPRITES_DIRECTORY;
    resourceManager.init();
    // ------------ RESOURCE MANAGER ------------

    // ---------- REGISTER COMPONENTS -----------
    NOOK::registerComponents();
    // ---------- REGISTER COMPONENTS -----------

    // ------------ REGISTER SYSTEMS ------------
    // Render Shape System
    auto renderShapeSystem = NOOK::registerRenderShapeSystem();
    renderShapeSystem->init();
    // Render Text System
    auto renderTextSystem = NOOK::registerRenderTextSystem();
    renderTextSystem->init();
    // Render System system
    auto renderSpriteSystem = NOOK::registerRenderSpriteSystem();
    renderSpriteSystem->init();
    // Physics System
    auto physicsSystem = NOOK::registerPhysicsSystem();
    physicsSystem->init();
    // Movement System
    auto movementSystem = NOOK::registerMovementSystem();
    movementSystem->init();
    // Jump System
    auto jumpSystem = NOOK::registerJumpSystem();
    jumpSystem->init();
    // Game Logic System
    auto gameLogicSystem = NOOK::registerGameLogicSystem();
    gameLogicSystem->init();
    // Pause System
    auto pauseSystem = NOOK::registerPauseSystem();
    pauseSystem->init();
    // Game Over System
    auto gameOverSystem = NOOK::registerGameOverSystem();
    gameOverSystem->init();
    // Debug System
    auto debugSystem = NOOK::registerDebugSystem();
    debugSystem->init();
    // ------------ REGISTER SYSTEMS ------------

    // TEMPLATE

    // ---------------- GAME LOOP ---------------
    sf::RenderWindow window;
    window.setFramerateLimit(config.FRAMES);
    sf::Clock clock;
    window.create(sf::VideoMode(config.WIDTH, config.HEIGHT), config.WINDOW_TITLE);
    if (!ImGui::SFML::Init(window)) return -1;

    // ----------------- AWAKE ------------------
    int iteration = 0;
    while (window.isOpen()) {
        if (iteration < 1) {
            physicsSystem->awake(worldId);
            iteration++;
        }
        // ----------------- AWAKE ------------------

        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, clock.restart());

        window.clear();

        physicsSystem->update(worldId, gameState);
        movementSystem->update(&event, gameState);
        jumpSystem->update(&event, gameState);
        renderShapeSystem->update(&window);
        renderTextSystem->update(&window);
        renderSpriteSystem->update(&window);
        gameLogicSystem->update();
        pauseSystem->update(&event, gameState);
        gameOverSystem->update(gameState);
        debugSystem->update(&event);

        ImGui::SFML::Render(window);

        window.display();
    }
    ImGui::SFML::Shutdown();

    // ---------------- GAME LOOP ---------------
    return 0;
}
