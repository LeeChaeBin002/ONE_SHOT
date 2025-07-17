#include "ResourceMgr.h"
#include "stdafx.h"
#include <SFML/Graphics/Font.hpp>


template<>
sf::Font ResourceMgr<sf::Font>::Empty = sf::Font();
template<>
sf::Texture ResourceMgr<sf::Texture>::Empty = sf::Texture();

template<>
sf::SoundBuffer ResourceMgr<sf::SoundBuffer>::Empty = sf::SoundBuffer();