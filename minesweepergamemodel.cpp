#include "minesweepergamemodel.h"
#include <algorithm>
#include <iostream>
#include <list>
using namespace std;

MineSweeperGameModel::MineSweeperGameModel(unsigned x, unsigned y, unsigned mines)
{
    field.clear();
    mines = mines<(x*y)?mines:x*y-1;

    for (unsigned i=0; i<x; i++) {
        vector<int> tmp(y);
        vector<int> dtmp(y);
        field.push_back(tmp);
        discoveredField.push_back(dtmp);
    }

    placeMines(mines);

    alive = true;
    endgame = false;
    numOfDiscoveredFields = 0;
    numOfFieldsToDiscover = (x*y) - mines;

}


void MineSweeperGameModel::placeMines(unsigned mines)
{
    if (field.size()==0)
        return;

    vector<pair<int,int>> fields;

    int x = static_cast<int>(field.size());

    int y = static_cast<int>(field[0].size());

    for (int i=0; i<x; i++) {
        for (int j=0; j<y; j++) {
            fields.push_back(pair<int,int>(i,j));
        }
    }

    random_shuffle(fields.begin(), fields.end());

    for (unsigned i=0; i<mines; i++) {
        addMine(fields[i]);
    }

}

void MineSweeperGameModel::printField()
{
    for (unsigned i=0; i<field.size(); i++) {
        for (int f: field[i]) {
            if (f>=0) {
                cout << f << " ";
            } else {
                cout <<  "x ";
            }
        }
        cout << endl;
    }

}

void MineSweeperGameModel::printDiscoveredMap()
{
    for (unsigned i=0; i<discoveredField.size(); i++) {
        for (int f: discoveredField[i]) {
            if (f>=0) {
                cout << f << " ";
            } else {
                cout <<  "x ";
            }
        }
        cout << endl;
    }
}


void MineSweeperGameModel::markAllUnmarkedFields(vector<State> &states)
{

    for (pair<int,int> pos: mines) {
        unsigned mx = static_cast<unsigned>(pos.first);
        unsigned my = static_cast<unsigned>(pos.second);
        if (discoveredField[mx][my] == 0) {
            discoveredField[mx][my] = -1;
            states.push_back(State(mx,my,Action::MARK));
        }
    }
}

void MineSweeperGameModel::showAllMines(vector<State> &modifications)
{
    for (pair<int,int> pos: mines) {
        unsigned mx = static_cast<unsigned>(pos.first);
        unsigned my = static_cast<unsigned>(pos.second);
        if (discoveredField[mx][my] == 0) {
            modifications.push_back(State(mx,my,field[mx][my]));
        }
    }
}


vector<State> MineSweeperGameModel::clickOnTile(unsigned x, unsigned y, bool mouse)
{
    vector<State> states;

    if (x >= field.size() || y >= field[0].size() || endgame) {
        return states;
    }


    if (mouse) {
        if (discoveredField[x][y] == -1) {
            discoveredField[x][y] = 0;
            states.push_back(State(x,y,Action::UNMARK));
        } else {
            int val = uncoverField(x,y);
            states.push_back(State(x,y,val));
            if (val == -1) {
                alive = false;
                endgame = true;
                showAllMines(states);
            } else if (numOfDiscoveredFields == numOfFieldsToDiscover) {
                endgame = true;
                markAllUnmarkedFields(states);
            } else if (val == 0) {
                discoverAllEmptyField(states,x,y);
            }
        }
    } else {
        if (discoveredField[x][y] == -1) {
            discoveredField[x][y] = 0;
            states.push_back(State(x,y,Action::UNMARK));
        } else if (discoveredField[x][y] == 0) {
            discoveredField[x][y] = -1;
            states.push_back(State(x,y,Action::MARK));
        } else {
            bool alive = uncoverNeighBourHood(states, x, y);
            if (!alive) {
                alive = false;
                endgame = true;
                showAllMines(states);
            } else if (numOfDiscoveredFields == numOfFieldsToDiscover) {
                endgame = true;
                markAllUnmarkedFields(states);
            }
        }
    }

    return states;
}

void MineSweeperGameModel::addMine(pair<int, int> position)
{
    unsigned x = static_cast<unsigned>(position.first);
    unsigned y = static_cast<unsigned>(position.second);

    mines.push_back(position);

    field[x][y] = -1;

    for (int i=-1; i<=1; i++) {
        for (int j=-1; j<=1; j++) {

            int neighbour_x = static_cast<int>(x) + i;
            int neighbour_y = static_cast<int>(y) + j;

            if (neighbour_x < 0 || neighbour_y < 0) {
                continue;
            }

            unsigned u_neigh_x = static_cast<unsigned>(neighbour_x);
            unsigned u_neigh_y = static_cast<unsigned>(neighbour_y);

            if (u_neigh_x >= field.size() || u_neigh_y >= field[0].size()
                    || field[u_neigh_x][u_neigh_y] == -1) {
                continue;
            }

            field[u_neigh_x][u_neigh_y]++;
        }
    }
}


bool MineSweeperGameModel::isNeighbourElementOfField(unsigned x, unsigned y, int i, int j)
{
    unsigned newX = static_cast<unsigned>(static_cast<int>(x)+i);
    unsigned newY = static_cast<unsigned>(static_cast<int>(y)+j);
    return static_cast<int>(x) + i >=0 && static_cast<int>(y) + j >=0
            && newX < field.size() && newY < field[0].size();
}


int MineSweeperGameModel::uncoverField(unsigned x, unsigned y)
{
    if (discoveredField[x][y] == 0) {
        discoveredField[x][y] = 1;
        numOfDiscoveredFields++;
    }
    return field[x][y];
}


bool MineSweeperGameModel::uncoverNeighBourHood(vector<State> &modifications, unsigned x, unsigned y)
{
    bool alive = true;

    return alive;
}

void MineSweeperGameModel::discoverAllEmptyField(vector<State> &modifications, unsigned x, unsigned y)
{
    State init(x,y,field[x][y]);
    list<State> stateList;
    stateList.push_back(init);
}

