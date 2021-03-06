#pragma once
#include <cstdint>
#include "../../sdk/math/vector3d.hpp"
#include "events.h"

namespace utilities {
	template< typename t >
	__forceinline static t call_virtual( void *name, int offset ) {
		int *table = *( int ** ) name;
		int address = table[ offset ];
		return ( t ) ( address );
	}

	std::uint8_t* pattern_scan(const char* module_name, const char* signature) noexcept;

	inline event_listener listener;
}
