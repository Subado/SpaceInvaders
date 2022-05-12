#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category
{
	enum class Type
	{
		None = 0,
		Scene = 1 << 0,
		Cannon = 1 << 1,
	};
}

#endif // CATEGORY_HPP
