#include "libs.h"

int main(void)
{
	int score = 0;
	double speed = 5;
	double dx = 0;
	double dy = 0;


	//create window
	sf::RenderWindow window(sf::VideoMode(700, 700), "Breakout!");
	window.setFramerateLimit(60);

	//creat font
	sf::Font font;
	font.loadFromFile("Roboto-Black.ttf");


	//create ball shape
	sf::CircleShape ball(7.f);
	ball.setFillColor(sf::Color::Green);
	ball.setPosition(350, 640);

	//create paddle shape
	sf::RectangleShape player(sf::Vector2f(70, 10));
	player.setFillColor(sf::Color::White);
	player.setPosition(322, 656);

sf::RectangleShape brick(sf::Vector2f(100, 25));

	std::vector<Brick> bricks;

	for (int iX{ 0 }; iX < 6; ++iX)
	{
		for (int iY{ 0 }; iY < 4; ++iY)
		{
			bricks.emplace_back((iX + 1) * (100 + 10) + 20, (iY + 2) * (25 + 3));
		}
	}

	while (window.isOpen())
	{
		sf::Vector2f ballPos = ball.getPosition();
		sf::Vector2f playerPos = player.getPosition();

		//detect collisionsd
		if (ballPos.x < 0) dx = speed;
		else if (ballPos.x > 800 - 10) dx = -speed;
		if (ballPos.y < 0) dy = speed;
		else if (ballPos.y > 800 - 10)
		{
			dx = 0;
			dy = 0;
		}

		if (ballPos.x >= playerPos.x && ballPos.x <= playerPos.x + 70)
		{
			if (ballPos.y >= playerPos.y - 10 && ballPos.x < playerPos.x + 35)
			{
				dy = -speed;
				dx = -speed;
			}
			else if (ballPos.y >= playerPos.y - 10 && ballPos.x <= playerPos.x + 70)
			{
				dy = -speed;
				dx = speed;
			}
		}

		//move ball
		ball.move(dx, dy);

		//input detection
			//release ball
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			dx = speed;
			dy = speed;
			score = 0;
		}
		
			//move left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			if (playerPos.x > 0)
				player.move(-speed, 0);
		
			//move right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			if (playerPos.x < 800 - 70) // need to make this static varible
				player.move(speed, 0);



			//close window
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//render
		window.clear();
		window.draw(ball);
		window.draw(player);
		for (auto& brick : bricks)
		{
			window.draw(brick.shape);
		}

		//draw text
		window.display();



	}
//	sf::RenderWindow window(sf::VideoMode(600, 972), "Breakout");

	return 0;
}
