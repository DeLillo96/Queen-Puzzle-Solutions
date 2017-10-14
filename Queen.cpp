#ifndef Queen_Class
#define Queen_Class

#include <iostream>
#include <vector>
#include "Position.cpp"

class Queen {
    int ring = 0;
    Position * rotations = nullptr;
    Position * translations = nullptr;
    public:
        Position position;
        std::vector<Position> invalid;

        Queen() { setRing(0); }

        Queen(int r) { setRing(r); }

        Queen(Position psx) { position = psx; }

        Queen(int x, int y) { position.setValue(x, y); }

        Position getPosition() { return position; }

        void setPosition(Position psx) { position = psx; }

        void setPosition(int x, int y) { position.setValue(x, y); }

        int getX() { return position.x; }

        int getY() { return position.y; }

        int getRing() { return ring; }

        void setRing(int r) { ring = r;}

        void setRotations(int size){
            if(rotations == nullptr) rotations = (Position *) malloc(sizeof(Position)*3);
            int x1 = size - position.x - 1;
            int y1 = size - position.y - 1;
            rotations[0] = Position(y1, position.x);
            rotations[1] = Position(x1, y1);
            rotations[2] = Position(position.y, x1);
        }

        Position getRotation(int index){ return rotations[index]; }

        void setTranslations(){
            if(position.x != position.y){
                if(translations == nullptr) translations = (Position *) malloc(sizeof(Position)*4);
                int i;
                translations[0] = Position(position.y, position.x);
                for(i = 1; i < 4; i++) {
                    translations[i] = Position(rotations[i - 1].y, rotations[i - 1].x);
                }
            }
        }

        Position getTranslation(int index){ return translations[index]; }

        void setInvalid(Position queen) {
            Position invalidPosition;
            invalidPosition.x = queen.x;
            invalidPosition.y = queen.y;
            invalid.push_back(invalidPosition);
        }

        std::vector<Position> getInvalid() { return invalid; }

        bool isValid(std::vector<Queen> queens)  {
            Position queen;
            for(int i = 0; i < queens.size(); i++) {
                queen = ((Queen) queens[i]).getPosition();
                if( isColumnFree(queen) ||
                    isRowFree(queen) ||
                    areDiagonalsFree((Queen) queens[i]) ||
                    isInvalid((Queen) queens[i])
                ) return false;
            }
            return true;
        }

        bool isInvalid(Queen queen){
            for(int i = 0; i < queen.invalid.size(); i++){
                if(isEqual((Position) queen.invalid[i])) return true;
            }
            return false;
        }

        bool isAlreadyPositioned(std::vector<Queen> queens) {
            Queen queen;
            for(int i = 0; i < queens.size(); i++) {
                queen = (Queen) queens[i];
                if(isEqual(queen.position)) return true;   //same row
                for(int j = 0; j < 3; j++) {
                    if(isEqual(queen.rotations[j])) return true;           //rotations
                }
                if(position.x == position.y || queen.position.x == queen.position.y) continue;
                for(int j = 0; j < 4; j++) {
                    if(isEqual(queen.translations[j])) return true;     //translations
                }
            }
            return false;
        }

        bool isEqual(std::vector<Queen> queens) {
            for(int i = 0; i < queens.size(); i++) {
                if( isEqual((((Queen) queens[i])).position)) return true;
            }
            return false;
        }


        bool isEqual(Position queen) { return isRowFree(queen) && isColumnFree(queen); }

        bool isRowFree(Position queen){ return position.y == queen.y; }

        bool isColumnFree(Position queen){ return position.x == queen.x; }

        bool areDiagonalsFree(Queen queen){
            return (position.y + position.x) == (queen.position.y + queen.position.x) || (position.y - position.x) == (queen.position.y - queen.position.x);
        }
};
#endif
