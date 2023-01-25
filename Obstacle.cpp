#include "Obstacle.h"


Vehicle::Vehicle(int x, int y) {
	this->x = x;
	this->y = y;
	this->direction = rightToLeft;
}

void Vehicle::setDirection(int direction) {
	this->direction = direction;
}

Car::Car(int x, int y) : Vehicle(x,y) {
	Vehicle::type = 1;
	Vehicle::length = this->length;
	this->setDirection(direction);
}

Cat::Cat(int x, int y) : Vehicle(x, y) {
	Vehicle::type = 3;
	Vehicle::length = this->length;
	this->setDirection(direction);
}

Truck::Truck(int x, int y) : Vehicle(x, y) {
	Vehicle::type = 2;
	Vehicle::length = this->length;
	this->setDirection(direction);
}

Bus::Bus(int x, int y) : Vehicle(x, y) {
	Vehicle::type = 4;
	Vehicle::length = this->length;
	this->setDirection(direction);
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
	short x1 = this->getX();
	short y = getY();
	if (x1 > borderGRx) return;
	for (int i = 0; i < height; i++) {
		gotoXY(x1, y + i);
		for (int j = 0; j < length; j++) {
			if ((x1 + j) <= borderGLx) {
				gotoXY(x1 + j + 1, y + i);
				continue;
			}
			if ((x1 + j) >= borderGRx) break;
			//gotoXY(this->getX() + j, this->getY()+i);
			cout << picture[i][j];
		}
		//if (i < height - 1) cout << endl;
		if (x1 - 1 <= borderGLx || x1 - 1 >= borderGRx) continue;
		gotoXY(x1 - 1, y + i);
		cout << " ";
	}
}

void Cat::draw() {
	short x1 = this->getX();
	short y = getY();
	if (this->getX() > borderGRx) return;
	for (int i = 0; i < height; i++) {
		gotoXY(x1, y + i);
		for (int j = 0; j < length; j++) {
			if ((x1 + j) <= borderGLx) {
				gotoXY(x1 + j + 1, y + i);
				continue;
			}
			if ((x1 + j) >= borderGRx) break;
			//gotoXY(this->getX() + j, this->getY()+i);
			cout << picture[i][j];
		}
		//if (i < height - 1) cout << endl;
		if (x1-1 <= borderGLx || x1-1 >= borderGRx) continue;
		gotoXY(x1 - 1, y + i);
		cout << " ";
	}
}

void Truck::draw() {
	short x1 = this->getX();
	short x2 = x1 - this->length - 1;
	short y = this->getY();
	if (x1 < borderGLx) return;
	for (int i = 0; i < height; i++) {
		gotoXY(x2, y + i);
		for (int j = 0; j < length; j++) {
			if ((x2 + j) <= borderGLx) {
				gotoXY(x2 + j + 1, y + i);
				continue;
			}
			if ((x2 + j) >= borderGRx) break;
			cout << picture[i][j];
		}
		if (x1 + 1 <= borderGLx || x1 + 1 >= borderGRx) continue;
		gotoXY(x1 + 1, y + i);
		cout << " ";
	}
}

void Bus::draw() {
	short x1 = this->getX();
	short x2 = x1 - this->length-1;
	short y = this->getY();
	if (x1 < borderGLx) return;
	for (int i = 0; i < height; i++) {
		gotoXY(x2,y + i);
		for (int j = 0; j < length; j++) {
			if ((x2 + j) <= borderGLx) {
				gotoXY(x2+j+1, y + i);
				continue;
			}
			if ((x2+j) >= borderGRx) break;
			//gotoXY(this->getX() - j, this->getY() + i);
			//cout << picture[i][length - j-1];
			cout << picture[i][j];
		}
		if (x1 + 1 <= borderGLx || x1 + 1 >= borderGRx) continue;
		gotoXY(x1 + 1, y + i);
		cout << " ";
	}
}

//-----------------------------------------------------------------lane class

lane::lane(int order, int direction, int level) {
	this->level = level;
	this->order = order; // hang thu may // tinh tu hang thu 0 cho con nguoi dung
	this->direction = direction;
	this->countTimeForRedLight = 0;
	int temp;
	int x;

	if (direction == leftToRight) {
		x = borderGLx + 1;
		while (x < borderGRx) {
			temp = rand() % 2;
			if (temp == 0) {
				Car* p = new Car(x, (borderGDy - 4) - (order * heightOflane));
				//p->space = len + tempSpace + randomSpace;
				this->point.push_back(p);
				x = x + p->length + 1;
			}
			else {
				Cat* p = new Cat(x, (borderGDy - 4) - (order * heightOflane));
				//p->space = len + tempSpace + randomSpace;
				this->point.push_back(p);
				x = x + p->length + 1;
			}
			x = x + 5 + (rand() % 70);
		}

	}
	//i * (len + tempSpace) + borderGLx + 1 + randomSpace
	else {
		x = borderGRx - 1;
		while (x > borderGLx) {
			temp = rand() % 2;
			if (temp == 0) {
				Truck* p = new Truck(x, (borderGDy - 4) - (order * heightOflane));
				//p->space = len + tempSpace;
				this->point.push_back(p);
				x = x - p->length - 1;
			}
			else {
				Bus* p = new Bus(x, (borderGDy - 4) - (order * heightOflane));
				//p->space = len + tempSpace + randomSpace;
				this->point.push_back(p);
				x = x - p->length - 1;
			}
			x = x - 5 - (rand() % 70);
		}
	}
	//borderGRx - 1 - i * (len + tempSpace) - randomSpace

	light.setY(this->point[0]->getY());
	light.setOrder(order);
}

void lane::updateLane() {
	if (countTimeForRedLight > time[level-1]) {
		int temp= rand() % 2;
		setTrafficLight(temp);
		drawLight();
		countTimeForRedLight = 0;
	}
	++countTimeForRedLight;
	if (light.isRedLight()) return;

	if (direction == rightToLeft) {
		if (point.back()->getX() <= borderGLx) {
			Vehicle* temp = point.back();
			point.pop_back();
			int x = borderGRx + 22;
			temp->setX(x);
			point.push_front(temp);
		} 
	}
	else {
		if (point.back()->getX() >= borderGRx) {
			Vehicle* temp = point.back();
			point.pop_back();
			int x = borderGLx - 22;
			temp->setX(x);
			point.push_front(temp);
		}
	}
	for (int i = 0; i < point.size(); i++) {
		point[i]->move();
	}
	gotoXY(0, 0);
}

bool lane::isRedOn() {
	return light.isRedLight();
}

void lane::drawVehicle() {
	for (int i = 0; i < point.size(); i++) {
		
		point[i]->draw();
	}
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

Vehicle* lane::returnEachVehicle(const int& index) {
	if (index >= point.size() || index < 0) return NULL;
	return point[index];
}

//-------------------------------------------------------------------traffic class
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


