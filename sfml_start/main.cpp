#include <SFML/Graphics.hpp>
#include <optional> // Needed for SFML 3 events
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>


std::string v2f_print(sf::Vector2f v){
    return "{" + std::to_string(v.x) + "," + std::to_string(v.y) + "}";
} 

struct Curve3p{ 
    sf::Vector2f a;
    sf::Vector2f b;
    sf::Vector2f c;

    Curve3p(sf::Vector2f a,sf::Vector2f b,sf::Vector2f c){
        this->a=a; this->b=b; this->c=c;
    }

    sf::Vector2f lerp(sf::Vector2f i,sf::Vector2f j, float t){ // not great practice putting this inside the curve3p 
        return {i.x + (j.x - i.x)* t, i.y + (j.y - i.y)*t};
    }

    sf::Vector2f get_point(float t, int noise = 0){
        sf::Vector2f i = lerp(this->a, this->b,t);
        sf::Vector2f j = lerp(this->b, this->c,t);
        sf::Vector2f k = lerp(i,j,t);
        float rx = (static_cast <float>(std::rand() % 1000)/1000.0 -0.5) * noise * (0.5- std::abs(0.5 - t));
        float ry = (static_cast <float>(std::rand() % 1000)/1000.0 -0.5) * noise * (0.5- std::abs(0.5 - t));
        return {k.x + rx, k.y + ry};
    }

    sf::VertexArray get_array(int divs = 1000, int noise = 0){
        sf::VertexArray arr = sf::VertexArray();
        for (int i=0; i<= divs;i++){
            arr.append( 
                sf::Vertex{get_point((i*1.0)/(divs*1.0), noise)}
            );
        }
        return arr;
    } 

    Curve3p create_next(){
        // first point will match the last from this point 
        sf::Vector2f a_new = this->c;
        sf::Vector2f b_new;
        // the middle point will be in line with the other middle point
        // y = mx + o (o for offset instead of c)
        float dx = this->c.x - this->b.x;
        float dy = this->c.y - this->b.y;
        if (dx != 0.0){
            float m = dy/dx;
            float o = this->b.y - this->b.x * m;
            b_new = sf::Vector2f(this->c.x +dx, (this->c.x + dx)*m +o);

        } else { // dx == 0 , so we calc as if it is inf 
            b_new = sf::Vector2f(this->c.x, this->c.y + dy);
        }

        float cx = static_cast <float>(std::rand() % 1000);
        float cy = static_cast <float>(std::rand() % 700);
        sf::Vector2f c_new = sf::Vector2f(cx,cy);
        std::cout << v2f_print(a_new)  << v2f_print(b_new) << v2f_print(c_new) << std::endl;
        return Curve3p(a_new, b_new, c_new);
    }

    Curve3p create_branch(){
        sf::Vector2f a_new = get_point(0.5);
        sf::Vector2f b_new;
        sf::Vector2f c_new;

        // point b will be along the line 
        
    }
};

int main()
{
    //global variables
    std::srand(time(0) +500);
    sf::Vector2u winDims = {1500, 1000};

    // shapes and bits
    sf::CircleShape circle = sf::CircleShape(5,30);
    circle.setPosition({500.0,900});

    std::vector<Curve3p> curves = {Curve3p({500.0,600.0},{500.0,300.0},{800.0,300.0})};
    curves.push_back(curves[0].create_next());

    // 1. VideoMode now takes a sf::Vector2u, so we wrap the numbers in {}
    sf::RenderWindow window(
        sf::VideoMode(winDims),
        "Hello World");

    while (window.isOpen()) {

        // 2. pollEvent no longer takes a reference. It returns a std::optional<sf::Event>
        while (const std::optional event = window.pollEvent()) {

            // 3. Event types are now checked using the ->is<Type>() method
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }


        window.clear();

        window.draw(circle);

        for (int i=0; i< curves.size();i++){
        window.draw(curves[i].get_array(100000, 100));
        }
        window.display();
    }
    return 0;
}




// we have three points ✅

// we step along the curve 
    // we lerp between the points 

// we lerp between two points and the other 2 points and then lerp between them 

// repeat and save to an array 

//draw to screen?

//profit