#include <iostream>
#include <cmath>
int main()
{
    double speed = 10.0; // this will be the projectile speed
    double rotationAngleInDegrees;
    double xSpeed;
    double ySpeed;
    double rotationAngleInRadians;
    double testingDegreesSet[25] = {0, 1, 5, 89, 90, 91, 135, 179, 180, 181, 359, 360, 361, -1, -89, -90, -91, -135, -179, -180, -181, -359, -360, -361};  
    double evenTestingDegreesSet[24] = {0, 2, 90, 92, 136, 178, 180, 358};
    for (int i = 0; i <= 360; i = i + 6)
    {
        rotationAngleInDegrees = i;
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