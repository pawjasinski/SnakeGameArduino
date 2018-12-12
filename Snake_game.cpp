#include <Arduino.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//Wpisz tutaj numery pinow ktore podlaczasz do wyswietlacza
#define CLK	13
#define DIN	11
#define DC	5
#define CE	4
#define RST	3
#define ROW 2
#define COL 16
#define ADRESSLCD 0x27
#define INITLENGHT 4

LiquidCrystal_I2C lcd(ADRESSLCD, COL, ROW); // Create object assistance display
Adafruit_PCD8544 display(CLK, DIN, DC, CE, RST);

enum class Direction { UP, DOWN, RIGHT, LEFT };

const uint8_t MaxWidth		= 84; //x
const uint8_t MaxHeight		= 48; //y
const uint8_t sizeOfArray 	= 200;


class Snake {
private:
	uint8_t xSnake[sizeOfArray];
	uint8_t ySnake[sizeOfArray];
	uint8_t xEgg;
	uint8_t yEgg;
	uint8_t gameSpeed;
	Direction actualDir;
	Direction oldDir;
	uint8_t snakeLength;
	uint8_t posHeadSnakeInArray;
	const uint8_t MoveRange; // Step of move in game
	// Czeka na wcisniecie przycisku odpowiednia ilosc czasu
	// zalezna od szybkosci gry
	void readMove() {
		delay(300);
	};
	void updateArrayOfSnake(Direction dir) {
		switch(dir) {
		case Direction::UP:
			xSnake[posHeadSnakeInArray] ;
			ySnake[posHeadSnakeInArray] -= MoveRange ;
			if(xEgg == xSnake[posHeadSnakeInArray] && yEgg == ySnake[ySnake[posHeadSnakeInArray]]) {
				snakeLength += 1;
				randomEgg();
			}
			posHeadSnakeInArray += 1;
			break;
		case Direction::DOWN:
			xSnake[posHeadSnakeInArray] ;
			ySnake[posHeadSnakeInArray] += MoveRange;
			if(xEgg == xSnake[posHeadSnakeInArray] && yEgg == ySnake[ySnake[posHeadSnakeInArray]]) {
				snakeLength += 1;
				randomEgg();
			}
			posHeadSnakeInArray += 1;
			break;
		case Direction::LEFT:
			xSnake[posHeadSnakeInArray] -= MoveRange;
			ySnake[posHeadSnakeInArray] ;
			if(xEgg == xSnake[posHeadSnakeInArray] && yEgg == ySnake[ySnake[posHeadSnakeInArray]]) {
				snakeLength += 1;
				randomEgg();
			}
			posHeadSnakeInArray += 1;
			break;
		case Direction::RIGHT:
			xSnake[posHeadSnakeInArray] ;
			ySnake[posHeadSnakeInArray] += MoveRange;
			if(xEgg == xSnake[posHeadSnakeInArray] && yEgg == ySnake[ySnake[posHeadSnakeInArray]]) {
				snakeLength += 1;
				randomEgg();
			}
			posHeadSnakeInArray += 1;
			break;
		default:
			break;
		}
	}
	void assistantLCDScore() {
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Gra Snake by Pawel");
		lcd.setCursor(0,1);
		lcd.print("Wynik: ");
		lcd.print(snakeLength - INITLENGHT);
	};
	void randomEgg() {
		xEgg = random(1, MaxWidth - 1);
		while( !(xEgg % 2) ) xEgg = random(1, MaxWidth - 1);
		yEgg = random(1, MaxHeight -1);
		while( !(yEgg % 2) ) yEgg = random(1, MaxHeight -1);
	}
public:
	Snake() : gameSpeed(1), snakeLength(INITLENGHT), actualDir(Direction::RIGHT), MoveRange(2)  {
		/* Nalezy koniecznie wykluczyc mozliwosc wylosowania Egg
		 * na aktualnym polozeniu weza */
		oldDir = actualDir;
		posHeadSnakeInArray = INITLENGHT;
		uint8_t xInit = 20; //Ustawienia poczatkowe polozenia weza
		uint8_t yInit = 24;
		for(int i = 0; i < snakeLength; ++i) {
			xSnake[i] = xInit += MoveRange;
			ySnake[i] = yInit;
		}
		randomEgg(); // losowanie wsp jajka
	};
	~Snake() {};
	void draw() {
		display.clearDisplay();
		for(int i = posHeadSnakeInArray - snakeLength; i < posHeadSnakeInArray; ++i) {
			display.drawCircle(xSnake[i], ySnake[i], 1, BLACK);
		}
		display.drawCircle(xEgg, yEgg, 1, BLACK);
		display.display();
		assistantLCDScore();
		readMove(); // Czekamy na wcisniecie przyscisku
	};
	void logic() {
		switch(actualDir) {
		case Direction::UP:
			if (oldDir == Direction::DOWN) actualDir = oldDir;
			updateArrayOfSnake(actualDir);
			break;
		case Direction::DOWN:
			if (oldDir == Direction::UP) actualDir = oldDir;
			updateArrayOfSnake(actualDir);
			break;
		case Direction::RIGHT:
			if (oldDir == Direction::LEFT) actualDir = oldDir;
			updateArrayOfSnake(actualDir);
			break;
		case Direction::LEFT:
			if (oldDir == Direction::RIGHT) actualDir = oldDir;
			updateArrayOfSnake(actualDir);
			break;
		default:break;
		}
	};
	void game() {

	};
};
Snake snake;

void setup() {
	lcd.init();			//Assistance display init
	lcd.backlight();//assistance disp light ON
	display.begin();
	display.setContrast(50);
}

void loop() {
	snake.draw();
	snake.logic();
}
