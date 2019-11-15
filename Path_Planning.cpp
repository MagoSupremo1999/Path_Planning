/* ==============================================================================================
   = Código desenvolvido para um robô pensar no melhor caminho para uma determinada localização =
   = 13/11/2019                                                                                 =
   = Desenvolvido por Vinícius Alves e Lucas Figueiras                                          =
   ============================================================================================== */
   
#include <SFML/Window.hpp>                                                              //Declaração das bibliotecas
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>
#include <math.h>

int main(){
    int Block_x[6], Block_y[6], start_x, start_y, end_x, end_y;                         //Declaração das variáveis de coordenadas
    float alpha, beta, limite, d[6];                                                    //Declaração das variáveis das retas
    float sen, cos;                                                                     //Seno e cosseno
    int Window_Sizex = 900;                                                             //Definição da dimensão horizontal da tela
    int Window_Sizey = 604;                                                             //Definição da dimensão vertical da tela

    sf::RenderWindow window(sf::VideoMode(Window_Sizex, Window_Sizey), "My window");    //Configura a janela

    sf::RectangleShape rectangle(sf::Vector2f(Window_Sizex, Window_Sizey));             //Gera o fundo verde (campo)
    rectangle.setFillColor(sf::Color::Green);

    alpha = (end_y - start_y)/(end_x - start_x);                    //Definição do coeficiente angular
    beta = 8*(start_y - start_x * alpha);                           //Definição do coeficiente linear
    sen = (end_y - start_y)/sqrt((end_y - start_y)*(end_y - start_y) + (end_x - start_x)*(end_x - start_x));    //Definição do seno   
    cos = (end_x - start_x)/sqrt((end_y - start_y)*(end_y - start_y) + (end_x - start_x)*(end_x - start_x));    //Definição do cosseno
    limite = 18/sen;                                                //Definição do limite mínimo de distância aos obstáculos

    srand(time(NULL));                                              //Configura a função rand()

    for (int x = 0; x < 6; x++) {                                   //Configura a posição central dos obstáculos no eixo x
        Block_x[x] = rand()%(Window_Sizex/8+1);
    }

    for (int x = 0; x < 6; x++) {                                   //Configura a posição central dos obstáculos no eixo y
        Block_y[x] = rand()%(Window_Sizey/8+1);
    }

    while (window.isOpen()){                                        //Abre a janela
        window.clear();                                             //Limpa o conteúdo da janela
        window.draw(rectangle);                                     //Desenha 'rectangle' ocultamente
        
        for (int cont = 0; cont < 6; cont++)                        //Determina os locais com obstáculos
            for (int x = -1; x < 2; x++) 
                for (int y = -1; y < 2; y++) {
                sf::RectangleShape block(sf::Vector2f(4, 4));
                block.setFillColor(sf::Color::Black);
                block.setPosition((Block_x[cont]+x)*8, (Block_y[cont]+y)*8);
                window.draw(block);                                 //Desenha 'block' ocultamente
        }

        for (int x = -1; x < 2; x++)                                //Determina o início da jornada
            for (int y = -1; y < 2; y++) {
                sf::RectangleShape start(sf::Vector2f(4, 4));
                start.setFillColor(sf::Color::Blue);
                start.setPosition((start_x+x)*8, (start_y+y)*8);
                window.draw(start);                                 //Desenha 'start' ocultamente
        }

        for (int x = -1; x < 2; x++)                                //Determina o fim da jornada
            for (int y = -1; y < 2; y++) {
                sf::RectangleShape end(sf::Vector2f(4, 4));
                end.setFillColor(sf::Color::White);
                end.setPosition((end_x+x)*8, (end_y+y)*8);
                window.draw(end);                                   //Desenha 'end' ocultamente
        }

        for (int x = 0;; x++) {
            alpha = (end_y - start_y)/(end_x - start_x);            //Definição do coeficiente angular
            beta = 8*(start_y - start_x * alpha);                   //Definição do coeficiente linear
            sen = (end_y - start_y)/sqrt((end_y - start_y)*(end_y - start_y) + (end_x - start_x)*(end_x - start_x));    //Definição do seno   
            cos = (end_x - start_x)/sqrt((end_y - start_y)*(end_y - start_y) + (end_x - start_x)*(end_x - start_x));    //Definição do cosseno
            limite = 18/sen;                                        //Definição do limite mínimo de distância aos obstáculos
            for (int i = 0; i < 6; i++) {
                if (d[i] < limite) {                                //Confere se existe algum obstáculo próximo ao caminho otimista e estabelece um desvio do caminnho
                    sf::Vertex desvio[] = {sf::Vertex(sf::Vector2f(8*start_x, 8*start_y)), sf::Vertex(sf::Vector2f(8*Block_x[i] + limite * cos, 8*Block_y[i] + limite * sen))};
                    window.draw(desvio, 10, sf::Lines);             //Desenha o desvio do caminho ocultamente
                    start_x = 8*Block_x[i] + limite * cos;
                    start_y = 8*Block_y[i] + limite * sen;
                    break;
                } else {                                            //Estabelece o caminho otimista
                    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(8*start_x, 8*start_y)), sf::Vertex(sf::Vector2f(8*end_x, 8*end_y))};
                    window.draw(line, 10, sf::Lines);               //Desenha o caminho otimista ocultamente
                }
            } 
        }

        window.display();                                           //Desoculta os desenhos na janela

        sf::Event event;
        while (window.pollEvent(event)){                            //Rotina que faz a janela fechar se o 'X' for clicado
            if (event.type == sf::Event::Closed){  
                window.close();
            }
        }
    }
    return 0;
}
