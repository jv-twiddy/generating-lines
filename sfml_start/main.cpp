#include <SFML/Graphics.hpp>
#include <optional> // Needed for SFML 3 events
#include <vector>
#include <cstdlib>


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

    sf::Vector2f get_point(float t){
        sf::Vector2f i = lerp(this->a, this->b,t);
        sf::Vector2f j = lerp(this->b, this->c,t);
        return lerp(i,j,t);
    }

    sf::VertexArray get_array(int divs = 1000){
        sf::VertexArray arr = sf::VertexArray();
        for (int i=0; i<= divs;i++){
            arr.append( 
                sf::Vertex{get_point((i*1.0)/(divs*1.0))}
            );
        }
        return arr;
    } 
    
};

int main()
{
    //global variables
    sf::Vector2u winDims = {1500, 1000};

    // shapes and bits
    sf::CircleShape circle = sf::CircleShape(5,30);
    circle.setPosition({static_cast<float>(winDims.x/2u),static_cast<float>(winDims.y/2u)});

    Curve3p first = Curve3p({500.0,900.0},{500.0,600.0},{800.0,600.0});

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

        window.draw(first.get_array());
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