#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <string>

class SoundManager {
public:
  static SoundManager &getInstance() {
    static SoundManager instance;
    return instance;
  }

  bool loadSound(const std::string &name, const std::string &filename) {
    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(filename))
      return false;

    auto sound = std::make_unique<sf::Sound>(*buffer);
    buffers[name] = std::move(buffer);
    sounds[name] = std::move(sound);
    return true;
  }

  void play(const std::string &name) {
    if (sounds.count(name) && sounds[name]) {
      sounds[name]->play();
    }
  }

private:
  SoundManager() {}
  std::map<std::string, std::unique_ptr<sf::SoundBuffer>> buffers;
  std::map<std::string, std::unique_ptr<sf::Sound>> sounds;
};

#endif // SOUND_MANAGER_HPP
