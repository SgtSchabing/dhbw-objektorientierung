#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "Vektor2d.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

class GameWindow : public Gosu::Window
{
	Gosu::Image ball;
	double x, y, xSpeed, ySpeed;
	const unsigned int w_width = 1500;
	const unsigned int w_height = 900;
	const unsigned int schleuderspitze_x = 230;
	const unsigned int schleuderspitze_y = w_height - 200;
	const double xSpeedCorrection = 0.3;
	const double ySpeedCorrection = 0.19;
	const double gravity = 1.5;
	bool isFlying = false;

public:
	
	GameWindow()
		: Window(1500, 900),
		ball("planet3.png") //direkt beim initialisieren mit bild laden
	{
		set_caption("Angry Ballz");
	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt --> KEINE LOGIK!!
	void draw() override
	{
		if (!isFlying) {		//ball nicht unterwegs, an schleuder
			graphics().draw_quad(							//Schleuderstab
				220, w_height, Gosu::Color::GREEN,
				240, w_height, Gosu::Color::YELLOW,
				220, w_height - 200, Gosu::Color::YELLOW,
				240, w_height - 200, Gosu::Color::YELLOW, 0.0);

			ball.draw_rot(x, y, 0.0, 0, 0.5, 0.5, 0.05, 0.05);

			graphics().draw_line(
				x, y, Gosu::Color::WHITE, schleuderspitze_x, schleuderspitze_y, Gosu::Color::WHITE, 0.0);


		}


		else {		//Ball losgeschossen, keine steuerung
			graphics().draw_quad(							//Schleuderstab
				220, w_height, Gosu::Color::YELLOW,
				240, w_height, Gosu::Color::YELLOW,
				220, w_height - 200, Gosu::Color::YELLOW,
				240, w_height - 200, Gosu::Color::YELLOW, 0.0);

			ball.draw_rot(x, y, 0.0, 0, 0.5, 0.5, 0.05, 0.05);
		}
	}
	// Wird 60x pro Sekunde aufgerufen --> HIER LOGIK!
	void update() override
	{
		
		if (!isFlying) {				//fliegt nicht, eingabe
			x = input().mouse_x();
			y = input().mouse_y();
			if (input().down(Gosu::ButtonName::MS_LEFT)) {
				isFlying = true;
				ySpeed = (schleuderspitze_y - y)*ySpeedCorrection;
				xSpeed = (schleuderspitze_x - x)*xSpeedCorrection;
			}
		}

		else {							//fliegt, keine eingabe
			if (input().down(Gosu::ButtonName::MS_RIGHT)) { isFlying = false; }
			y = y + ySpeed;
			x = x + xSpeed;
			ySpeed = ySpeed + gravity;
		}


		if (input().down(Gosu::ButtonName::KB_ESCAPE)) { this->close(); }
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
