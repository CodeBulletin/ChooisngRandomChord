#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <cmath>
#include <vector>
#include <functional>
#include <complex>
#include <string>
#include <sstream>

namespace sfh {
	//apply
	template<typename r_type = sf::Vector2f, typename type = float>
	r_type apply2d(const r_type& vec, std::function<type(type)> function) {
		return { function(vec.x), function(vec.y) };
	}

	template<typename r_type = sf::Vector3f, typename type = float>
	r_type apply3d(const r_type& vec, std::function<type(type)> function) {
		return { function(vec.x), function(vec.y), function(vec.z) };
	}
	
	template<typename r_type = std::vector<float>, typename type = float>
	r_type apply2dList(const r_type& vec, std::function<type(type)> function) {
		return { function(vec[0]), function(vec[1]) };
	}

	template<typename r_type = std::vector<float>, typename type = float>
	r_type apply3dList(const r_type& vec, std::function<type(type)> function) {
		return { function(vec[0]), function(vec[1]), function(vec[2]) };
	}

	template<typename r_type = std::vector<float>,typename type = float>
	r_type apply4dList(const r_type& vec, std::function<type(type)> function) {
		return { function(vec[0]), function(vec[1]), function(vec[2]), function(vec[3]) };
	}

	template<typename r_type = std::vector<float>, typename type = float>
	r_type applyNdList(const r_type& vec, std::function<type(type)> function) {
		r_type vec2;
		for (type& i : vec) {
			vec2.push_back(function(i));
		}
		return vec2;
	}

	//map
	template<typename type = float>
	type map(type v, type valmin, type valmax, type mapmin, type mapmax) {
		return mapmin + (mapmax - mapmin) * ((v - valmin) / (valmax - valmin));
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	const r_type map2d(const r_type& v, type valmin, type valmax, type mapmin, type mapmax) {
		return {
			map<type>(v.x, valmin, valmax, mapmin, mapmax),
			map<type>(v.y, valmin, valmax, mapmin, mapmax)
		};
	}

	template<typename r_type = sf::Vector3f, typename type = float>
	const r_type map3d(const r_type& v, type valmin, type valmax, type mapmin, type mapmax) {
		return {
			map<type>(v.x, valmin, valmax, mapmin, mapmax),
			map<type>(v.y, valmin, valmax, mapmin, mapmax),
			map<type>(v.z, valmin, valmax, mapmin, mapmax)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type map2dList(const r_type& v, type valmin, type valmax, type mapmin, type mapmax) {
		return {
			map<type>(v[0], valmin, valmax, mapmin, mapmax),
			map<type>(v[1], valmin, valmax, mapmin, mapmax)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type& map3dList(const r_type& v, type valmin, type valmax, type mapmin, type mapmax) {
		return {
			map<type>(v[0], valmin, valmax, mapmin, mapmax),
			map<type>(v[1], valmin, valmax, mapmin, mapmax),
			map<type>(v[2], valmin, valmax, mapmin, mapmax)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type map4dList(const r_type& v, type valmin, type valmax, type mapmin, type mapmax) {
		return {
			map<type>(v[0], valmin, valmax, mapmin, mapmax),
			map<type>(v[1], valmin, valmax, mapmin, mapmax),
			map<type>(v[2], valmin, valmax, mapmin, mapmax),
			map<type>(v[3], valmin, valmax, mapmin, mapmax)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type mapNdList(const r_type& v, type valmin, type valmax, type mapmin, type mapmax) {
		r_type vec2;
		for (auto& i : v) {
			vec2.push_back(map<type>(i, valmin, valmax, mapmin, mapmax));
		}
		return vec2;
	}

	//clamp
	template<typename type = float>
	type clamp(type v, type min, type max) {
		return v < min ? min : v > max ? max : v;
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	const r_type clamp2d(const r_type& v, type min, type max) {
		return {
			clamp<type>(v.x, min, max),
			clamp<type>(v.y, min, max)
		};
	}

	template<typename r_type = sf::Vector3f, typename type = float>
	const r_type clamp3d(const r_type& v, type min, type max) {
		return {
			clamp<type>(v.x, min, max),
			clamp<type>(v.y, min, max),
			clamp<type>(v.z, min, max)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type& clamp2dList(const r_type& v, type min, type max) {
		return {
			clamp<type>(v[0], min, max),
			clamp<type>(v[1], min, max)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type& clamp3dList(const r_type& v, type min, type max) {
		return {
			clamp<type>(v[0], min, max),
			clamp<type>(v[1], min, max),
			clamp<type>(v[2], min, max),
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type& clamp4dList(const r_type& v, type min, type max) {
		return {
			clamp<type>(v[0], min, max),
			clamp<type>(v[1], min, max),
			clamp<type>(v[2], min, max),
			clamp<type>(v[3], min, max),
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type& clampNdList(const r_type& v, type min, type max) {
		r_type vec2;
		for (auto& i : v) {
			vec2.push_back(clamp<type>(i, min, max));
		}
		return vec2;
	}
	
	//mag2
	template<typename r_type = sf::Vector2f, typename type = float>
	type mag2d2(const r_type& vec) {
		return vec.x * vec.x + vec.y * vec.y;
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	type mag3d2(const r_type& vec) {
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	type mag2dList2(const r_type& vec) {
		return vec[0] * vec[0] + vec[1] * vec[1];
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	type mag3dList2(const r_type& vec) {
		return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	type mag4dList2(const r_type& vec) {
		return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2] + vec[3] * vec[3];
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type magNdList2(const r_type& vec) {
		double mag2 = 0;
		for (type& i : vec) {
			mag2 += i * i;
		}
		return (type)mag2;
	}
	
	//mag
	template<typename r_type = sf::Vector2f, typename type = float>
	type mag2d(const r_type& vec) {
		return (type)std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	type mag3d(const r_type& vec) {
		return (type)std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	type mag2dList(const r_type& vec) {
		return (type)std::sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	type mag3dList(const r_type& vec) {
		return (type)std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	type mag4dList(const r_type& vec) {
		return (type)std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2] + vec[3] * vec[3]);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type magNdList(const r_type& vec) {
		double mag2 = 0;
		for (type& i : vec) {
			mag2 += i * i;
		}
		return (type)std::sqrt(mag2);
	}
	
	//sqrt
	template<typename r_type = sf::Vector2f, typename type = float>
	const r_type sqrt2d(const r_type& v) {
		return {
			(type)std::sqrt((double)v.x),
			(type)std::sqrt((double)v.y),
		};
	}

	template<typename r_type = sf::Vector3f, typename type = float>
	const r_type sqrt3d(const r_type& v) {
		return {
			(type)std::sqrt((double)v.x),
			(type)std::sqrt((double)v.y),
			(type)std::sqrt((double)v.z)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type sqrt2dList(const r_type& v) {
		return {
			(type)std::sqrt((double)v[0]),
			(type)std::sqrt((double)v[1]),
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type sqrt3dList(const r_type& v) {
		return {
			(type)std::sqrt((double)v[0]),
			(type)std::sqrt((double)v[1]),
			(type)std::sqrt((double)v[2])
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type sqrt4dList(const r_type& v) {
		return {
			(type)std::sqrt((double)v[0]),
			(type)std::sqrt((double)v[1]),
			(type)std::sqrt((double)v[2]),
			(type)std::sqrt((double)v[3])
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type& sqrtNdList(const r_type& v) {
		r_type vec2;
		for (auto& i : v) {
			vec2.push_back((type)std::sqrt((double)i));
		}
		return vec2;
	}

	//atan2
	template<typename r_type = sf::Vector2f, typename type = float>
	type atan2(const r_type& vec) {
		return (type)std::atan2(vec.y, vec.x);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type atan2List(const r_type& vec) {
		return (type)std::atan2(vec[1], vec[0]);
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	type atan2Rev(const r_type& vec) {
		return (type)std::atan2(vec.x, vec.y);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type atan2ListRev(const r_type& vec) {
		return (type)std::atan2(vec[0], vec[1]);
	}

	//reverse
	template<typename r_type = sf::Vector2f>
	const r_type rev2d(const r_type& v) {
		return { v.y, v.x };
	}

	template<typename r_type = sf::Vector3f>
	const r_type rev3d(const r_type& v) {
		return { v.z, v.y, v.x };
	}

	template<typename r_type = std::vector<float>>
	const r_type rev2dList(const r_type& v) {
		return { v[1], v[0] };
	}

	template<typename r_type = std::vector<float>>
	const r_type rev3dList(const r_type& v) {
		return { v[2], v[1], v[0] };
	}

	template<typename r_type = std::vector<float>>
	const r_type rev4dList(const r_type& v) {
		return { v[3], v[2], v[1], v[0] };
	}

	template<typename r_type = std::vector<float>>
	const r_type revNdList(const r_type& v) {
		r_type vec2;
		for (int i = v.size() - 1; i >= 0; i--) {
			vec2.push_back(v[i]);
		}
		return vec2;
	}

	//normal
	template<typename r_type = sf::Vector2f, typename type = float>
	std::pair<r_type, r_type> normal(const r_type& vec) {
		return { { vec.y, -vec.x }, { -vec.y, vec.x } };
	}

	template<typename r_type = std::vector<float>, typename type = float>
	std::pair<r_type, r_type> normalList(const r_type& vec) {
		return { { vec[1], -vec[0] }, { -vec[1], vec[0] } };
	}
	
	//normalize
	template<typename r_type = sf::Vector2f, typename type = float>
	const r_type normalize2d(const r_type& v) {
		type mag = mag2d<r_type, type>(v);
		return {
			v.x / mag,
			v.y / mag
		};
	}

	template<typename r_type = sf::Vector3f, typename type = float>
	const r_type normalize3d(const r_type& v) {
		type mag = mag3d<r_type, type>(v);
		return {
			v.x / mag,
			v.y / mag,
			v.z / mag
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type normalize2dlist(const r_type& v) {
		type mag = mag2dList<r_type, type>(v);
		return {
			v[0] / mag,
			v[1] / mag,
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type normalize3dlist(const r_type& v) {
		type mag = mag3dList<r_type, type>(v);
		return {
			v[0] / mag,
			v[1] / mag,
			v[2] / mag
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type normalize4dlist(const r_type& v) {
		type mag = mag4dList<r_type, type>(v);
		return {
			v[0] / mag,
			v[1] / mag,
			v[2] / mag,
			v[3] / mag,
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	const r_type& normalizeNdList(const r_type& v) {
		type mag = magNdList<r_type, type>(v);
		r_type vec2;
		for (auto& i : v) {
			vec2.push_back(i / mag);
		}
		return vec2;
	}

	//lerp
	template<typename type = float>
	type lerp(type v1, type v2, type t) {
		return v1 + (v2 - v1) * t;
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	r_type lerp2d(const r_type& vec1, const r_type& vec2, type t) {
		return { 
			(type)(vec1.x + (vec2.x - vec1.x) * t),
			(type)(vec1.y + (vec2.y - vec1.y) * t)
		};
	}

	template<typename r_type = sf::Vector3f, typename type = float>
	r_type lerp3d(const r_type& vec1, const r_type& vec2, type t) {
		return { 
			(type)(vec1.x + (vec2.x - vec1.x) * t),
			(type)(vec1.y + (vec2.y - vec1.y) * t),
			(type)(vec1.z + (vec2.z - vec1.z) * t)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	r_type lerp2dList(const r_type& vec1, const r_type& vec2, type t) {
		return {
			(type)(vec1[0] + (vec2[0] - vec1[0]) * t),
			(type)(vec1[1] + (vec2[1] - vec1[1]) * t)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	r_type lerp3dList(const r_type& vec1, const r_type& vec2, type t) {
		return {
			(type)(vec1[0] + (vec2[0] - vec1[0]) * t),
			(type)(vec1[1] + (vec2[1] - vec1[1]) * t),
			(type)(vec1[2] + (vec2[2] - vec1[2]) * t)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	r_type lerp4dList(const r_type& vec1, const r_type& vec2, type t) {
		return {
			(type)(vec1[0] + (vec2[0] - vec1[0]) * t),
			(type)(vec1[1] + (vec2[1] - vec1[1]) * t),
			(type)(vec1[2] + (vec2[2] - vec1[2]) * t),
			(type)(vec1[3] + (vec2[3] - vec1[3]) * t)
		};
	}

	template<typename r_type = std::vector<float>, typename type = float>
	r_type lerpNdList(const r_type& vec1, const r_type& vec2, type t) {
		r_type vec3;
		for (int i = 0; i < vec1.size(); i++) {
			vec3.push_back((type)(vec1[i] + (vec2[i] - vec1[i]) * t));
		}
		return vec3;
	}

	//dot
	template<typename r_type = sf::Vector2f, typename type = float>
	type dot2d(const r_type& vec1, const r_type& vec2) {
		return (type)(vec1.x * vec2.x + vec1.y * vec2.y);
	}

	template<typename r_type = sf::Vector3f, typename type = float>
	type dot3d(const r_type& vec1, const r_type& vec2) {
		return (type)(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z + vec2.z);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type dot2dList(const r_type& vec1, const r_type& vec2) {
		return (type)(vec1[0] * vec2[0] + vec1[1] * vec2[1]);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type dot3dList(const r_type& vec1, const r_type& vec2) {
		return (type)(vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] + vec2[2]);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type dot4dList(const r_type& vec1, const r_type& vec2) {
		return (type)(vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] + vec2[2] + vec1[3] + vec2[3]);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type dotNdList(const r_type& vec1, const r_type& vec2) {
		type dot;
		for (int i = 0; i < vec1.size(); i++) {
			dot += vec1[i] * vec2[i];
		}
		return dot;
	}

	//cross
	template<typename r_type = sf::Vector2f>
	r_type crossProduct(const r_type& a, const r_type& b) {
		return { 
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		};
	}

	template<typename r_type = std::vector<float>>
	r_type crossProductList(const r_type& a, const r_type& b) {
		return {
			a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0]
		};
	}

	//distance2
	template<typename r_type = sf::Vector2f, typename type = float>
	type distance2d2(const r_type& vec1, const r_type& vec2) {
		return (type)(
			(vec1.x - vec2.x) * (vec1.x - vec2.x) +
			(vec1.y - vec2.y) * (vec1.y - vec2.y)
		);
	}

	template<typename r_type = sf::Vector3f, typename type = float>
	type distance3d2(const r_type& vec1, const r_type& vec2) {
		return (type)(
			(vec1.x - vec2.x) * (vec1.x - vec2.x) +
			(vec1.y - vec2.y) * (vec1.y - vec2.y) +
			(vec1.z - vec2.z) * (vec1.z - vec2.z)
		);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type distance2dList2(const r_type& vec1, const r_type& vec2) {
		return (type)(
			(vec1[0] - vec2[0]) * (vec1[0] - vec2[0]) +
			(vec1[1] - vec2[1]) * (vec1[1] - vec2[1])
		);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type distance3dList2(const r_type& vec1, const r_type& vec2) {
		return (type)(
			(vec1[0] - vec2[0]) * (vec1[0] - vec2[0]) +
			(vec1[1] - vec2[1]) * (vec1[1] - vec2[1]) +
			(vec1[2] - vec2[2]) * (vec1[2] - vec2[2])
		);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type distance4dList2(const r_type& vec1, const r_type& vec2) {
		return (type)(
			(vec1[0] - vec2[0]) * (vec1[0] - vec2[0]) +
			(vec1[1] - vec2[1]) * (vec1[1] - vec2[1]) +
			(vec1[2] - vec2[2]) * (vec1[2] - vec2[2]) +
			(vec1[3] - vec2[3]) * (vec1[3] - vec2[3])
		);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type distanceNdList2(const r_type& vec1, const r_type& vec2) {
		type dot;
		for (int i = 0; i < vec1.size(); i++) {
			dot += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
		}
		return dot;
	}

	//distance
	template<typename r_type = sf::Vector2f, typename type = float>
	type distance2d(const r_type& vec1, const r_type& vec2) {
		return (type)std::sqrt(
			(vec1.x - vec2.x) * (vec1.x - vec2.x) +
			(vec1.y - vec2.y) * (vec1.y - vec2.y)
		);
	}

	template<typename r_type = sf::Vector3f, typename type = float>
	type distance3d(const r_type& vec1, const r_type& vec2) {
		return (type)std::sqrt(
			(vec1.x - vec2.x) * (vec1.x - vec2.x) +
			(vec1.y - vec2.y) * (vec1.y - vec2.y) +
			(vec1.z - vec2.z) * (vec1.z - vec2.z)
		);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type distance2dList(const r_type& vec1, const r_type& vec2) {
		return (type)std::sqrt(
			(vec1[0] - vec2[0]) * (vec1[0] - vec2[0]) +
			(vec1[1] - vec2[1]) * (vec1[1] - vec2[1])
		);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type distance3dList(const r_type& vec1, const r_type& vec2) {
		return (type)std::sqrt(
			(vec1[0] - vec2[0]) * (vec1[0] - vec2[0]) +
			(vec1[1] - vec2[1]) * (vec1[1] - vec2[1]) +
			(vec1[2] - vec2[2]) * (vec1[2] - vec2[2])
		);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type distance4dList(const r_type& vec1, const r_type& vec2) {
		return (type)(
			(vec1[0] - vec2[0]) * (vec1[0] - vec2[0]) +
			(vec1[1] - vec2[1]) * (vec1[1] - vec2[1]) +
			(vec1[2] - vec2[2]) * (vec1[2] - vec2[2]) +
			(vec1[3] - vec2[3]) * (vec1[3] - vec2[3])
			);
	}

	template<typename r_type = std::vector<float>, typename type = float>
	type distanceNdList(const r_type& vec1, const r_type& vec2) {
		type dot;
		for (int i = 0; i < vec1.size(); i++) {
			dot += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
		}
		return (type)std::sqrt(dot);
	}

	//complex_vector/list
	template<typename r_type = sf::Vector2f, typename type = float>
	std::complex<type> toComplex(const r_type& vec) {
		return { vec.x, vec.y };
	}

	template<typename r_type = std::vector<float>, typename type = float>
	std::complex<type> listToComplex(const r_type& vec) {
		return { vec[0], vec[1] };
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	r_type toVector(const std::complex<type>& vec) {
		return { vec.real, vec.imag };
	}

	//vector/List_to_string
	template<typename r_type = std::vector<float>, typename type = float>
	std::string list2dToString(const r_type& list) {
		static std::ostringstream oss;
		oss << "| x: " << list[0] << ", y: " << list[1] << " |";
		return oss.str();
	}

	template<typename r_type = std::vector<float>, typename type = float>
	std::string list3dToString(const r_type& list) {
		static std::ostringstream oss;
		oss << "| x: " << list[0] << ", y: " << list[1] << ", z: " << list[2] << " |";
		return oss.str();
	}

	template<typename r_type = std::vector<float>, typename type = float>
	std::string list4dToString(const r_type& list) {
		static std::ostringstream oss;
		oss << "| x: " << list[0] << ", y: " << list[1] << ", z: " << list[2] << ", w: " << list[3] << " |";
		return oss.str();
	}

	template<typename r_type = std::vector<float>, typename type = float>
	std::string listNdToString(const r_type& list) {
		static std::ostringstream oss;
		oss << "| ";
		for (int i = 0; i < list.size(); i++) {
			if (i != 0) {
				oss << " ," << i << ": " << list[i];
			}
			else {
				oss << i << ": " << list[i];
			}
		}
		oss << " |";
		return oss.str();
	}

	template<typename r_type = sf::Vector2f, typename type = float>
	std::string vec2dToString(const r_type& vec) {
		static std::ostringstream oss;
		oss << "| x: " << vec.x << ", y: " << vec.y << " |";
		return oss.str();
	}

	template<typename r_type = sf::Vector3f, typename type = float>
	std::string vec3dToString(const r_type& vec) {
		static std::ostringstream oss;
		oss << "| x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << " |";
		return oss.str();
	}

	//vector_list
	template<typename r_type = sf::Vector2f, typename p_type = std::vector<float>, typename type = float>
	r_type listToVec2d(const p_type& list) {
		return { (type)list[0], (type)list[1] };
	}

	template<typename r_type = sf::Vector3f, typename p_type = std::vector<float>, typename type = float>
	r_type listToVec3d(const p_type& list) {
		return { (type)list[0], (type)list[1], (type)list[2]};
	}

	template<typename r_type = std::vector<float>, typename p_type = sf::Vector2f, typename type = float>
	r_type vec2dToList(const p_type& list) {
		return { (type)list.x, (type)list.y };
	}

	template<typename r_type = std::vector<float>, typename p_type = sf::Vector3f, typename type = float>
	r_type vec3dToList(const p_type& list) {
		return { (type)list.x, (type)list.y, (type)list.z };
	}

	//2d_3d
	template<typename r_type = sf::Vector2f, typename p_type = sf::Vector3f, typename type = float>
	r_type vec3dToVec2d(const p_type& list) {
		return { (type)list.x, (type)list.y };
	}

	template<typename r_type = sf::Vector3f, typename p_type = sf::Vector2f, typename type = float>
	r_type vec2dToVec3d(const p_type& list, type z = 0) {
		return { (type)list.x, (type)list.y, z };
	}
}