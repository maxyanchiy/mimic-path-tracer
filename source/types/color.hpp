#pragma once
#ifndef COLOR_H
#define COLOR_H

#include "vec3.hpp"

void write_color(std::ostream& out, color pixel_color) {
	out << static_cast<int>(255.999 * pixel_color.x()) << " "        // R
		<< static_cast<int>(255.999 * pixel_color.y()) << " "        // G
		<< static_cast<int>(255.999 * pixel_color.z()) << std::endl; // B
}

#endif // !COLOR_H

