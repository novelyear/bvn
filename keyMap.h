#ifndef KEYMAP_H
#define KEYAMP_H

#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include <string>

// ȫ�ֱ��� key
extern std::unordered_map<bool, std::unordered_map<std::string, sf::Keyboard::Key>> key;

void initializeKeyMapping();

#endif // KEYAMP_H

