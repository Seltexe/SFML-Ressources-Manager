#pragma once
#include "State.hpp"
#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class GameState : public State {
public:
    GameState() = default;
    virtual ~GameState() = default;

    void onEnter() override 
    {
        std::cout << "Entrée dans l'état GameState" << std::endl;
        // On peut vérifier ici si les ressources ont été chargées
    }

    void onExit() override 
    {
        std::cout << "Sortie de l'état GameState" << std::endl;
    }

    void loadResources() override 
    {
        // Exemple de chargement de texture via ResourceManager
        auto& textureManager = ResourceManager<sf::Texture>::GetInstance();
        if (!textureManager.exists("player")) 
        {
            if (textureManager.load("player", "../assets/textures/knight.png"))
                std::cout << "Texture 'player' chargée !" << std::endl;
            else
                std::cerr << "Erreur lors du chargement de 'player' !" << std::endl;
        }
        // Ajouter d'autres ressources (fonts, sons, etc.) si besoin
    }

    void update(sf::Time dt) override 
    {
        // Logique du jeu ici
    }

    void render(sf::RenderWindow& window) override 
    {
        // Affichage du jeu, par exemple :
        sf::Sprite playerSprite;
        auto& textureManager = ResourceManager<sf::Texture>::GetInstance();
        playerSprite.setTexture(textureManager.Get("player"));
        window.draw(playerSprite);
    }
};