#ifndef Chessboard_Class
#define Chessboard_Class

#include <iostream>
#include <vector>
#include "Position.cpp"
#include "Queen.cpp"
#include "Ring.cpp"

class Chessboard : public Ring {
    int centerChessboard;
    int maxQueenPlaced;
    bool pair = true;
    public:
        void setData(int s){
            if (s > 0) {
                size = s;
                if(size % 2 == 1) pair = false;
                maxQueenPlaced = getMaxQueenPlaced();
            }
        }

        int getMaxQueenPlaced(){
            int middle = getMiddle();
            if(pair){
                return (middle - 1) * 4 + 3;
            } else {
                return (middle - 1) * 4;
            }
        }

        int getMiddle(){
            int num = size;
            if(!pair) num++;
            return num / 2;
        }

        void getSolutions(){
            int i, count=0, middle = getMiddle(), possibleQueen;
            std::vector<Queen> solutions, newSolutions, history;
            Queen queen;

            if(!pair)middle--; //REGOLA DELLA COLONNA CENTRALE
            std::cout << "Unique Solutions in " << size << "x" << size << " \nPossible queen: " << maxQueenPlaced << "\nTo " << middle << '\n';
            for(int x = 0; x < middle; x++) {
                solutions.clear();
                queen.setPosition(x, 0);
                queen.setRing(0);
                solutions.push_back(queen);
                for(;;){
                    possibleQueen = maxQueenPlaced - getInvalidSideOfRings(solutions);
                    for(i = 0; i < getMiddle() ; i++){ //PER OGNI ANELLO
                        if(possibleQueen + solutions.size() >= size){ //SE ESISTONO REGINE POSSIBILI PER TROVARE UNA SOLIUZIONE
                            newSolutions = getSolutionInARing(i, solutions, history); //DAMMI LE NUOVE REGINE NELL'ANELLO i IN BASE ALLE REGINE GIÀ POSIZIONATE E LE VECCHIE SOLUZIONI
                            if(newSolutions.size() > 0){
                                if(solutions.size() + newSolutions.size() < 3 && i == 0) break;
                                for(int j = 0; j < newSolutions.size(); j ++){
                                    solutions.push_back(newSolutions[j]); //AGGIUNGI LE REGINE
                                }
                                possibleQueen -= getInvalidSideOfRings(newSolutions) + 4;
                            }
                        }
                    }
                    if(solutions.size() <= 1) break;
                    if(solutions.size() == size) { //DEBUG
                        count++;
                        std::cout << "SOLUTION " << count << '\n';
                        printSolution(solutions);
                    }
                    Queen invalidQueen = (Queen)solutions.back();
                    solutions.pop_back();
                    solutions.back().setInvalid(invalidQueen.position);
                    if(invalidQueen.getX() == (size - 1) && x == 0) {
                        invalidQueen.setRotations(size);
                        invalidQueen.setTranslations();
                        solutions.back().setInvalid(invalidQueen.getTranslation(0));
                    }
                }
                queen.setRotations(size);
                queen.setTranslations();
                history.push_back(queen);
            }
        }

        int getInvalidSideOfRings(std::vector<Queen> queens){
            int response = 0, middle = getMiddle(), x , y, ring;
            for(int j = 0; j < queens.size(); j++){
                Queen indexQueen = (Queen) queens[j];
                x = indexQueen.getX();
                y = indexQueen.getY();
                ring = indexQueen.getRing();
                if( x > ring && x < (size - ring - 1) ||
                    y > ring && y < (size - ring - 1)) {
                    if(pair){
                        if(!((x == middle || x == middle - 1) ||
                            (y == middle || y == middle - 1)) ){
                            response++;
                        }
                    } else {
                        if(!((x < middle - 1 || x > middle - 1) ||
                            (y < middle - 1 || y > middle - 1)) ){
                            response++;
                        }
                    }
                }
                if(x == y){ response++; } //SICURO?
            }return response;
        }

        void saveQueenInHistory(Queen queen){
            queen.setRotations(size);
            queen.setTranslations();
        }

        void saveQueenPosition(Queen queen){
            placed.push_back(queen);
        }

        void printSolution(std::vector<Queen> queens){
            for(int j = 0; j < queens.size(); j++){
                Queen indexQueen = (Queen) queens[j];
                std::cout << "\t(" << indexQueen.getX() << ", " << indexQueen.getY() << ")" << '\n';
            }
        }
};
#endif
