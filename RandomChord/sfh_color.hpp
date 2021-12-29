#pragma once
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>

namespace sfh {
	namespace color {
		//HSL_RGB
		template<typename r_type = std::vector<float>, typename p_type1 = std::vector<uint8_t>>
		r_type RGB_to_HSL(const p_type1& col) {
			const float R1 = col[0] / 255.0f;
			const float G1 = col[1] / 255.0f;
			const float B1 = col[2] / 255.0f;

			float cmax = std::max(R1, std::max(G1, B1));
			float cmin = std::min(R1, std::min(G1, B1));

			float delta = cmax - cmin;
			float l = (cmax + cmin) / 2.0f;
			float h = 0;
			if (delta == 0.0f) {
				return { h, 0.0f, l, float(col[3]) };
			}
			float s = delta / (1 - std::fabs(2.0f * l - 1.0f));
			if (R1 == cmax) (h = 60 * std::fmod((G1 - B1) / delta, 6.0f)) < 0.0f ? h = 360 + h : h = h;
			else if (G1 == cmax) h = 60 * ((B1 - R1) / delta + 2);
			else if (B1 == cmax) h = 60 * ((R1 - G1) / delta + 4);

			return { h, s, l, float(col[3]) };
		}

		template<typename r_type = std::vector<float>>
		r_type RGB_to_HSL(const sf::Color& col) {
			return RGB_to_HSL<r_type, std::vector<uint8_t>>({ col.r, col.g, col.b, col.a });
		}

		template<typename r_type = std::vector<int>, typename p_type = std::vector<float>, typename cast = int>
		r_type HSL_to_RGB(const p_type& col) {
			float C = (1 - std::fabs(2 * col[2] - 1)) * col[1];
			float h = col[0] / 60.0f;
			float X = C * (1 - std::fabs(std::fmod(h, 2) - 1));
			float m = col[2] - C / 2.0f;
			switch (int(h))
			{
			case 0: return { (cast)std::round((C + m) * 255.0f), (cast)std::round((X + m) * 255.0f), (cast)std::round((m) * 255.0f), (cast)col[3] };
			case 1: return { (cast)std::round((X + m) * 255.0f), (cast)std::round((C + m) * 255.0f), (cast)std::round((m) * 255.0f), (cast)col[3] };
			case 2: return { (cast)std::round((m) * 255.0f), (cast)std::round((C + m) * 255.0f), (cast)std::round((X + m) * 255.0f), (cast)col[3] };
			case 3: return { (cast)std::round((m) * 255.0f), (cast)std::round((X + m) * 255.0f), (cast)std::round((C + m) * 255.0f), (cast)col[3] };
			case 4: return { (cast)std::round((X + m) * 255.0f), (cast)std::round((m) * 255.0f), (cast)std::round((C + m) * 255.0f), (cast)col[3] };
			case 5: return { (cast)std::round((C + m) * 255.0f), (cast)std::round((m) * 255.0f), (cast)std::round((X + m) * 255.0f), (cast)col[3] };
			default: return { (cast)std::round((C + m) * 255.0f), (cast)std::round((X + m) * 255.0f), (cast)std::round((m) * 255.0f), (cast)col[3] };
			}
		}

		//HSV_RGB
		template<typename r_type = std::vector<float>, typename p_type1 = std::vector<uint8_t>>
		r_type RGB_to_HSV(const p_type1& col) {
			const float R1 = col[0] / 255.0f;
			const float G1 = col[1] / 255.0f;
			const float B1 = col[2] / 255.0f;

			float cmax = std::max(R1, std::max(G1, B1));
			float cmin = std::min(R1, std::min(G1, B1));

			float delta = cmax - cmin;
			float h = 0;
			float v = cmax;
			float s = cmax == 0.0f ? 0.0f : delta / cmax;
			if (delta == 0.0f) return { h, s, v, float(col[3]) };
			else if (R1 == cmax) (h = 60 * std::fmod((G1 - B1) / delta, 6.0f)) < 0.0f ? h = 360 + h : h = h;
			else if (G1 == cmax) h = 60 * ((B1 - R1) / delta + 2);
			else if (B1 == cmax) h = 60 * ((R1 - G1) / delta + 4);

			return { h, s, v, float(col[3]) };
		}

		template<typename r_type = std::vector<float>>
		r_type RGB_to_HSV(const sf::Color& col) {
			return RGB_to_HSV<r_type, std::vector<uint8_t>>({ col.r, col.g, col.b, col.a });
		}

		template<typename r_type = sf::Color, typename p_type = std::vector<float>, typename cast = uint8_t>
		r_type HSV_to_RGB(const p_type& col) {
			float C = col[2] * col[1];
			float h = col[0] / 60.0f;
			float X = C * (1 - std::fabs(std::fmod(h, 2) - 1));
			float m = col[2] - C;
			switch (int(h))
			{
			case 0: return { (cast)std::round((C + m) * 255.0f), (cast)std::round((X + m) * 255.0f), (cast)std::round((m) * 255.0f), (cast)col[3] };
			case 1: return { (cast)std::round((X + m) * 255.0f), (cast)std::round((C + m) * 255.0f), (cast)std::round((m) * 255.0f), (cast)col[3] };
			case 2: return { (cast)std::round((m) * 255.0f), (cast)std::round((C + m) * 255.0f), (cast)std::round((X + m) * 255.0f), (cast)col[3] };
			case 3: return { (cast)std::round((m) * 255.0f), (cast)std::round((X + m) * 255.0f), (cast)std::round((C + m) * 255.0f), (cast)col[3] };
			case 4: return { (cast)std::round((X + m) * 255.0f), (cast)std::round((m) * 255.0f), (cast)std::round((C + m) * 255.0f), (cast)col[3] };
			case 5: return { (cast)std::round((C + m) * 255.0f), (cast)std::round((m) * 255.0f), (cast)std::round((X + m) * 255.0f), (cast)col[3] };
			default: return { (cast)std::round((C + m) * 255.0f), (cast)std::round((X + m) * 255.0f), (cast)std::round((m) * 255.0f), (cast)col[3] };
			}
		}

		//HSV_HSL
		template<typename list1 = std::vector<float>, typename list2 = std::vector<float>, typename cast = float, typename cast2 = float>
		list1 HSV_to_HSL(list2 HSV) {
			cast h = HSV[0];
			cast l = (HSV[2] - (HSV[2] * HSV[1]) / 2.0f);
			cast s = (l == 0.0f || l == 1.0f) ? 0.0f : (HSV[2] - l) / (std::min<cast2>(l, 1.0f - l));
			return { h, s, l, (cast)HSV[3] };
		}

		template<typename list1 = std::vector<float>, typename list2 = std::vector<float>, typename cast = float, typename cast2 = float>
		list1 HSL_to_HSV(list2 HSL) {
			cast h = HSL[0];
			cast v = (HSL[2] + (HSL[1] * std::min<cast2>(HSL[2], 1.0 - HSL[2])));
			cast s = (v == 0.0f) ? 0.0f : 2.0f - (2.0f * (cast)HSL[2] / v);
			return { h, s, v, (cast)HSL[3] };
		}

		//RGB_Hex
		template<typename r_type = sf::Color, typename d_type = uint8_t>
		r_type hexToRGBA(uint32_t hex) {
			d_type r = hex >> 24;
			uint32_t x = hex << 8;
			d_type g = x >> 24;
			x = hex << 16;
			d_type b = x >> 24;
			x = hex << 24;
			d_type a = x >> 24;
			return { r, g, b, a };
		}

		template<typename r_type = sf::Color, typename d_type = uint8_t>
		r_type hexToRGB(uint32_t hex, d_type alpha = 255) {
			uint32_t x = hex << 8;
			d_type r = x >> 24;
			x = hex << 16;
			d_type g = x >> 24;
			x = hex << 24;
			d_type b = x >> 24;
			return { r, g, b, alpha };
		}

		uint32_t RGBA_toHex(const sf::Color& color) {
			uint32_t hex = color.r;
			hex <<= 8;
			hex += color.g;
			hex <<= 8;
			hex += color.b;
			hex <<= 8;
			hex += color.a;
			return hex;
		}

		template<typename type = std::vector<uint8_t>>
		uint32_t RGBA_toHex(const type& color) {
			uint32_t hex = color[0];
			hex <<= 8;
			hex += color[1];
			hex <<= 8;
			hex += color[2];
			hex <<= 8;
			hex += color[3];
			return hex;
		}

		//Vec_Color
		template<typename list = std::vector<uint8_t>, typename cast = uint8_t>
		list colorToVector(const sf::Color& col) {
			return { (cast)col.r, (cast)col.g, (cast)col.b, (cast)col.a };
		}

		template<typename list = std::vector<uint8_t>, typename list2 = std::vector<int>, typename cast = uint8_t>
		list vectorToVector(const list2& col) {
			return { (cast)col[0], (cast)col[1], (cast)col[2], (cast)col[3] };
		}

		template<typename list = std::vector<uint8_t>>
		sf::Color vectorToColor(const list& col) {
			return { (uint8_t)col[0], (uint8_t)col[1], (uint8_t)col[2], (uint8_t)col[3] };
		}

		//lerp
		template<typename list = std::vector<float>, typename type = float>
		list lerpHue(const list& Hue1, type Hue , type x) {
			return { Hue1[0] + (Hue - Hue1[0]) * x, Hue1[1], Hue1[2], Hue1[3] };
		}

		template<typename type = float>
		sf::Color lerp(const sf::Color& L1, const sf::Color& L2, type x1, type x2, type x3, type x4) {
			return {
				(uint8_t)(L1.r + (L2.r - L1.r) * x1),
				(uint8_t)(L1.g + (L2.g - L1.g) * x2),
				(uint8_t)(L1.b + (L2.b - L1.b) * x3),
				(uint8_t)(L1.a + (L2.a - L1.a) * x4)
			};
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list lerp(const list& L1, const list& L2, const type x1, type x2, type x3, type x4) {
			return { 
				(cast)(L1[0] + (L2[0] - L1[0]) * x1),
				(cast)(L1[1] + (L2[1] - L1[1]) * x2),
				(cast)(L1[2] + (L2[2] - L1[2]) * x3),
				(cast)(L1[3] + (L2[3] - L1[3]) * x4)
			};
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list lerp(const list& L1, const sf::Color& L2, type x1, type x2, type x3, type x4) {
			return {
				(cast)(L1[0] + (L2.r - L1[0]) * x1),
				(cast)(L1[1] + (L2.g - L1[1]) * x2),
				(cast)(L1[2] + (L2.b - L1[2]) * x3),
				(cast)(L1[3] + (L2.a - L1[3]) * x4)
			};
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list lerp(const sf::Color& L1, const list& L2, type x1, type x2, type x3, type x4) {
			return {
				(cast)(L1.r + (L2[0] - L1.r) * x1),
				(cast)(L1.g + (L2[1] - L1.g) * x2),
				(cast)(L1.b + (L2[2] - L1.b) * x3),
				(cast)(L1.a + (L2[3] - L1.a) * x4)
			};
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list lerp(const list& L1, const list& L2, type x) {
			return lerp<list, type, cast>(L1, L2, x, x, x, x);
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list lerp(const list& L1, const sf::Color& L2, type x) {
			return lerp<list, type, cast>(L1, L2, x, x, x, x);
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list lerp(const sf::Color& L1, const list& L2, type x) {
			return lerp<list, type, cast>(L1, L2, x, x, x, x);
		}

		template<typename type = float>
		sf::Color lerp(const sf::Color& L1, const sf::Color& L2, type x) {
			return lerp<type>(L1, L2, x, x, x, x);
		}

		//Additive Mixing
		template<typename type = float>
		sf::Color additive_mixing(const sf::Color& L1, const sf::Color& L2) {
			return {
				(uint8_t)((L2.r + L1.r) * 0.5f),
				(uint8_t)((L2.g + L1.g) * 0.5f),
				(uint8_t)((L2.b + L1.b) * 0.5f),
				(uint8_t)((L2.a + L1.a) * 0.5f)
			};
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list additive_mixing(const sf::Color& L1, const list& L2) {
			return {
				(cast)((L2[0] + L1.r) * 0.5f),
				(cast)((L2[1] + L1.g) * 0.5f),
				(cast)((L2[2] + L1.b) * 0.5f),
				(cast)((L2[3] + L1.a) * 0.5f)
			};
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list additive_mixing(const list& L1, const sf::Color& L2) {
			return {
				(cast)((L2.r + L1[0]) * 0.5f),
				(cast)((L2.r + L1[1]) * 0.5f),
				(cast)((L2.r + L1[2]) * 0.5f),
				(cast)((L2.r + L1[3]) * 0.5f)
			};
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list additive_mixing(const list& L1, const list& L2) {
			return {
				(cast)((L2[0] + L1[0]) * 0.5f),
				(cast)((L2[1] + L1[1]) * 0.5f),
				(cast)((L2[2] + L1[2]) * 0.5f),
				(cast)((L2[3] + L1[3]) * 0.5f)
			};
		}

		template<typename listof = std::vector<std::pair<std::vector<uint8_t>, int>>,
			typename r_type = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		r_type additive_mixing(const listof& L1) {
			type r = 0, g = 0, b = 0, a = 0;
			type n = 0;
			for (auto i : L1) {
				r += i.first[0] * (type)i.second;
				g += i.first[1] * (type)i.second;
				b += i.first[2] * (type)i.second;
				a += i.first[3] * (type)i.second;
				n += i.second;
			}
			r = std::round(r / n);
			g = std::round(g / n);
			b = std::round(b / n);
			a = std::round(a / n);
			return { (cast)r, (cast)g, (cast)b, (cast)a };
		}

		template<typename type = float>
		sf::Color additive_mixing(const std::vector<std::pair<sf::Color, int>>& L1) {
			type r = 0, g = 0, b = 0, a = 0;
			type n = 0;
			for (auto i : L1) {
				r += i.first.r * (type)i.second;
				g += i.first.g * (type)i.second;
				b += i.first.b * (type)i.second;
				a += i.first.a * (type)i.second;
				n += i.second;
			}
			r = std::round(r / n);
			g = std::round(g / n);
			b = std::round(b / n);
			a = std::round(a / n);
			return { (uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a };
		}

		//Subtractive Mixing
		template<typename type = float>
		sf::Color subtractive_mixing(const sf::Color& L1, const sf::Color& L2) {
			return {
				(uint8_t)((L2.r * L1.r) / 255.0f),
				(uint8_t)((L2.g * L1.g) / 255.0f),
				(uint8_t)((L2.b * L1.b) / 255.0f),
				(uint8_t)((L2.a * L1.a) / 255.0f)
			};
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list subtractive_mixing(const sf::Color& L1, const list& L2) {
			return {
				(cast)((L2[0] * L1.r) / 255.0f),
				(cast)((L2[1] * L1.g) / 255.0f),
				(cast)((L2[2] * L1.b) / 255.0f),
				(cast)((L2[3] * L1.a) / 255.0f)
			};
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list subtractive_mixing(const list& L1, const sf::Color& L2) {
			return {
				(cast)((L2.r * L1[0]) / 255.0f),
				(cast)((L2.r * L1[1]) / 255.0f),
				(cast)((L2.r * L1[2]) / 255.0f),
				(cast)((L2.r * L1[3]) / 255.0f)
			};
		}

		template<typename list = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
		list subtractive_mixing(const list& L1, const list& L2) {
			return {
				(cast)((L2[0] * L1[0]) / 255.0f),
				(cast)((L2[1] * L1[1]) / 255.0f),
				(cast)((L2[2] * L1[2]) / 255.0f),
				(cast)((L2[3] * L1[3]) / 255.0f)
			};
		}

		template<typename listof = std::vector<std::vector<uint8_t>>,
			typename r_type = std::vector<uint8_t>, typename type = float, typename cast = uint8_t>
			r_type subtractive_mixing(const listof& L1) {
			type r = 1.0, g = 1.0, b = 1.0, a = 1.0;
			for (auto i : L1) {
				r *= (type)i[0] / (type)255.0;
				g *= (type)i[1] / (type)255.0;
				b *= (type)i[2] / (type)255.0;
				a *= (type)i[3] / (type)255.0;
			}
			r = std::round(255 * r);
			g = std::round(255 * g);
			b = std::round(255 * b);
			a = std::round(255 * a);
			return { (cast)r, (cast)g, (cast)b, (cast)a };
		}

		template<typename type = float>
			sf::Color subtractive_mixing(const std::vector<sf::Color>& L1) {
			type r = 1.0, g = 1.0, b = 1.0, a = 1.0;
			for (auto i : L1) {
				r *= (type)i.r / (type)255.0;
				g *= (type)i.g / (type)255.0;
				b *= (type)i.b / (type)255.0;
				a *= (type)i.a / (type)255.0;
			}
			r = std::round(255 * r);
			g = std::round(255 * g);
			b = std::round(255 * b);
			a = std::round(255 * a);
			return { (uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a };
		}

		//Gradient
		template<typename list = std::vector<float>, typename type = float>
		std::vector<list> gradientHue(list Hue1, list Hue2, int n) {
			std::vector<list> ColList;
			for (int i = 0; i < n; i++) {
				float t = (float)i / (float)n;
				ColList.push_back(lerp<list, type, type>(Hue1, Hue2, t));
			}
			return ColList;
		}

		template<typename type = float>
		std::vector<sf::Color> gradientRGBA(sf::Color Col1, sf::Color Col2, int n) {
			std::vector<sf::Color> ColList;
			for (int i = 0; i < n; i++) {
				float t = (float)i / (float)n;
				ColList.push_back(lerp<type>(Col1, Col2, t));
			}
			return ColList;
		}
		
		template<typename list = std::vector<float>, typename type = float>
		std::vector<list> gradientRGBA(list Hue1, list Hue2, int n) {
			std::vector<list> ColList;
			for (int i = 0; i < n; i++) {
				float t = (float)i / (float)n;
				ColList.push_back(lerp<list, type, type>(Hue1, Hue2, t));
			}
			return ColList;
		}
	}
}