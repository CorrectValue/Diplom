#include "UI.h"

int UI::count;
int UI::hours;
int UI::minutes;
int UI::season;
int UI::weather;

void UI::drawStartWindow()
{
	//описывает стартовое окошко
	RenderWindow startWindow(sf::VideoMode(640, 480), "Start");
	Gui gui(startWindow);
	auto back = tgui::Picture::create({ "Images/UI/red-leather.jpg", { 0, 0, 640, 480} });
	gui.add(back);

	//описываем надписи в окне
	auto toplabel = Label::create("Creating simulation");
	toplabel->setPosition(130, 75);
	toplabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	toplabel->setTextColor(sf::Color(252, 211, 27));
	toplabel->setTextSize(36);
	gui.add(toplabel);

	auto seasonlabel = Label::create("Season of start");
	seasonlabel->setPosition(25, 175);
	seasonlabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	seasonlabel->setTextColor(sf::Color(252, 211, 27));
	seasonlabel->setTextSize(25);
	gui.add(seasonlabel);

	auto weatherlabel = Label::create("Weather of start");
	weatherlabel->setPosition(240, 175);
	weatherlabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	weatherlabel->setTextColor(sf::Color(252, 211, 27));
	weatherlabel->setTextSize(25);
	gui.add(weatherlabel);

	auto timelabel = Label::create("Time of start");
	timelabel->setPosition(25, 300);
	timelabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	timelabel->setTextColor(sf::Color(252, 211, 27));
	timelabel->setTextSize(25);
	gui.add(timelabel);

	auto countlabel = Label::create("Count of creatures");
	countlabel->setPosition(240, 300);
	countlabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	countlabel->setTextColor(sf::Color(252, 211, 27));
	countlabel->setTextSize(25);
	gui.add(countlabel);

	//описываем поля ввода
	EditBox::Ptr editBoxCount = tgui::EditBox::create();
	editBoxCount->setSize(130, 40);
	editBoxCount->setPosition(280, 350);
	editBoxCount->setDefaultText("50");
	editBoxCount->setInputValidator(EditBox::Validator::Int);
	gui.add(editBoxCount, "CountBox");

	ComboBox::Ptr cmbSeason = ComboBox::create();
	cmbSeason->setSize(150, 35);
	cmbSeason->setPosition(30, 225);
	cmbSeason->addItem("Summer");
	cmbSeason->addItem("Fall");
	cmbSeason->addItem("Winter");
	cmbSeason->addItem("Spring");
	cmbSeason->setSelectedItem("Summer");
	gui.add(cmbSeason);

	ComboBox::Ptr cmbWeather = ComboBox::create();
	cmbWeather->setSize(150, 35);
	cmbWeather->setPosition(280, 225);
	cmbWeather->addItem("Fallout");
	cmbWeather->addItem("Cloudy");
	cmbWeather->addItem("Clear");
	cmbWeather->addItem("Storm");
	cmbWeather->addItem("Gray");
	cmbWeather->setSelectedItem("Clear");
	gui.add(cmbWeather);

	EditBox::Ptr editBoxHours = EditBox::create();
	editBoxHours->setSize(50, 40);
	editBoxHours->setPosition(25, 350);
	editBoxHours->setDefaultText("23");
	editBoxHours->setInputValidator("([0-1]?[0-9])|2?[0-3]");
	gui.add(editBoxHours, "HoursBox");

	auto semicolonlabel = Label::create(":");
	semicolonlabel->setPosition(82, 343);
	semicolonlabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	semicolonlabel->setTextColor(sf::Color(252, 211, 27));
	semicolonlabel->setTextSize(40);
	gui.add(semicolonlabel);

	EditBox::Ptr editBoxMinutes = EditBox::create();
	editBoxMinutes->setSize(50, 40);
	editBoxMinutes->setPosition(100, 350);
	editBoxMinutes->setDefaultText("59");
	editBoxMinutes->setInputValidator("[0-5]?[0-9]");
	gui.add(editBoxMinutes, "MinutesBox");

	/*ComboBox::Ptr cmbHours = ComboBox::create();
	cmbHours->setSize(150, 35);
	cmbHours->setPosition(25, 350);
	for (int i = 0; i < 24; i++)
	{
		stringstream ss;
		ss << i;
		cmbHours->addItem(ss.str());
	}
	cmbHours->setSelectedItem("Clear");
	gui.add(cmbHours);*/

	//описать кнопки

	auto btnCreate = Button::create();
	btnCreate->setPosition(480, 175);
	btnCreate->setSize(150, 50);
	btnCreate->setText("Create");
	gui.add(btnCreate);

	auto btnRandom = Button::create();
	btnRandom->setPosition(480, 275);
	btnRandom->setSize(150, 50);
	btnRandom->setText("Random");
	gui.add(btnRandom);

	auto btnLoad = Button::create();
	btnLoad->setPosition(480, 375);
	btnLoad->setSize(150, 50);
	btnLoad->setText("Load");
	gui.add(btnLoad);

	btnCreate->connect("pressed", getData, std::ref(editBoxCount), std::ref(cmbSeason), std::ref(cmbWeather), std::ref(editBoxHours), std::ref(editBoxMinutes), std::ref(startWindow));
	btnRandom->connect("pressed", makeRandom, std::ref(startWindow));

	while (startWindow.isOpen())
	{
		sf::Event event;
		while (startWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				startWindow.close();

			}
			gui.handleEvent(event);
		}
		gui.draw();
		startWindow.display();
	}
}

void UI::drawLoadWindow()
{
	//описывает окно загрузки
	RenderWindow loadWindow(sf::VideoMode(640, 480), "Load");
	Gui gui(loadWindow);
	auto back = tgui::Picture::create({ "Images/UI/red-leather.jpg", { 0, 0, 640, 480 } });
	gui.add(back);

	//описываем надписи в окне
	auto toplabel = Label::create("Load simulation");
	toplabel->setPosition(170, 75);
	toplabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	toplabel->setTextColor(sf::Color(252, 211, 27));
	toplabel->setTextSize(36);
	gui.add(toplabel);

	auto midlabel = Label::create("Input filename without extension:");
	midlabel->setPosition(155, 180);
	midlabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	midlabel->setTextColor(sf::Color(252, 211, 27));
	midlabel->setTextSize(20);
	gui.add(midlabel);

	//описываем поле ввода
	EditBox::Ptr editBoxName = EditBox::create();
	editBoxName->setSize(400, 40);
	editBoxName->setPosition(110, 230);
	editBoxName->setDefaultText("sim1");
	gui.add(editBoxName, "NameBox");

	//описываем кнопки

	auto btnBack = Button::create();
	btnBack->setPosition(35, 350);
	btnBack->setSize(150, 50);
	btnBack->setText("Back");
	gui.add(btnBack);

	auto btnLoad = Button::create();
	btnLoad->setPosition(435, 350);
	btnLoad->setSize(150, 50);
	btnLoad->setText("Load");
	gui.add(btnLoad);

	while (loadWindow.isOpen())
	{
		sf::Event event;
		while (loadWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				loadWindow.close();

			}
			gui.handleEvent(event);
		}
		gui.draw();
		loadWindow.display();
	}
}

void UI::drawSaveWindow()
{
	//описывает окно сохранения
	RenderWindow saveWindow(sf::VideoMode(640, 480), "Save");
	Gui gui(saveWindow);
	auto back = tgui::Picture::create({ "Images/UI/red-leather.jpg", { 0, 0, 640, 480 } });
	gui.add(back);

	//описываем надписи в окне
	auto toplabel = Label::create("Save simulation");
	toplabel->setPosition(170, 75);
	toplabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	toplabel->setTextColor(sf::Color(252, 211, 27));
	toplabel->setTextSize(36);
	gui.add(toplabel);

	auto midlabel = Label::create("Input filename without extension:");
	midlabel->setPosition(155, 180);
	midlabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	midlabel->setTextColor(sf::Color(252, 211, 27));
	midlabel->setTextSize(20);
	gui.add(midlabel);

	//описываем поле ввода
	EditBox::Ptr editBoxName = EditBox::create();
	editBoxName->setSize(400, 40);
	editBoxName->setPosition(110, 230);
	editBoxName->setDefaultText("sim1");
	gui.add(editBoxName, "NameBox");

	//описываем кнопки

	auto btnBack = Button::create();
	btnBack->setPosition(35, 350);
	btnBack->setSize(150, 50);
	btnBack->setText("Back");
	gui.add(btnBack);

	auto btnsave = Button::create();
	btnsave->setPosition(435, 350);
	btnsave->setSize(150, 50);
	btnsave->setText("Save");
	gui.add(btnsave);

	while (saveWindow.isOpen())
	{
		sf::Event event;
		while (saveWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				saveWindow.close();

			}
			gui.handleEvent(event);
		}
		gui.draw();
		saveWindow.display();
	}
}

void UI::drawMainWindow(RenderWindow &window, vector<animal> &animals, vector<human> &humans, world &wrld)
{
	//описывает главное окно программы
	//в существующее главное окно программы выводятся нужные виджоты
	//в правой части окна будут виджеты
	Gui gui(window);
	auto back = tgui::Picture::create({ "Images/UI/red-leather.jpg", { 0, 0, 300, 768} });
	back->setPosition({ 724, 0 });
	gui.add(back);

	auto creatureslabel = Label::create("Creatures");
	creatureslabel->setPosition(730, 115);
	creatureslabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	creatureslabel->setTextColor(sf::Color(252, 211, 27));
	creatureslabel->setTextSize(30);
	gui.add(creatureslabel);

	auto creaturesBox = ChatBox::create();
	creaturesBox->setSize(288, 150);
	creaturesBox->setTextSize(20);
	creaturesBox->setPosition(730, 150);
	gui.add(creaturesBox);

	auto peoplelabel = Label::create("People");
	peoplelabel->setPosition(730, 315);
	peoplelabel->setHorizontalAlignment(Label::HorizontalAlignment::Right);
	peoplelabel->setTextColor(sf::Color(252, 211, 27));
	peoplelabel->setTextSize(30);
	gui.add(peoplelabel);

	auto peopleBox = ChatBox::create();
	peopleBox->setSize(288, 400);
	peopleBox->setTextSize(20);
	peopleBox->setPosition(730, 350);
	gui.add(peopleBox);

	auto worldBox = ChatBox::create();
	worldBox->setSize(220, 80);
	worldBox->setTextSize(20);
	worldBox->setPosition(730, 5);
	gui.add(worldBox);

	auto backbtn = Button::create();
	backbtn->setPosition(970, 60);
	backbtn->setSize(50, 50);
	backbtn->setText("Back");
	gui.add(backbtn);

	auto savebtn = Button::create();
	savebtn->setPosition(970, 5);
	savebtn->setSize(50, 50);
	savebtn->setText("Save");
	gui.add(savebtn);

	//обновить информацию о мире и агентах в виджетах
	//информация о животных и людях
	for (int i = 0; i < animals.size(); i++)
	{
		creaturesBox->addLine(animals[i].getAnimalData(), sf::Color(252, 211, 27));
	}

	for (int i = 0; i < humans.size(); i++)
	{
		peopleBox->addLine(humans[i].getHumanData(), sf::Color(252, 211, 27));
	}
	//информация о мире
	worldBox->addLine(wrld.getDateData(), sf::Color(252, 211, 27));
	worldBox->addLine(wrld.getTimeData(), sf::Color(252, 211, 27));
	worldBox->addLine(wrld.getWeatherData(), sf::Color(252, 211, 27));

	gui.draw();
}

void UI::getData(EditBox::Ptr &ebCount, ComboBox::Ptr &cbSeason, ComboBox::Ptr &cbWeather, EditBox::Ptr &ebHours, EditBox::Ptr &ebMinutes, RenderWindow &window)
{
	//получает данные из стартового окна
	//получить данные из едитбоксов
	String countStr, hoursStr, minutesStr; //поскольку из виджетов можно вытащить только строку
	countStr = ebCount->getText();
	hoursStr = ebHours->getText();
	minutesStr = ebMinutes->getText();
	//вытащить инты из строк
	std::string cstr = countStr.toAnsiString();
	std::string hstr = hoursStr.toAnsiString();
	std::string mstr = minutesStr.toAnsiString();
	std::istringstream issc(cstr);
	std::istringstream issh(hstr);
	std::istringstream issm(mstr);
	issc >> UI::count;
	issh >> UI::hours;
	issm >> UI::minutes;

	//получить данные из комбобоксов
	season = cbSeason->getSelectedItemIndex();
	weather = cbWeather->getSelectedItemIndex();

	//закрыть окно - как?
	window.close();

}

void UI::makeRandom(RenderWindow &window)
{
	//задаёт случайные стартовые параметры
	season = rand() % 4;
	weather = rand() % 5;
	count = rand() % 190 + 10;
	hours = rand() % 24;
	minutes = rand() % 60;
	//закрыть окно
	window.close();

}