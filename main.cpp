#include <SFML/Graphics.hpp>
#include "Player.h"
#include <Windows.h>

static const float VIEW_HEIGHT = 864.0f;
static const float VIEW_WIDHT = 564.0f;


//ฟังชั่น ในการเซ้ทค่า display ให้คงที่ตลอดหลังจากปรับขยายหรือหดหน้า
void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	// aspectRatio คือการเซ้ทค่าของหน้าจอให้คงที่ตลอดหลังจากมีการขยายหน้าจอ เป็นต้น
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_WIDHT * aspectRatio);  // การให้มันคงที่ค่าในแกน x ภาพหน้าจะเหมือนเดิม
}


int main()
{	
	float detalTime = 0.0f;       // ตั้งค่าความเร็วให้ตัวละครเดิน 
	float totaltime = 0;		  // ตั้งค่าความเร็วให้ตัวละครเดิน 	
	float speed_player = 100.0f;  // ตั้งค่าความเร็วให้ตัวละครเดิน
	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(564.0f, 864.0f), "Game_pp" );  //ขนาดหน้าจอ "ชื่อหัวเกม"
	//sf::RenderWindow window(sf::VideoMode(VIEW_WIDHT, VIEW_HEIGHT), "GamePUNPUN");  //ขนาดหน้าจอ "ชื่อหัวเกม"

	// view
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(564.0f, 864.0f));   // ทำให้การปรับหน้าจอภาพให้มีขนาดตงที่
	
	// ลองใส่พื้นหลัง
	sf::RectangleShape background(sf::Vector2f(564.0f, 864.0f)); // ให้รูปใหญ่เท่าไหร่ ก็เลือกขนาดเอา
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("sprite/background_game.jpg");
	background.setTexture(&backgroundTexture);
	//spite.setOrigin(size.x / 2, size.y / 2);

	// Item
	sf::RectangleShape Heart(sf::Vector2f(72.0f, 73.0f));
	sf::Texture Heartlove;
	Heartlove.loadFromFile("sprite/heart_main.png");
	Heart.setTexture(&Heartlove);
	Heart.setPosition({ 270,340 });

	//Hp
	sf::RectangleShape HP(sf::Vector2f(230.0f, 70.0f));
	sf::Texture HPplayer;
	HPplayer.loadFromFile("sprite/HP_1_100p.png");
	HP.setTexture(&HPplayer);
	HP.setPosition({ 50,30 });
	
	// เป็นของวงกลม
	sf::CircleShape shape(70,5);  // (ขนาด,มุมที่ให้เกิด เช่นอันนี้เป็น 5 มุม)
	shape.setPosition({ 450,400 });  // ตำแหน่งวงกลม (x,y)
	shape.setFillColor(sf::Color::White);  //สีของรูป
	
	//ตัวละคร
	sf::Texture playerTexture;
	playerTexture.loadFromFile("sprite/playermainful.png"); // ดึงรูปมาจากในไฟล์
	int animationFrame = 0; // แฟรมของตัวละคร ที่ 0 


	// animation ใน class		//การแบ่งสโคปของรูปภาพ (4,4)	//ความเร็วในการรันเฟรม (0.5f)	// ความเร็วของตัวละคร (100.0f)
	Player player(&playerTexture, sf::Vector2u(4, 6), 0.2f , 120.0f);


	while (window.isOpen())
	{	

		detalTime = clock.restart().asSeconds(); // คำสั่งหน่วงให้น้องเดินช้า
		window.draw(background); // ให้พื้นหลังแสดง
		window.draw(shape); // ให้วงกลมเคลื่อนที่
		window.draw(Heart);
		window.draw(HP);

		player.Draw(window); // ให้ตัวละครเคลื่อนที่ได้	

		sf::Event evnt;			 
		while (window.pollEvent(evnt))	// while นี้ทำให้สามารถใช้เม้ากดเต็มจอหรือใช้ขยาย กว้างยาวได้
		{
			switch (evnt.type)
			{

				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::Resized:
					ResizeView(window, view);
					break;

			}
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 

		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
			shape.setPosition((float)mousePos.x, (float)mousePos.y);
		}

	//if(shape.getGlobalBounds().intersects(player))
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) { return 0; }  // กด x เพื่อออกจากโปรแกรม

		
		player.Update(detalTime); // เป็นทุกอย่างของตัวละคร ทั้งการตัดภาพ การเดิน เอนิเมชั่น
		view.setCenter(player.GetPosition());  //กล้องตามตัวละครของเรา เซ้ทค่าให้อยุ่ตรงกลางหรือค่าที่เราเซ้ทไว้
		

		window.display();
		window.clear();
		window.setView(view);
		
	
	}

	return 0;
}