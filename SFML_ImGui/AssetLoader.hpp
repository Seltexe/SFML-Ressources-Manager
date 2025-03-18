#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <future>
#include "json.hpp"
#include "ResourceManager.hpp"

class AssetLoader {
public:
    static std::future<bool> loadAssetsAsync(const std::string& filename, const std::string& stateName) {
        return std::async(std::launch::async, [filename, stateName]() {
            return loadAssetsFromJSON(filename, stateName);
            });
    }

private:
    static bool loadAssetsFromJSON(const std::string& filename, const std::string& stateName) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error : Impossible to open " << filename << std::endl;
            return false;
        }

        nlohmann::json jsonData;
        file >> jsonData;

        if (jsonData.find(stateName) == jsonData.end()) {
            std::cerr << "Error : No assets defined for that state " << stateName << std::endl;
            return false;
        }

        auto& textureManager = ResourceManager<sf::Texture>::GetInstance();

        for (auto& [name, path] : jsonData[stateName].items()) {
            if (!textureManager.load(name, path)) {
                std::cerr << "Error : Impossible to load " << path << std::endl;
                return false;
            }
            else {
                std::cout << "Loaded : " << name << " from " << path << std::endl;
            }
        }

        return true;
    }
};