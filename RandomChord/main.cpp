#include "App.hpp"
#include "sfhelper.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <filesystem>

class RandomChord : public App {
public:
	sf::CircleShape C1, Center, EquilateralTriangle, C2;

	std::vector<sf::Vertex> lines;
	sf::CircleShape a, b;

	float cRad = 500, thickness = 4;

	int greater = 0, total = 0;

	const float pi = 2 * std::asin(1.0f);

	int mode = 0;

	std::string fontName;
	sf::Font font;
	sf::Text text1, text2;

	int frameRate;
	bool vSync, drawTriangle, drawHalfRadiusCircle, drawCenter, make_color, randomSeed, SaveFrame;
	int Seed;
	int FrameNumber, numhash;

	std::string folder, filename, type;

	sf::Color CircleColor, innerCircleColor, triangleColor, centerColor, lineColor, radialColor, nomakeLine, State1, State2, TexCol, BackGround, Point1, Point2;

	sf::RenderTexture Tex;
	RandomChord() {
		name = "RandomChord";
		create_window();

		load_ini();

		window.setVerticalSyncEnabled(vSync);
		window.setFramerateLimit(frameRate);
	}

	uint32_t hex2int(const char* hex) {
		uint32_t val = 0;
		while (*hex!='\0') {
			uint8_t byte = *hex;
			if (byte >= '0' && byte <= '9') byte = byte - '0';
			else if (byte >= 'a' && byte <= 'f') byte = byte - 'a' + 10;
			else if (byte >= 'A' && byte <= 'F') byte = byte - 'A' + 10;
			val = (val << 4) | (byte & 0xF);
			hex++;
		}
		return val;
	}

	void load_ini() {
		std::fstream fs("settings.ini");
		std::string dump;

		fs >> dump;
		fs >> mode;
		fs >> dump;
		fs >> vSync;
		fs >> dump;
		fs >> frameRate;
		fs >> dump;
		fs >> drawTriangle;
		fs >> dump;
		fs >> drawHalfRadiusCircle;
		fs >> dump;
		fs >> drawCenter;
		fs >> dump;
		fs >> make_color;
		fs >> dump;
		fs >> fontName;
		fs >> dump;
		fs >> randomSeed;
		fs >> dump;
		fs >> Seed;
		fs >> dump;
		fs >> SaveFrame;
		fs >> dump;
		fs >> folder;
		fs >> dump;
		fs >> filename;
		fs >> dump;
		fs >> type;
		fs >> dump;

		fs >> dump;
		fs >> dump;
		CircleColor = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		innerCircleColor = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		triangleColor = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		centerColor = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		lineColor = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		radialColor = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		nomakeLine = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		State1 = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		State2 = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		TexCol = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		BackGround = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs >> dump;
		fs >> dump;
		Point1 = sfh::color::hexToRGBA(hex2int(dump.c_str()));
		Point2 = sfh::color::hexToRGBA(hex2int(dump.c_str()));

		fs.close();
	}

	void setup() {
		if (!randomSeed) sfh::random::mt_engine.seed(Seed);
		C1.setPointCount(1000);
		C1.setRadius(cRad);
		C1.setOrigin(C1.getRadius(), C1.getRadius());
		C1.setFillColor(sf::Color::Transparent);
		C1.setOutlineThickness(thickness);
		C1.setOutlineColor(CircleColor);
		C1.setPosition(width / 2.f, height / 2.f);

		EquilateralTriangle = C1;
		EquilateralTriangle.setOutlineColor(triangleColor);
		EquilateralTriangle.setPointCount(3);
		EquilateralTriangle.setOutlineThickness(2);

		C2.setPointCount(1000);
		C2.setRadius(cRad/2);
		C2.setOrigin(C2.getRadius(), C2.getRadius());
		C2.setFillColor(sf::Color::Transparent);
		C2.setOutlineThickness(2);
		C2.setOutlineColor(innerCircleColor);
		C2.setPosition(width / 2.f, height / 2.f);

		Center.setPointCount(100);
		Center.setRadius(5);
		Center.setOrigin(Center.getRadius(), Center.getRadius());
		Center.setFillColor(centerColor);
		Center.setOutlineThickness(0);
		Center.setPosition(width / 2.f, height / 2.f);

		a = b = Center;
		a.setRadius(10);
		a.setOrigin(a.getRadius(), a.getRadius());
		b.setRadius(10);
		b.setOrigin(b.getRadius(), b.getRadius());
		a.setFillColor(Point1);
		b.setFillColor(Point2);

		font.loadFromFile(fontName);
		text1.setPosition(20, 20);
		text1.setFont(font);
		text1.setFillColor(TexCol);

		text2.setPosition(20, 80);
		text2.setFont(font);
		text2.setFillColor(TexCol);

		numhash = std::count(filename.begin(), filename.end(), '#');
		filename.erase(remove(filename.begin(), filename.end(), '#'), filename.end());

		Tex.create(width, height, window.getSettings());
	}

	void DrawText() {
		text1.setString("P(l > sqrt(3)) = " + std::to_string(greater) +  "/" + std::to_string(total) +  " = " + std::to_string((float)greater/(float)total));
		
		std::string expected = mode == 0 ? "1/3" :
			(mode == 1 ? "1/4" : 
				(mode == 2 ? "1/2" : 
					(mode == 3 ? "0.628" : "0.428")));

		std::string modeName = mode == 0 ? "" :
			(mode == 1 ? "1/4" :
				(mode == 2 ? "1/2" :
					(mode == 3 ? "0.60" : "0.42")));
		text2.setString("Expected P(l > sqrt(3)) = " + expected);
		Tex.draw(text1);
		Tex.draw(text2);
	}

	void randomChordUsing2Points() {
		auto point1 = sfh::normalize2d(sfh::random::random2d(-1.0f, 1.0f));
		auto point2 = sfh::normalize2d(sfh::random::random2d(-1.0f, 1.0f));

		float dist = sfh::distance2d(point1, point2);
		if (dist > std::sqrt(3)) greater++;
		total++;

		sf::Color col;
		if (!make_color) col = nomakeLine;
		else {
			if (dist >= std::sqrt(3)) col = State1;
			else col = State2;
		}

		point1.x = point1.x * cRad + width / 2.f;
		point1.y = point1.y * cRad + height / 2.f;
		a.setPosition(point1);

		point2.x = point2.x * cRad + width / 2.f;
		point2.y = point2.y * cRad + height / 2.f;
		b.setPosition(point2);

		auto line = sfh::shape::thickLine(point1, point2, 6, lineColor);

		if(lines.size() > 0) Tex.draw(&lines[0], lines.size(), sf::Lines);

		auto Line = sfh::shape::line(point1, point2, col);
		lines.insert(lines.end(), Line.begin(), Line.end());

		if (lines.size() > 1000) {
			lines.erase(lines.begin());
			lines.erase(lines.begin());
		}

		Tex.draw(&line[0], line.size(), sf::TrianglesStrip);
		Tex.draw(a);
		Tex.draw(b);
	}

	void randomChordUsingRandomCenterPoint() {
		float r = std::sqrt(sfh::random::random1d(0.f, 1.f));
		float angle = sfh::random::random1d(0.f, 1.f) * 2.f * pi;

		float x = r * std::cos(angle);
		float y = r * std::sin(angle);

		auto vec = sf::Vector2f(x, y);

		auto [vec1, vec2] = sfh::normal(vec);
		vec1 = sfh::normalize2d(vec1);
		vec2 = sfh::normalize2d(vec2);

		float p = (vec2.y - vec1.y) / (vec2.x - vec1.x);
		float q = -p * vec.x + vec.y;

		float denom = 1 + p * p;
		float delta = std::sqrt(denom - q * q);

		auto v = vec;
		auto v1 = sf::Vector2f((-(q * p) + delta) / denom, (q + p * delta) / denom);
		auto v2 = sf::Vector2f((-(q * p) - delta) / denom, (q - p * delta) / denom);

		float dist = sfh::distance2d(v1, v2);
		if (dist > std::sqrt(3)) greater++;
		total++;

		sf::Color col;
		if (!make_color) col = nomakeLine;
		else {
			if (dist > std::sqrt(3)) col = State1;
			else col = State2;
		}

		v.x = v.x * cRad + width / 2.f;
		v.y = v.y * cRad + height / 2.f;

		v1.x = v1.x * cRad + width / 2.f;
		v1.y = v1.y * cRad + height / 2.f;

		v2.x = v2.x * cRad + width / 2.f;
		v2.y = v2.y * cRad + height / 2.f;

		a.setPosition(v);

		auto line = sfh::shape::thickLine(v1, v2, 6, lineColor);
		auto line2 = sfh::shape::thickLine(v, { width / 2.f , height / 2.f }, 6, radialColor);

		if (lines.size() > 0) Tex.draw(&lines[0], lines.size(), sf::Lines);

		auto Line = sfh::shape::line(v1, v2, col);
		lines.insert(lines.end(), Line.begin(), Line.end());

		if (lines.size() > 1000) {
			lines.erase(lines.begin());
			lines.erase(lines.begin());
		}

		Tex.draw(&line[0], line.size(), sf::TrianglesStrip);
		Tex.draw(&line2[0], line2.size(), sf::TrianglesStrip);
		Tex.draw(a);
	}

	void randomChordUsingRadius() {
		float angle = sfh::random::random1d(0.f, 1.f) * 2 * pi;
		float t = sfh::random::random1d(0.f, 1.f);

		auto Rad_vec = sf::Vector2f(std::cos(angle), std::sin(angle));
		auto vec = sf::Vector2f(
			sfh::map(t, 0.f, 1.f, 0.f, Rad_vec.x),
			sfh::map(t, 0.f, 1.f, 0.f, Rad_vec.y)
		);

		auto [vec1, vec2] = sfh::normal(vec);
		vec1 = sfh::normalize2d(vec1);
		vec2 = sfh::normalize2d(vec2);

		float p = (vec2.y - vec1.y) / (vec2.x - vec1.x);
		float q = -p * vec.x + vec.y;

		float denom = 1 + p * p;
		float delta = std::sqrt(denom - q * q);

		auto v = Rad_vec;
		auto vx = vec;
		auto v1 = sf::Vector2f((-(q * p) + delta) / denom, (q + p * delta) / denom);
		auto v2 = sf::Vector2f((-(q * p) - delta) / denom, (q - p * delta) / denom);

		float dist = sfh::distance2d(v1, v2);
		if (dist > std::sqrt(3)) greater++;
		total++;

		sf::Color col;
		if (!make_color) col = nomakeLine;
		else {
			if (dist > std::sqrt(3)) col = State1;
			else col = State2;
		}

		v.x = v.x * cRad + width / 2.f;
		v.y = v.y * cRad + height / 2.f;

		vx.x = vx.x * cRad + width / 2.f;
		vx.y = vx.y * cRad + height / 2.f;

		v1.x = v1.x * cRad + width / 2.f;
		v1.y = v1.y * cRad + height / 2.f;

		v2.x = v2.x * cRad + width / 2.f;
		v2.y = v2.y * cRad + height / 2.f;

		a.setPosition(vx);

		auto line = sfh::shape::thickLine(v1, v2, 6, lineColor);
		auto line2 = sfh::shape::thickLine(v, { width / 2.f , height / 2.f }, 6, radialColor);

		if (lines.size() > 0) Tex.draw(&lines[0], lines.size(), sf::Lines);

		auto Line = sfh::shape::line(v1, v2, col);
		lines.insert(lines.end(), Line.begin(), Line.end());

		if (lines.size() > 1000) {
			lines.erase(lines.begin());
			lines.erase(lines.begin());
		}

		Tex.draw(&line[0], line.size(), sf::TrianglesStrip);
		Tex.draw(&line2[0], line2.size(), sf::TrianglesStrip);
		Tex.draw(a);
	}

	void randomChordUsingRandomPointAndAngle() {
		float r = std::sqrt(sfh::random::random1d(0.f, 1.f));
		float angle = sfh::random::random1d(0.f, 1.f) * 2.f * pi;

		float x = r * std::cos(angle);
		float y = r * std::sin(angle);

		float angle2 = sfh::random::random1d(0.f, 1.f) * 2.f * pi;

		auto vec = sf::Vector2f(x, y);

		float p = std::tan(angle2);
		float q = -p * vec.x + vec.y;

		float denom = 1 + p * p;
		float delta = std::sqrt(denom - q * q);

		auto v = vec;
		auto v1 = sf::Vector2f((-(q * p) + delta) / denom, (q + p * delta) / denom);
		auto v2 = sf::Vector2f((-(q * p) - delta) / denom, (q - p * delta) / denom);

		float dist = sfh::distance2d(v1, v2);
		if (dist > std::sqrt(3)) greater++;
		total++;

		sf::Color col;
		if (!make_color) col = nomakeLine;
		else {
			if (dist > std::sqrt(3)) col = State1;
			else col = State2;
		}

		v.x = v.x * cRad + width / 2.f;
		v.y = v.y * cRad + height / 2.f;

		v1.x = v1.x * cRad + width / 2.f;
		v1.y = v1.y * cRad + height / 2.f;

		v2.x = v2.x * cRad + width / 2.f;
		v2.y = v2.y * cRad + height / 2.f;

		a.setPosition(v);

		auto line = sfh::shape::thickLine(v1, v2, 6, lineColor);

		if (lines.size() > 0) Tex.draw(&lines[0], lines.size(), sf::Lines);

		auto Line = sfh::shape::line(v1, v2, col);
		lines.insert(lines.end(), Line.begin(), Line.end());

		if (lines.size() > 1000) {
			lines.erase(lines.begin());
			lines.erase(lines.begin());
		}

		Tex.draw(&line[0], line.size(), sf::TrianglesStrip);
		Tex.draw(a);
	}

	void Save_Frame() {
		std::stringstream ss;
		if (!std::filesystem::is_directory(std::filesystem::current_path() / folder)) std::filesystem::create_directory(std::filesystem::current_path() / folder);
		ss << std::filesystem::current_path().string() << "\\" << folder << filename << std::setw(5) << std::setfill('0') << FrameNumber << type;
		std::cout << ss.str() << "\n";
		FrameNumber++;
		Tex.getTexture().copyToImage().saveToFile(ss.str());
	}

	void randomMethod() {
		int r = sfh::random::random1d(0, 3);

		if (r == 0) randomChordUsing2Points();
		else if (r == 1) randomChordUsingRandomCenterPoint();
		else if (r == 2) randomChordUsingRadius();
		else randomChordUsingRandomPointAndAngle();
	}

	void loop() override {
		Tex.clear(BackGround);
		DrawText();

		if (mode == 0) randomChordUsing2Points();
		else if (mode == 1) randomChordUsingRandomCenterPoint();
		else if (mode == 2) randomChordUsingRadius();
		else if (mode == 3) randomChordUsingRandomPointAndAngle();
		else if (mode == 4) randomMethod();

		Tex.draw(C1);
		if (drawTriangle) Tex.draw(EquilateralTriangle);
		if (drawHalfRadiusCircle) Tex.draw(C2);
		if (drawCenter) Tex.draw(Center);
		Tex.display();

		if (SaveFrame) Save_Frame();

		sf::Sprite sprite;
		sprite.setTexture(Tex.getTexture());
		window.draw(sprite);
		window.display();
	}
};

int main() {
	RandomChord App;
	App.run();
	return 0;
}