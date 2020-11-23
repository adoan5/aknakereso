#ifndef MINESWEEPERGAMEMODEL_H
#define MINESWEEPERGAMEMODEL_H
#include <vector>
#include <algorithm>

using namespace std;

enum Action {
    MARK = -3, UNMARK = -2
};

struct State {
    unsigned x;
    unsigned y;
    int action;

    State(unsigned _x, unsigned _y, int _action) {
        x = _x;
        y = _y;
        action = _action;
    }

};


class MineSweeperGameModel
{
public:
    MineSweeperGameModel(unsigned x, unsigned y, unsigned mines);
    vector<State> clickOnTile(unsigned  x, unsigned  y, bool mouse);
    bool isEndGame() {return endgame;}
    bool isAlive() {return alive;}

private:
    void addMine(pair<int,int> position);
    void placeMines(unsigned mines);
    void printField();
    void printDiscoveredMap();
    int uncoverField(unsigned x, unsigned y);
    void markAllUnmarkedFields(vector<State> &modifications);
    void showAllMines(vector<State> &modifications);
    void discoverAllEmptyField(vector<State> &modifications, unsigned x, unsigned y);
    bool uncoverNeighBourHood(vector<State> &modifications, unsigned x, unsigned y);
    bool isNeighbourElementOfField(unsigned x, unsigned y, int i, int j);

    vector<vector<int>> field;
    vector<vector<int>> discoveredField;
    vector<pair<int,int>> mines;

    unsigned int numOfDiscoveredFields;
    unsigned int numOfFieldsToDiscover;

    bool endgame;
    bool alive;

};

#endif // MINESWEEPERGAMEMODEL_H
