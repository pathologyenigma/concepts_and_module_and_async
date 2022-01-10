export module ecs.Def;
import <cstdint>;
import <limits>;
export namespace ecs {
	using Entity = uint32_t;
	using Index = uint32_t;
	static constexpr auto InvalidIndex = std::numeric_limits<Index>::max();
};