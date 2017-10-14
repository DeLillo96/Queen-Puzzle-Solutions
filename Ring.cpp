#ifndef Ring_Class
#define Ring_Class

#include <iostream>
#include <vector>
#include "Position.cpp"
#include "Queen.cpp"

class Ring {
    public:
        int size;
        std::vector<Queen> placed;
        std::vector<Queen> getSolutionInARing(int offset, std::vector<Queen> oldQueens, std::vector<Queen> historyQueens){
            Queen probeQueen;
            std::vector<Queen> newQueens;
            for(int i = 0; i < 4; i++) {
                if(isSideFree(i, offset, oldQueens)){
                    probeQueen = getPositionsInASide(i, offset, oldQueens, historyQueens);
                    if(probeQueen.getRing() != -1) {
                        newQueens.push_back(probeQueen);
                        oldQueens.push_back(probeQueen);
                    }
                }
            }
            return newQueens;
        }

        Queen getPositionsInASide(int side, int offset, std::vector<Queen> oldQueens, std::vector<Queen> historyQueens){
            if(side == 0){
                return getPositionInTopBottom(true, offset, oldQueens, historyQueens);
            }
            if(side == 1){
                return getPositionInLeftRight(false, offset, oldQueens, historyQueens);
            }
            if(side == 2){
                return getPositionInTopBottom(false, offset, oldQueens, historyQueens);
            }
            return getPositionInLeftRight(true, offset, oldQueens, historyQueens);
        }

        Queen getPositionInTopBottom(bool side, int offset, std::vector<Queen> oldQueens, std::vector<Queen> historyQueens){
            Queen probeQueen (offset);
            int lowLimit = 0 + offset;
            int highLimit = size - offset - 1;

            if(lowLimit == highLimit) highLimit++;
            for(int i = lowLimit; i <= highLimit; i++) {
                if(side) {
                    probeQueen.setPosition(i, lowLimit);
                } else {
                    probeQueen.setPosition(i, highLimit);
                }
                if(!probeQueen.isValid(oldQueens)) continue;
                if(probeQueen.isAlreadyPositioned(historyQueens)) continue;
                return probeQueen;
            }
            probeQueen.setRing(-1);
            return probeQueen;
        }

        Queen getPositionInLeftRight(bool side, int offset, std::vector<Queen> oldQueens, std::vector<Queen> historyQueens){
            Queen probeQueen (offset);
            int lowLimit = 0 + offset;
            int highLimit = size - offset - 1;

            if(lowLimit == highLimit) highLimit++;
            for(int i = lowLimit; i <= highLimit; i++) {
                if(side) {
                    probeQueen.setPosition(lowLimit, i);
                } else {
                    probeQueen.setPosition(highLimit, i);
                }
                if(!probeQueen.isValid(oldQueens))continue;
                if(probeQueen.isAlreadyPositioned(historyQueens)) continue;
                return probeQueen;
            }
            probeQueen.setRing(-1);
            return probeQueen;
        }

        bool isSideFree(int side, int offset, std::vector<Queen> oldQueens) {
            Queen queen;
            for(int i = 0; i < oldQueens.size(); i++) {
                queen = (Queen) oldQueens[i];
                switch(side){
                    case 0: if(queen.getY() == offset) return false; break;
                    case 1: if(queen.getX() == size - offset - 1) return false; break;
                    case 2: if(queen.getY() == size - offset - 1) return false; break;
                    case 3: if(queen.getX() == offset) return false; break;
                }
            }
            return true;
        }
};
#endif
