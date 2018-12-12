#include <Arduino.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define CLK	13
#define DIN	11
#define DC	5
#define CE	4
#define RST	3

LiquidCrystal_I2C lcd(0x27, 16, 2); // Create object assistance display
Adafruit_PCD8544 display(13, 11, 5, 4, 3);

enum class Direction { UP, DOWN, RIGHT, LEFT };

const uint8_t MaxWidth		= 84; //x
const uint8_t MaxHeight	= 48; //y


class Snake {
private:
	uint8_t xSnake[200];
	uint8_t ySnake[200];
	uint8_t xEgg;
	uint8_t yEgg;
	uint8_t gameSpeed;
	Direction actualDir;
	uint8_t snakeLength;
	const uint8_t MoveRange = 2;

public:
	Snake() : gameSpeed(1), SnakeLength(4), actualDir(Direction::LEFT)  {
		xEgg = random(1, MaxWidth - 1);
		yEgg = random(1, MaxHeight -1);
		uint8_t xInit = 40;
		uint8_t yInit = 24;
		for(int i = 0; i < snakeLength; ++i) {
			xSnake[i] = xInit += MoveRange;
			ySnake[i] = yInit;
		}
	};
	~Snake() {};
	void draw() {
		for(int i = 0; i < snakeLength; ++i) {
			display.drawCircle(x[i], y[i], 1, 1);
		}
	};
	void logic() {

	};
	void game() {

	};
};


void setup() {
	lcd.init();			//Assistance display init
	lcd.backlight();	//assistance disp light ON
	//game init
}

void loop() {
	//draw
	//logic//
	//game

}
