#pragma once
#include <SFML\Graphics.hpp>

namespace Textures
{
	enum class ID
	{
		Sprite,
	};
}

namespace Fonts
{
	enum class ID
	{
		Main
	};
}

//Forward declaration and a few type definitions
namespace tp
{
	namespace utils
	{
		template <typename Resource, typename Identifier>
		class ResourceHolder;
	}
}

using TextureHolder = tp::utils::ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = tp::utils::ResourceHolder<sf::Font, Fonts::ID>;