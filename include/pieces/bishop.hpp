/**
 * @file bishop.hpp
 * @author group
 * @brief subclasse com a lógica do bishop
 * @version 0.1
 * @date 2022-11-28
 * @details responsável por construir a subclasse bishop
 * e chamar a função def_possible_movements.
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"

using namespace std;

/**
 * @brief define os possíveis movimentos 
 * @details dentro da subclasse Bishop, que herda de Piece, construímos
 *  o bispo recebendo sua cor, determinamos uma matriz de possíveis movimentos
 *  recebendo seu ponto atual.
 */ 
class Bishop: public Piece {

    public:

        Bishop(string color);
        ~Bishop(){};

        /**
         * @brief define uma matriz de possíveis movimentos
         * 
         * @param spot é o ponto atual da peça, necessário para sabermos
         * seus possíveis futuros movimentos.
         */
        void def_possible_movements(int* spot) override;

};

#endif