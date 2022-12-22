#include "Obstacle.h"


Vehicle::Vehicle(int x, int y) {
	this->x = x;
	this->y = y;
	this->trafficLight = greenLight;
	this->direction = rightToLeft;
}

void Vehicle::setDirection(int direction) {
	this->direction = direction;
}

Car::Car(int x, int y) : Vehicle(x,y) {
	this->setDirection(direction);
}
Cat::Cat(int x, int y) : Vehicle(x, y) {
	this->setDirection(direction);
}
Truck::Truck(int x, int y) : Vehicle(x, y) {
	this->setDirection(direction);
}
Bus::Bus(int x, int y) : Vehicle(x, y) {
	this->setDirection(direction);
}

lane::lane(int level, int order, int direction = leftToRight) {
	this->level = level;
	this->order = order; // hang thu may // tinh tu hang thu 0 cho con nguoi dung
	this->direction = direction;
	int temp, len, tempSpace =0;
	int x;
	temp = rand() % 2;
	if (temp == 0) {
		if (direction == leftToRight) {
			Car temp1(0,0);
			len = temp1.picture[0].length();
		}
		else {
			Truck temp1(0, 0);
			len = temp1.picture[0].length();
		}
	}
	else {
		if (direction == leftToRight) {
			Cat temp1(0, 0);
			len = temp1.picture[0].length();
		}
		else {
			Bus temp1(0, 0);
			len = temp1.picture[0].length();
		}
	}
	if (level == 1) tempSpace = spacelevel1;
	if (level == 2) tempSpace = spacelevel2;
	if (level == 3) tempSpace = spacelevel3;
	if (level == 4) tempSpace = spacelevel4;
	if (level == 5) tempSpace = spacelevel5;

	if (direction == leftToRight) {
		x = borderGLx + 1;
		while (x < borderGRx) {

		}
	}
	else {
		x = borderGRx - 1;
	}

	int numberObstacle =( (borderGRx - borderGLx - 1) / (len + tempSpace) )+1;

	for (int i = 0; i < numberObstacle; i++) {
		int randomSpace = 5 + rand() % 30;
		if (temp == 0) {
			if (direction == leftToRight) {
				Car* p = new Car(i * (len + tempSpace) + borderGLx +1 + randomSpace, (borderGDy-4) - (order * heightOflane));
				p->space = len + tempSpace + randomSpace;
				this->point.push_back(p);
			}
			else {
				Truck* p = new Truck(borderGRx -1 - i * (len + tempSpace)-randomSpace, (borderGDy - 4) - (order * heightOflane));
				p->space =len+ tempSpace + randomSpace;
				this->point.push_back(p);
			}
		}
		else if (temp == 1) {
			if (direction == leftToRight) {
				Cat* p = new Cat(i * (len + tempSpace) + borderGLx + 1 + randomSpace, (borderGDy - 4) - (order * heightOflane));
				p->space = len + tempSpace + randomSpace;
				this->point.push_back(p);
			}
			else {
				Bus* p = new Bus(borderGRx -1 - i * (len + tempSpace) - randomSpace, (borderGDy - 4) - (order  * heightOflane));
				p->space =len + tempSpace + randomSpace;
				this->point.push_back(p);
			}
		}
	}
	light.setY(this->point[0]->getY());
	light.setOrder(order);
}

void Vehicle::move() {
	if (direction == rightToLeft) {
		x--;
	}
	else {
		x++;
	}
}

int Vehicle::getX() const {
	return x;
}

int Vehicle::getY() const {
	return y;
}

void Vehicle::setX(int x) {
	this->x = x;
}

void Vehicle::setY(int y) {
	this->y = y;
}

void Car::draw() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < picture[i].length(); j++) {
			if ((this->getX() + j) <= borderGLx || (this->getX() + j) >= borderGRx) continue;
			gotoXY(this->getX() + j, this->getY()+i);
			cout << picture[i][j];
		}
		if (i < height - 1) cout << endl;
		if (this->getX()-1 <= borderGLx || this->getX()-1 >= borderGRx) continue;
		gotoXY(this->getX()-1, this->getY() + i);
		cout << " ";
	}
}

void Cat::draw() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < picture[i].length(); j++) {
			if ((this->getX() + j) <= borderGLx || (this->getX() + j) >= borderGRx) continue;
			gotoXY(this->getX() + j, this->getY()+i);
			cout << picture[i][j];
		}
		if (i < height - 1) cout << endl;
		if (this->getX()-1 <= borderGLx || this->getX()-1 >= borderGRx) continue;
		gotoXY(this->getX()-1, this->getY() + i);
		cout << " ";
	}
}

void Truck::draw() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < picture[i].length(); j++) {
			if ((this->getX() - j) <= borderGLx || (this->getX() - j) >= borderGRx) continue;
			gotoXY(this->getX() - j, this->getY()+i);
			cout << picture[i][picture[i].length()-j-1];
		}
		if (i <height-1) cout << endl;
		if (this->getX() + 1 <= borderGLx || this->getX() + 1 >= borderGRx) continue;
		gotoXY(this->getX() + 1, this->getY() + i);
		cout << " ";
	}
}

void Bus::draw() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < picture[i].length(); j++) {
			if ((this->getX() - j) <= borderGLx || (this->getX() - j) >= borderGRx) continue;
			gotoXY(this->getX() - j, this->getY() + i);
			cout << picture[i][picture[i].length() - j-1];
		}
		if (i < height - 1) cout << endl;
		if (this->getX() + 1 <= borderGLx || this->getX() + 1 >= borderGRx) continue;
		gotoXY(this->getX() + 1, this->getY() + i);
		cout << " ";
	}
}

void lane::play() {
	for (int i = 0; i < point.size(); i++) {
		point[i]->draw();
	}
	if (light.isRedLight()) return;
	if (direction == rightToLeft) {
		if (point.back()->getX() <= borderGLx) {
			Vehicle* temp = point.back();
			point.pop_back();
			temp->setX(point.front()->getX() + temp->space);
			point.push_front(temp);
		} 
	}
	else {
		if (point.back()->getX() >= borderGRx) {
			Vehicle* temp = point.back();
			point.pop_back();
			temp->setX(point.front()->getX() - temp->space);
			point.push_front(temp);
		}
	}

	for (int i = 0; i < point.size(); i++) {
		point[i]->move();
	}
	gotoXY(0, 0);
}

void lane::drawLight() {
	light.draw();
}

lane::~lane() {
	Vehicle* temp;
	while (!point.empty()) {
		temp = point.back();
		point.pop_back();
		delete temp;
	}
}

void lane::setTrafficLight(bool isRed) {
	if (!light.isRedLight()) {
		if (isRed) {
			light.setRedOn();
		}
	}
	else {
		light.setGreenOn();
	}
}

void trafficLight::draw() {
	if (isRed) {
		setColor(4, 0); //nen do chu den
		if (order % 2 == 0) {
			gotoXY(borderGRx + 1, y);
		}
		else {
			gotoXY(borderGLx - 2, y);
		}
		cout << "  ";
		setColor(15, 0); //nen trang chu den
	}
	else {
		setColor(2, 0); //nen xanh chu den
		if (order % 2 == 0) {
			gotoXY(borderGRx + 1, y);
		}
		else {
			gotoXY(borderGLx - 2, y);
		}
		cout << "  ";
		setColor(15, 0);
	}
}

trafficLight::trafficLight() {
	isRed = false;
}

void trafficLight::setY(int y) {
	this->y = y;
}

void trafficLight::setOrder(int order) {
	this->order = order;
}


bool trafficLight::isRedLight() {
	return isRed;
}

void trafficLight::setRedOn() {
	isRed = true;
}

void trafficLight::setGreenOn() {
	isRed = false;
}