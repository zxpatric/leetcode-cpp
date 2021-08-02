//
// Created by ZhouP on 4/2/2019.
//

#ifndef CPPSANDBOX_TICTACTOE_H
#define CPPSANDBOX_TICTACTOE_H

#include <iostream>

enum TicTac
{
    EMPTY = 0,
    X,
    O
};


#define CheckFull if(isFull()){ std::cout << "Game over!" << std::endl; break; }

class TicTacToe
{
private:
    TicTac m_values [3][3];

    void init ()
    {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                m_values[i][j] = TicTac::EMPTY;
            }
        }
    }


public:
    TicTacToe ()
    {
        init();
    }

    void Print ()
    {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (m_values[i][j] == TicTac::EMPTY)
                    std::cout << '-';
                else if (m_values[i][j] == TicTac::X)
                    std::cout << 'X';
                else
                    std::cout << 'O';

                if (j!=2)
                    std::cout << '|';
            }
            std::cout<<std::endl;
        }
    }

    void AddTicTac(TicTac tt, unsigned int x, unsigned int y)
    {
        if (x<=3 && y <=3 && m_values[x][y]==TicTac::EMPTY)
        {
            m_values[x][y] = tt;
        }
        else
        {
            throw std::invalid_argument("invalid input " + std::to_string(x) + "," + std::to_string(y));
        }

    }

    bool isFull ()
    {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (m_values[i][j]== TicTac::EMPTY)
                    return false;
            }
        }
        return true;
    }

    void AIPut ()
    {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (m_values[i][j]== TicTac::EMPTY)
                {
                    m_values[i][j] = TicTac::O;
                    return;
                }
            }
        }

        throw std::logic_error("Nowhere to put anymore!");
    }

    void ReadUserInput ()
    {
//        while(true)
        while(!isFull())
        {
//            CheckFull

            while (true)
            {
                unsigned int x, y;
                std::cout << std::endl << "Input row:" << std::endl;
                std::cin >> x;
                std::cout << std::endl << "Input column:" << std::endl;
                std::cin >> y;

                if (x<=3 && y <=3 && m_values[x][y]== TicTac::EMPTY)
                {
                    m_values[x][y]=TicTac::X;
                    break;
                }
                else
                {
                    std::cout << "bad input " << x << "," << y << " please reInput" << std::endl;
                }
            }

//            CheckFull

            if (isFull())
              break;

            std::cout << "Before AI:" << std::endl;
            Print();

            AIPut ();

            std::cout << "After AI:" << std::endl;
            Print();
        }
        std::cout << "Game over!" << std::endl;
    }
};



void test_tictactoe()
{
    TicTacToe ttt;
//    ttt.AddTicTac(TicTac::X, 0, 1);
//    ttt.Print();
//
//    std::cout << std::endl;

//    for (int i = 0; i <9; ++i) {
//        ttt.AIPut();
//        ttt.Print();
//        std::cout << "Board Full is " << std::boolalpha << ttt.isFull() << std::endl;
//    }

    ttt.ReadUserInput ();
    ttt.Print();
}


#endif //CPPSANDBOX_TICTACTOE_H
