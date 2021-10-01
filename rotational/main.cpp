#include "SFML/Graphics.hpp"
#include<cmath>
#include<cstdio>
using namespace sf;
using namespace std;

float radians(float angle)
{
    return M_PI*angle/180;
}

double degrees(double angle)
{
    return angle * 180/M_PI;
}

float magnitude(Vector3<float> v)
{
    return (float)sqrt(pow(v.x, 2)+ pow(v.y, 2)+ pow(v.z, 2));
}

Vector3<float> cross_product(const Vector3<float>& v1, const Vector3<float>& v2)
{
    Vector3<float> result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}



int main()
{
    // Plane related
    Vector2<float> origin = {500, 500};
    Vector3<float> radius = {100, 0, 0};

    RenderWindow window(VideoMode(1000, 1000), "Ball", Style::Resize);
    window.setFramerateLimit(60);

    // Ball Related
    float mag_radius = magnitude(radius);
    float x, y;
    CircleShape ball(30);
    bool motion = false; // 0 for circular, 1 for linear
    CircleShape center(10);
    Vector3<float> velocity;

    center.setPosition(origin);

    // Line Related
    RectangleShape line((Vector2<float>){mag_radius, 5});
    line.setPosition(origin.x+5, origin.y+5);



    Event event{};

    // Angle related
    Vector3<float> angular_vel = {0, 0, M_PI/2};
    const auto deg = (float)degrees(angular_vel.z);
    float theta=0;

    // Clock related
    Clock clock;
    Time et;


    while(window.isOpen()) {
        et = clock.restart();
        window.clear();
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyReleased:
                {
                    velocity = cross_product(angular_vel, radius);
                    motion = true;
                }
                default:
                    break;
            }
        }

        if(not motion) {
            float radian = -radians(theta);
            x = origin.x + (mag_radius * cos(radian));
            y = origin.y + (mag_radius * sin(radian));

            theta += (deg * et.asSeconds());
            ball.setPosition(x - 15, y - 15);
            line.rotate(-deg * et.asSeconds());
            radius.y = (y - origin.y); // change in Y co-ordinate with respect to origin
            radius.x = radius.y / tan(radian); // same thing but X co-ordinate
        }
        else
        {
            ball.move(-velocity.x*et.asSeconds(), -velocity.y*et.asSeconds());
        }
        window.draw(ball);
        window.draw(center);
        window.draw(line);
        window.display();
    }
    return 0;
}
