#include <string>
#include <vector>
using namespace std;

class piece {
    public:
        void setPieceType(char type);
        char getPieceType();
        void setMoveType(int type);
        int getMoveVal();
        vector<vector<string>> getMoveType();
        void setSide(int s);
        int getSide();
    private:
        char pieceType;
        int moveType;
        int side;
        vector<vector<vector<string>>> movements;
        void initMovements();
};