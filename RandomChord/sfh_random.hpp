#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>
#include <random>
#include <cmath>
#include <vector>

#define PI 3.14159265
#define PI_D 3.141592653589793238462643383279502884197169399375105820974944

namespace sfh {
	namespace random {
		static std::random_device randomDevice;
		static std::mt19937 mt_engine(randomDevice());

		template<class type>
		using uniform_distribution =
			typename std::conditional<std::is_floating_point<type>::value, std::uniform_real_distribution<type>,
			typename std::conditional<std::is_integral<type>::value, std::uniform_int_distribution<type>, void>::type >::type;

		//Random1d
		template<typename type = float>
		type random1d(type min = -1, type max = 1) {
			uniform_distribution<type> rand(min, max);
			return { rand(mt_engine) };
		}

		//Random2d
		template<typename type = sf::Vector2f, typename type2 = float>
		type random2d(type2 min1, type2 max1, type2 min2, type2 max2) {
			uniform_distribution<type2> rand1(min1, max1);
			uniform_distribution<type2> rand2(min2, max2);
			return { rand1(mt_engine), rand2(mt_engine) };
		}

		template<typename type = sf::Vector2f, typename type2 = float>
		type random2d(type2 min, type2 max) {
			uniform_distribution<type2> rand(min, max);
			return { rand(mt_engine), rand(mt_engine) };
		}

		template<typename type = sf::Vector2f, typename type2 = float>
		type random2d() {
			uniform_distribution<type2> rand((type2)0, (type2)(2 * PI_D));
			type2 angle = rand(mt_engine);
			return { (type2)std::cos(angle), (type2)std::sin(angle) };
		}

		//Random3d
		template<typename type = sf::Vector3f, typename type2 = float>
		type random3d(type2 min1, type2 max1, type2 min2, type2 max2, type2 min3, type2 max3) {
			uniform_distribution<type2> rand1(min1, max1);
			uniform_distribution<type2> rand2(min2, max2);
			uniform_distribution<type2> rand3(min3, max3);
			return { rand1(mt_engine), rand2(mt_engine), rand3(mt_engine) };
		}

		template<typename type = sf::Vector3f, typename type2 = float>
		type random3d(type2 min, type2 max) {
			uniform_distribution<type2> rand(min, max);
			return { rand(mt_engine), rand(mt_engine), rand(mt_engine) };
		}

		template<typename type = sf::Vector3f, typename type2 = float, typename cast = float>
		type random3d(type2 mult0 = 1.0f, type2 mult1 = 1.0f, type2 mult2 = 1.0f) {
			uniform_distribution<type2> rand((type2)0, (type2)(2 * PI_D));
			type2 phi = rand(mt_engine);
			type2 theta = rand(mt_engine);
			return {
				(cast)(mult0 * std::sin(theta) * std::cos(phi)),
				(cast)(mult1 * std::sin(theta) * std::sin(phi)),
				(cast)(mult2 * std::cos(theta))
			};
		}

		//Random4d
		template<typename type = std::vector<float>, typename type2 = float>
		type random4d(type2 min1, type2 max1, type2 min2, type2 max2, type2 min3, type2 max3, type2 min4, type2 max4) {
			uniform_distribution<type2> rand1(min1, max1);
			uniform_distribution<type2> rand2(min2, max2);
			uniform_distribution<type2> rand3(min3, max3);
			uniform_distribution<type2> rand4(min4, max4);
			return { rand1(mt_engine), rand2(mt_engine), rand3(mt_engine), rand4(mt_engine) };
		}

		template<typename type = std::vector<float>, typename type2 = float>
		type random4d(type2 min, type2 max) {
			uniform_distribution<type2> rand(min, max);
			return { rand(mt_engine), rand(mt_engine), rand(mt_engine), rand(mt_engine) };
		}

		template<typename type = std::vector<float>, typename type2 = float, typename cast = float>
		type random4d(type2 mult0 = 255.0f, type2 mult1 = 255.0f, type2 mult2 = 255.0f, type2 mult3 = 255.0f) {
			uniform_distribution<type2> rand((type2)0, (type2)(2 * PI_D));
			type2 alpha = rand(mt_engine);
			type2 beta = rand(mt_engine);
			type2 gamma = rand(mt_engine);
			return {
				(cast)(mult0 * std::sin(alpha) * std::cos(beta) * std::cos(gamma)),
				(cast)(mult1 * std::cos(alpha) * std::cos(beta) * std::cos(gamma)),
				(cast)(mult2 * std::sin(beta) * std::cos(gamma)),
				(cast)(mult3 * std::cos(gamma))
			};
		}

		//RandomNd
		template<typename r_type = std::vector<float>, typename type = float>
		r_type randomNd(int n, const r_type& min, const r_type& max) {
			r_type vec;
			for (int i = 0; i < n; i++) {
				uniform_distribution<type> rand(min[i], max[i]);
				vec.push_back(rand(mt_engine));
			}
			return vec;
		}

		template<typename r_type = std::vector<float>, typename type = float>
		r_type randomNd(int n, type min, const type max) {
			r_type vec;
			uniform_distribution<type> rand(min, max);
			for (int i = 0; i < n; i++) {
				vec.push_back(rand(mt_engine));
			}
			return vec;
		}

		//RandomColor
		template<typename type = sf::Color, typename type2 = int, typename cast = uint8_t>
		type randomRGBA(type2 min1, type2 max1, type2 min2, type2 max2, type2 min3, type2 max3, type2 min4, type2 max4) {
			uniform_distribution<type2> rand1(min1, max1);
			uniform_distribution<type2> rand2(min2, max2);
			uniform_distribution<type2> rand3(min3, max3);
			uniform_distribution<type2> rand4(min4, max4);
			return { (cast)rand1(mt_engine), (cast)rand2(mt_engine),
				(cast)rand3(mt_engine), (cast)rand4(mt_engine) };
		}

		template<typename type = sf::Color, typename type2 = int, typename cast = uint8_t>
		type randomRGB(type2 min1, type2 max1, type2 min2, type2 max2, type2 min3, type2 max3, type2 alpha = 255) {
			uniform_distribution<type2> rand1(min1, max1);
			uniform_distribution<type2> rand2(min2, max2);
			uniform_distribution<type2> rand3(min3, max3);
			return { (cast)rand1(mt_engine), (cast)rand2(mt_engine),
				(cast)rand3(mt_engine), (cast)alpha };
		}

		template<typename type = sf::Color, typename type2 = int, typename cast = uint8_t>
		type randomRGBA(type2 min, type2 max) {
			uniform_distribution<type2> rand(min, max);
			return { (cast)rand(mt_engine), (cast)rand(mt_engine), (cast)rand(mt_engine), (cast)rand(mt_engine) };
		}

		template<typename type = sf::Color, typename type2 = int, typename cast = uint8_t>
		type randomRGB(type2 min, type2 max, type2 alpha = 255) {
			uniform_distribution<type2> rand(min, max);
			return { (cast)rand(mt_engine), (cast)rand(mt_engine), (cast)rand(mt_engine), (cast)alpha };
		}

		template<typename type = sf::Color, typename type2 = float, typename cast = uint8_t>
		type randomRGBA_Surface(type2 mult0 = 255.0f, type2 mult1 = 255.0f, type2 mult2 = 255.0f, type2 mult3 = 255.0f) {
			uniform_distribution<type2> rand((type2)0, (type2)(2 * PI_D));
			type2 alpha = rand(mt_engine);
			type2 beta = rand(mt_engine);
			type2 gamma = rand(mt_engine);
			return {
				(cast)(mult0 * std::sin(alpha) * std::cos(beta) * std::cos(gamma)),
				(cast)(mult1 * std::cos(alpha) * std::cos(beta) * std::cos(gamma)),
				(cast)(mult2 * std::sin(beta) * std::cos(gamma)),
				(cast)(mult3 * std::cos(gamma))
			};
		}

		template<typename type = sf::Color, typename type2 = float, typename cast = uint8_t>
		type randomRGB_Surface(type2 mult0 = 255.0f, type2 mult1 = 255.0f, type2 mult2 = 255.0f, type2 alpha = 255) {
			uniform_distribution<type2> rand((type2)0, (type2)(2 * PI_D));
			type2 phi = rand(mt_engine);
			type2 theta = rand(mt_engine);
			return {
				(cast)(mult0 * std::sin(theta) * std::cos(phi)),
				(cast)(mult1 * std::sin(theta) * std::sin(phi)),
				(cast)(mult2 * std::cos(theta)),
				(cast)alpha
			};
		}

		template<typename type = std::vector<float>, typename type2 = float, typename cast = float>
		type randomHueSaturation(type2 mult0 = 360.0f, type2 mult1 = 1.0f, type2 mult2 = 1.0f, type2 alpha = 255) {
			uniform_distribution<type2> rand((type2)0, (type2)1);
			return {
				(cast)(mult0 * rand(mt_engine)),
				(cast)(mult1 * rand(mt_engine)),
				(cast)(mult2 * rand(mt_engine)),
				(cast)alpha
			};
		}

		template<typename type = std::vector<float>, typename type2 = float, typename cast = float>
		type randomHue(type2 mult0 = 360.0f, type2 S = 1.0f, type2 V = 1.0f, type2 alpha = 255) {
			uniform_distribution<type2> rand((type2)0, (type2)1);
			return {
				(cast)(mult0 * rand(mt_engine)),
				(cast)S, (cast)V, (cast)alpha
			};
		}
	}
}