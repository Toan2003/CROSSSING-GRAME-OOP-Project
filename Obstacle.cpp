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
	this->order = order; // hang thu may
	this->direction = direction;
	int temp, len, tempSpace =0;
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


	int numberObstacle = (borderGRx - borderGLx - 1) / (len + tempSpace) +2;

	for (int i = 0; i < numberObstacle; i++) {
		if (temp == 0) {
			if (direction == leftToRight) {
				Car* p = new Car(i*(len + tempSpace) + borderGLx +1, (borderGDy-4) - ((order-1)*heightOflane));
				p->space = len + tempSpace;
				this->point.push_back(p);
			}
			else {
				Truck* p = new Truck(borderGRx -1 - i * (len + tempSpace), (borderGDy - 4) - ((order-1) * heightOflane));
				p->space = len + tempSpace;
				this->point.push_back(p);
			}
		}
		else if (temp == 1) {
			if (direction == leftToRight) {
				Cat* p = new Cat(i * (len + tempSpace) + borderGLx + 1, (borderGDy - 4) - ((order - 1) * heightOflane));
				p->space = len + tempSpace;
				this->point.push_back(p);
			}
			else {
				Bus* p = new Bus(borderGRx -1 - i * (len + tempSpace), (borderGDy - 4) - ((order - 1) * heightOflane));
				p->space = len + tempSpace;
				this->point.push_back(p);
			}
		}
	}
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

	//	if (direction == rightToLeft) {
	//		if (point[i]->getX() <= borderGLx) {
	//			//point[i]->setX(point[1]->getX());
	//			//point[1]->setX(point[i]->getX() + point[i]->space);
	//		}
	//	}
	//	else {
	//		if (point[i]->getX() >= borderGRx) {
	//			//point[i]->setX(point[1]->getX());
	//			//point[1]->setX(point[i]->getX() - point[i]->space);
	//		}
	//	}

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
	for (int i = 0; i < point.size(); i++) {
		point[i]->draw();
	}
	gotoXY(0, 0);
}

lane::~lane() {
	Vehicle* temp;
	while (!point.empty()) {
		temp = point.back();
		point.pop_back();
		delete[] temp;
	}
}

