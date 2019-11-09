#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>

int main(){
    int Block_x[6], Block_y[6], start_x, start_y, end_x, end_y;                         //Declaração das variáveis iniciais
    int Window_Sizex = 900;
    int Window_Sizey = 604;

    sf::RenderWindow window(sf::VideoMode(Window_Sizex, Window_Sizey), "My window");    //Configura a janela

    sf::RectangleShape rectangle(sf::Vector2f(Window_Sizex, Window_Sizey));             //Gera o fundo verde (campo)
    rectangle.setFillColor(sf::Color::Green);

    start_x = rand()%(Window_Sizex/8);                          //Determinação das variáveis iniciais
    start_y = rand()%(Window_Sizey/8);
    end_x = rand()%(Window_Sizex/8);
    end_y = rand()%(Window_Sizey/8);

    srand(time(NULL));                                          //Configura a função rand()

    for (int x = 0; x < 6; x++) {                               //Determina a posição central dos obstáculos no eixo x
        Block_x[x] = rand()%(Window_Sizex/8+1);
    }

    for (int x = 0; x < 6; x++) {                               //Determina a posição central dos obstáculos no eixo y
        Block_y[x] = rand()%(Window_Sizey/8+1);
    }

    while (window.isOpen()){                                    //Abre a janela
        window.clear();
        window.draw(rectangle);                                 //Desenha 'rectangle' ocultamente
        for (int x = 0; x < Window_Sizex; x += 8)               //Determina os locais existentes
            for (int y = 0; y < Window_Sizey; y += 8) {
                sf::RectangleShape local(sf::Vector2f(4, 4));
                local.setFillColor(sf::Color::Red);
                local.setPosition(x,y);
                window.draw(local);                             //Desenha 'local' ocultamente        
        }
        for (int cont = 0; cont < 6; cont++)                    //Determina os locais com obstáculos
            for (int x = -1; x < 2; x++) 
                for (int y = -1; y < 2; y++) {
                sf::RectangleShape block(sf::Vector2f(4, 4));
                block.setFillColor(sf::Color::Black);
                block.setPosition((Block_x[cont]+x)*8, (Block_y[cont]+y)*8);
                window.draw(block);                             //Desenha 'block' ocultamente
        }

        for (int x = -1; x < 2; x++)                            //Determina o início da jornada
            for (int y = -1; y < 2; y++) {
                sf::RectangleShape start(sf::Vector2f(4, 4));
                start.setFillColor(sf::Color::Blue);
                start.setPosition((start_x+x)*8, (start_y+y)*8);
                window.draw(start);                             //Desenha 'start' ocultamente
        }

        for (int x = -1; x < 2; x++)                            //Determina o fim da jornada
            for (int y = -1; y < 2; y++) {
                sf::RectangleShape end(sf::Vector2f(4, 4));
                end.setFillColor(sf::Color::White);
                end.setPosition((end_x+x)*8, (end_y+y)*8);
                window.draw(end);                               //Desenha 'end' ocultamente
        }

        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(8*start_x, 8*start_y)), sf::Vertex(sf::Vector2f(8*end_x, 8*end_y))};
        window.draw(line, 10, sf::Lines);

        window.display();                                       //Desoculta as os desenhos na janela

        sf::Event event;
        while (window.pollEvent(event)){                        //Rotina que faz a janela fechar se o 'X' for clicado
            if (event.type == sf::Event::Closed){  
                window.close();
            }
        }
    }
    return 0;
}
