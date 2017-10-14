#ifndef Position_Class
#define Position_Class

class Position
{
    public:
        int x;
        int y;

        Position(int x1, int y1) { setValue(x1,y1); }

        Position() { setValue(0,0); }

        void setValue(int x1, int y1) {
            x = x1;
            y = y1;
        }
};
#endif
