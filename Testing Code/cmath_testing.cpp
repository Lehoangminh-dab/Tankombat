#include <iostream>
#include <cmath>
int main()
{
    double speed = 10.0;
    double rotationAngleInDegrees;
    double xSpeed;
    double ySpeed;
    double rotationAngleInRadians;
    double testingDegreesSet[24] = {0, 1, 89, 90, 91, 135, 179, 180, 181, 359, 360, 361, -1, -89, -90, -91, -135, -179, -180, -181, -359, -360, -361};  
    
    for (int i = 0; i < 24; i++)
    {
        rotationAngleInDegrees = testingDegreesSet[i];
        rotationAngleInRadians = rotationAngleInDegrees * M_PI / 180.0;
        xSpeed = speed * cos(rotationAngleInRadians);
        ySpeed = speed * sin(rotationAngleInRadians);
        std::cout << "Current Testing Degree Value: " << rotationAngleInDegrees << std::endl;
        std::cout << "Radian Value: " << rotationAngleInRadians << std::endl;
        std::cout << "X Speed: " << xSpeed << std::endl;
        std::cout << "Y Speed: " << ySpeed << std::endl;
        std::cout << std::endl;
    }
}