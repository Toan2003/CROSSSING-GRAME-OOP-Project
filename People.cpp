#include "People.h"

CPEOPLE::CPEOPLE()
{
    mX = 50;
    mY = borderGDy - 3;
    mState = true;
}

void CPEOPLE::Up()
{
    if (mY - 2 == borderGUy)
    {
        return;
    }
    mY -= 5;
};

void CPEOPLE::Left()
{
    if (borderGLx + 1 == mX)
    {
        return;
    }
    mX -= 1;
}

void CPEOPLE::Right()
{
    if (borderGRx - 3 == mX)
    {
        return;
    }
    mX += 1;
}

void CPEOPLE::Down()
{
    if (borderGDy - 3 == mY)
    {
        return;
    }
    mY += 5;
}

void CPEOPLE::move()
{
    switch (c)
    {
    case KEY_UP /* H */:
        Up();
        break;
    case KEY_DOWN /* K */:
        Down();
        break;
    case KEY_LEFT /* M */:
        Left();
        break;
    case KEY_RIGHT: /* P */
        Right();
        break;
    }
}

void CPEOPLE::draw()
{
    gotoXY(mX + 1, mY);
    cout << "o";

    gotoXY(mX, mY + 1);

    cout << "/";

    gotoXY(mX + 1, mY + 1);
    cout << "|";

    gotoXY(mX + 2, mY + 1);
    cout << (char)92;

    gotoXY(mX, mY + 2);
    cout << "/";

    gotoXY(mX + 2, mY + 2);
    cout << (char)92;

    gotoXY(0, 0);
}

void CPEOPLE::clearPeople()
{

    gotoXY(mX + 1, mY);
    cout << " ";

    gotoXY(mX, mY + 1);
    cout << " ";

    gotoXY(mX + 1, mY + 1);
    cout << " ";

    gotoXY(mX + 2, mY + 1);
    cout << " ";

    gotoXY(mX, mY + 2);
    cout << " ";

    gotoXY(mX + 2, mY + 2);
    cout << " ";
}

bool CPEOPLE::isDead()
{
    if (mState == false)
        return true;
    return false;
}

bool CPEOPLE::isFinish()
{
    if (mState == true && mY - 2 == borderGUy)
    {
        return true;
    }
    return false;
}

bool CPEOPLE::isImpact(const Vehicle*& object, int type)
{
    int ax, ay;
    int px, py;
    ax = object->getX();
    ay = object->getY();
    px = mX;
    py = mY;
    if (type == 1) // car
    {              // dau
        if (((px + 1) >= (ax + 2) && (px + 1) <= (ax + 8) && py == ay) || ((px + 1) >= (ax + 1) && (px + 1) <= (ax + 12) && py == (ay + 1)) || ((px + 1) >= ax && (px + 1) <= (ax + 13) && py == (ay + 2)) || ((px + 1) >= ax && (px + 1) <= (ax + 13) && py == (ay + 3)))
        {
            mState = false;
            return true;
        }
        // tay trai
        if (((px) >= (ax + 2) && px <= (ax + 8) && (py + 1) == ay) || ((px) >= (ax + 1) && (px) <= (ax + 12) && (py + 1) == (ay + 1)) || ((px) >= ax && (px) <= (ax + 13) && (py + 1) == (ay + 2)) || (px) >= ax && (px) <= (ax + 13) && (py + 1) == (ay + 3))
        {
            mState = false;
            return true;
        }
        // tay phai
        if (((px + 2) >= (ax + 2) && (px + 2) <= (ax + 8) && (py + 1) == ay) || ((px + 2) >= (ax + 1) && (px + 2) <= (ax + 12) && (py + 1) == (ay + 1)) || ((px + 2) >= ax && (px + 2) <= (ax + 13) && (py + 1) == (ay + 2)) || (px + 2) >= ax && (px + 2) <= (ax + 13) && (py + 1) == (ay + 3))
        {
            mState = false;
            return true;
        }
        // chan trai
        if (((px) >= (ax + 2) && px <= (ax + 8) && (py + 2) == ay) || ((px) >= (ax + 1) && (px) <= (ax + 12) && (py + 2) == (ay + 1)) || ((px) >= ax && (px) <= (ax + 13) && (py + 2) == (ay + 2)) || (px) >= ax && (px) <= (ax + 13) && (py + 2) == (ay + 3))
        {
            mState = false;
            return true;
        }
        if (((px + 2) >= (ax + 2) && (px + 2) <= (ax + 8) && (py + 2) == ay) || ((px + 2) >= ax && (px + 2) <= (ax + 12) && (py + 2) == (ay + 1)) || ((px + 2) >= ax && (px + 2) <= (ax + 13) && (py + 2) == (ay + 2)) || (px + 2) >= ax && (px + 2) <= (ax + 13) && (py + 2) == (ay + 3))
        {
            mState = false;
            return true;
        }
    }
    else if (type == 2) // truc
    {
        if (((px + 1) >= (ax - 12) && (px + 1) <= (ax - 8 + 1) && py == ay) || ((px + 1) >= (ax - 17) && (px + 1) <= (ax + 1) && py == (ay + 1)) || ((px + 1) >= (ax - 18) && (px + 1) <= (ax + 1) && py == (ay + 2)) || ((px + 1) >= (ax - 18) && (px + 1) <= (ax - 1 + 1) && py == (ay + 3)))
        {
            mState = false;
            return true;
        }
        // tay trai
        if (((px) >= (ax - 12) && px <= (ax - 8 + 1) && (py + 1) == ay) || ((px) >= (ax - 17) && (px) <= (ax + 1) && (py + 1) == (ay + 1)) || ((px) >= (ax - 18) && (px) <= (ax + 1) && (py + 1) == (ay + 2)) || (px) >= (ax - 18) && (px) <= (ax - 1 + 1) && (py + 1) == (ay + 3))
        {
            mState = false;
            return true;
        }
        // tay phai
        if (((px + 2) >= (ax - 12) && (px + 2) <= (ax - 8 + 1) && (py + 1) == ay) || ((px + 2) >= (ax - 17) && (px + 2) <= (ax + 1) && (py + 1) == (ay + 1)) || ((px + 2) >= (ax - 18) && (px + 2) <= (ax + 1) && (py + 1) == (ay + 2)) || (px + 2) >= (ax - 18) && (px + 2) <= (ax - 1 + 1) && (py + 1) == (ay + 3))
        {
            mState = false;
            return true;
        }
        // chan trai
        if (((px) >= (ax - 12) && px <= (ax - 8 + 1) && (py + 2) == ay) || ((px) >= (ax - 17) && (px) <= ((ax + 1) && (py + 2) == (ay + 1)) || ((px) >= (ax - 18) && (px) <= (ax + 1) && (py + 2) == (ay + 2)) || (px) >= (ax - 18) && (px) <= (ax - 1 + 1) && (py + 2) == (ay + 3)))
        {
            mState = false;
            return true;
        }
        if (((px + 2) >= (ax - 12) && (px + 2) <= (ax - 8 + 1) && (py + 2) == ay) || ((px + 2) >= (ax - 17) && (px + 2) <= (ax + 1) && (py + 2) == (ay + 1)) || ((px + 2) >= (ax - 18) && (px + 2) <= (ax + 1) && (py + 2) == (ay + 2)) || (px + 2) >= (ax - 18) && (px + 2) <= (ax - 1 + 1) && (py + 2) == (ay + 3))
        {
            mState = false;
            return true;
        }
    }
    else if (type == 3) // cat
    {
        if (((px + 1) >= (ax) && (px + 1) <= (ax + 1) && py == ay) || ((px + 1) >= (ax + 1) && (px + 1) <= (ax + 8) && py == (ay + 1)) || ((px + 1) >= (ax + 1) && (px + 1) <= (ax + 7) && py == (ay + 2)) || ((px + 1) >= (ax + 2) && (px + 1) <= (ax + 7) && py == (ay + 3)) || ((px + 1) >= (ax + 5) && (px + 1) <= (ax + 7) && py == ay))
        {
            mState = false;
            return true;
        }
        // tay trai
        if (((px) >= (ax) && px <= (ax + 1) && (py + 1) == ay) || ((px) >= (ax + 1) && (px) <= (ax + 8) && (py + 1) == (ay + 1)) || ((px) >= (ax + 1) && (px) <= (ax + 7) && (py + 1) == (ay + 2)) || (px) >= (ax + 1) && (px) <= (ax + 7) && (py + 1) == (ay + 3) || ((px) >= (ax + 5) && px <= (ax + 7) && (py + 1) == ay))
        {
            mState = false;
            return true;
        }
        // tay phai
        if (((px + 2) >= (ax) && (px + 2) <= (ax + 1) && (py + 1) == ay) || ((px + 2) >= (ax + 1) && (px + 2) <= (ax + 8) && (py + 1) == (ay + 1)) || ((px + 2) >= (ax + 1) && (px + 2) <= (ax + 7) && (py + 1) == (ay + 2)) || (px + 2) >= (ax + 1) && (px + 2) <= (ax + 7) && (py + 1) == (ay + 3) || ((px + 2) >= (ax + 5) && (px + 2) <= (ax + 7) && (py + 1) == ay))
        {
            mState = false;
            return true;
        }
        // chan trai
        if (((px) >= (ax) && px <= (ax + 1) && (py + 2) == ay) || ((px) >= (ax + 1) && (px) <= (ax + 8) && (py + 2) == (ay + 1)) || ((px) >= (ax + 1) && (px) <= (ax + 7) && (py + 2) == (ay + 2)) || (px) >= (ax + 1) && (px) <= (ax + 7) && (py + 2) == (ay + 3) || ((px) >= (ax + 5) && px <= (ax + 7) && (py + 2) == ay))
        {
            mState = false;
            return true;
        }
        if (((px + 2) >= (ax) && (px + 2) <= (ax + 1) && (py + 2) == ay) || ((px + 2) >= ax && (px + 2) <= (ax + 8) && (py + 2) == (ay + 1)) || ((px + 2) >= (ax + 1) && (px + 2) <= (ax + 7) && (py + 2) == (ay + 2)) || (px + 2) >= (ax + 1) && (px + 2) <= (ax + 7) && (py + 2) == (ay + 3) || ((px + 2) >= (ax + 5) && (px + 2) <= (ax + 7) && (py + 2) == ay))
        {
            mState = false;
            return true;
        }
    }
    else if (type == 4) // bus
    {
        if (((px + 1) >= (ax - 18) && (px + 1) <= (ax - 5) && py == ay) || ((px + 1) >= (ax - 20) && (px + 1) <= (ax) && py == (ay + 1)) || ((px + 1) >= (ax - 21) && (px + 1) <= (ax) && py == (ay + 2)) || ((px + 1) >= (ax - 21) && (px + 1) <= (ax - 1) && py == (ay + 3)))
        {
            mState = false;
            return true;
        }
        // tay trai
        if (((px) >= (ax - 18) && px <= (ax - 5) && (py + 1) == ay) || ((px) >= (ax - 20) && (px) <= (ax) && (py + 1) == (ay + 1)) || ((px) >= (ax - 21) && (px) <= (ax) && (py + 1) == (ay + 2)) || (px) >= (ax - 21) && (px) <= (ax - 1) && (py + 1) == (ay + 3))
        {
            mState = false;
            return true;
        }
        // tay phai
        if (((px + 2) >= (ax - 18) && (px + 2) <= (ax - 5) && (py + 1) == ay) || ((px + 2) >= (ax - 20) && (px + 2) <= (ax) && (py + 1) == (ay + 1)) || ((px + 2) >= (ax - 21) && (px + 2) <= (ax) && (py + 1) == (ay + 2)) || (px + 2) >= (ax - 21) && (px + 2) <= (ax - 1) && (py + 1) == (ay + 3))
        {
            mState = false;
            return true;
        }
        // chan trai
        if (((px) >= (ax - 18) && px <= (ax - 5) && (py + 2) == ay) || ((px) >= (ax - 20) && (px) <= ((ax) && (py + 2) == (ay + 1)) || ((px) >= (ax - 21) && (px) <= (ax) && (py + 2) == (ay + 2)) || (px) >= (ax - 21) && (px) <= (ax - 1) && (py + 2) == (ay + 3)))
        {
            mState = false;
            return true;
        }
        if (((px + 2) >= (ax - 18) && (px + 2) <= (ax - 5) && (py + 2) == ay) || ((px + 2) >= (ax - 20) && (px + 2) <= (ax) && (py + 2) == (ay + 1)) || ((px + 2) >= (ax - 21) && (px + 2) <= (ax) && (py + 2) == (ay + 2)) || (px + 2) >= (ax - 21) && (px + 2) <= (ax - 1) && (py + 2) == (ay + 3))
        {
            mState = false;
            return true;
        }
    }
    return false;
}

int CPEOPLE::getMY()
{
    return mY;
}

int CPEOPLE::getMX()
{
    return mX;
}

void foo(CPEOPLE* p)
{
    char tempt ='\0';
    p->nhanbanphim(tempt);
}

void CPEOPLE::nhanbanphim(char tempt)
{
    while (true)
    {
        tempt = _getch();
        c = tempt;
    }

}

void CPEOPLE::update()
{
    clearPeople();
    move();
    draw();
}

void CPEOPLE::assignChar()
{
    c = '\0';
}




