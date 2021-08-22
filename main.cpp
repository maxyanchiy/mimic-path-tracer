#include "source/types/vec3.hpp"
#include "source/types/color.hpp"
#include "source/types/ray.hpp"

#include <iostream>

using namespace std;

namespace r_consts {
	constexpr int imageWidth = 1280;
	constexpr int ppmMaxColorValue = 255;
}

const bool hitSphere(const point3& center, const double radius, ray& r) {
	const vec3 origin_spherecenter = r.origin() - center;
	const double b = 2 * dot(r.direction(), origin_spherecenter);
	const double a = dot(r.direction(), r.direction());
	const double c = dot(origin_spherecenter, origin_spherecenter) - radius * radius;
	const auto discriminant = b*b - 4*a*c;
	return discriminant >= 0;
}
color ray_color(ray& r) {
	if (hitSphere(point3(0, 0, -5.0), 1.5, r)) {
		return color(1.0,0.0,0.0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	const double t = 0.5 * (unit_direction.y() + 1.0);
	return ((1 - t) * color(1.0, 1.0, 1.0) + t * color(1.0, 0.753, 0.796));
}

int main() {

	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int imageHeight = static_cast<int>(r_consts::imageWidth/aspect_ratio);

	// Camera
	const auto viewport_height = 2.0;
	const auto viewport_width = viewport_height * aspect_ratio;
	const auto focal_length = 1.0;

	const point3 origin(0, 0, 0);
	const vec3 horizontal(viewport_width, 0, 0);
	const vec3 vertical(0, viewport_height, 0);
	const vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	std::cout << "P3" << std::endl;
	std::cout << r_consts::imageWidth << " " << imageHeight << std::endl;
	std::cout << r_consts::ppmMaxColorValue << std::endl;

	for (int PixelRawIterator = imageHeight-1; PixelRawIterator >= 0; --PixelRawIterator) {
		std::cerr << "\r Scanning Raw: " << PixelRawIterator+1 << " of "<< imageHeight << std::flush;
		for (int PixelColumnIterator = 0; PixelColumnIterator < r_consts::imageWidth; ++PixelColumnIterator) {
			const double u = (double)PixelRawIterator / imageHeight;
			const double v = (double)PixelColumnIterator / r_consts::imageWidth;
			ray r(origin, lower_left_corner + u * vertical + v * horizontal - origin);
			color pixel_color(ray_color(r));
			write_color(std::cout, pixel_color);
		}
	}
	std::cerr << "\n Done \n";
}