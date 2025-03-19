#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <future>
#include <mutex>
#include "json.hpp"
#include "ResourceManager.hpp"

class AssetLoader {
public:
    /// <summary>
	/// Load assets from a JSON file asynchronously
    /// </summary>
    /// <param name="filename"></param>
    /// <param name="stateName"></param>
    /// <returns></returns>
    static std::future<bool> loadAssetsAsync(const std::string& filename, const std::string& stateName) {
        return std::async(std::launch::async, [filename, stateName]() {
            try {
                return loadAssetsFromJSON(filename, stateName);
            }
            catch (const std::exception& e) {
                std::cerr << "Exception in loadAssetsAsync: " << e.what() << std::endl;
                return false;
            }
            });
    }

private:
    /// <summary>
	/// Load assets from a JSON file
    /// </summary>
    /// <param name="filename"></param>
    /// <param name="stateName"></param>
    /// <returns></returns>
    static bool loadAssetsFromJSON(const std::string& filename, const std::string& stateName) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error: Impossible to open " << filename << std::endl;
            return false;
        }

        nlohmann::json jsonData;
        file >> jsonData;
        file.close(); // Explicitly close the file

        if (jsonData.find(stateName) == jsonData.end()) {
            std::cerr << "Error: No assets defined for that state " << stateName << std::endl;
            return false;
        }

        auto& textureManager = ResourceManager<sf::Texture>::GetInstance();
        static std::mutex mtx; // Mutex to ensure thread safety

        for (auto& [name, path] : jsonData[stateName].items()) {
            std::lock_guard<std::mutex> lock(mtx); // Lock the mutex for thread safety
            if (!textureManager.load(name, path)) {
                std::cerr << "Error: Impossible to load " << path << std::endl;
                return false;
            }
            else {
                std::cout << "Loaded: " << name << " from " << path << std::endl;
            }
        }

        return true;
    }
};
