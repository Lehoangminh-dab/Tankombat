#include <iostream>
struct HitBox
{
    double topLeftX;
    double topLeftY;
    double bottomLeftX;
    double bottomLeftY;
    double topRightX;
    double topRightY;
    double bottomRightX;
    double bottomRightY;
    int rotationAngleComparedToScreen;
};

bool checkCollision(HitBox a, HitBox b);

int main()
{

}

bool checkCollision(HitBox a, HitBox b)
{
    // change b coordinates to match a's rotation
    
}


