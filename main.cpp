#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>
#include "Color.h"
#include "Screen.h"
#include "Vector2.h"
#include "Transform.h"
#include "Object.h"
#include "Rectangle.h"

const float PI = 3.141592f;
const int WIDTH = 432;
const int HEIGHT = 240;

// 432x240 / 320x240 / 160x120 / 100x100 / 120x90 //
// CMD Line height = 0.6 //

Screen screen(WIDTH, HEIGHT);

Color::Color colors[20] = {Color::Black, Color::Red, Color::Green, Color::Yellow, Color::Blue, Color::Purple, Color::Cyan,
							Color::IntenseBlack, Color::IntenseRed, Color::IntenseGreen, Color::IntenseYellow, Color::IntenseBlue, Color::IntensePurple, Color::IntenseCyan};

int main()
{

    Object *object = new Rectangle(0, HEIGHT / 2, 30, 30, Color::White);

	int curentKey;
    bool running = true;
    while (running)
    {
        if (_kbhit())
			curentKey = _getch();

		if (curentKey == 32) CLEAR_CONSOLE
		if (curentKey == 27) running = false;

		curentKey = 0;

        object->Rotate(0.4f);
        object->Move(Vector2(10.f, 0));
        object->Scale(Vector2(-0.08f, -0.08f));

        screen.Clear(Color::Black);

        object->Draw(screen);

        screen.Display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return 0;
}