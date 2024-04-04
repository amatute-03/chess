#include <string>
#include <vector>
using namespace std;

class piece {
    public:
        void setPieceType(char type);
        char getPieceType();
        void setMoveType(int type);
        vector<vector<string>> getMoveType();
        void setSide(int s);
        int getSide();
        void setPrefix(string pre);
        string getPrefix();
        void setSuffix(string suf);
        string getSufix();
    private:
        char pieceType;
        int moveType;
        int side;
        string prefix;
        string suffix;
        vector<vector<vector<string>>> movements;
        void initMovements();
};