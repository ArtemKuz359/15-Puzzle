#include "gameboard.h"
#include <random>
#include <algorithm>
#include <numeric>
using namespace std;


bool isAdjacent(const GameBoard::Position first, const GameBoard::Position second)
{
    if (first == second){
        return false;
    }

    const auto calcDistance = [](const size_t pos1, size_t pos2){
        int distance = static_cast<int>(pos1);
        distance -= static_cast<int>(pos2);
        distance = abs(distance);
        return distance;
    };
    bool result {false};

    if(first.first == second.first){
        int distance = calcDistance(first.second, second.second);
        if(distance == 1){
            result = true;
        }
    } else if (first.second == second.second){
        int distance = calcDistance(first.first, second.first);
        if(distance == 1){
            result = true;
        }

    }
    return result;
}

GameBoard::GameBoard(QObject *parent, const size_t boardDimension)
    : QAbstractListModel{parent},
      m_dimension {boardDimension},
      m_boardSize {m_dimension * m_dimension}
{
    m_rawBoard.resize(m_boardSize);
    iota(m_rawBoard.begin(), m_rawBoard.end(), 1);
    shuffle();
}



int GameBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_rawBoard.size();
}

QVariant GameBoard::data(const QModelIndex &index,int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
    {
        return {};
    }
    const int rowIndex = index.row();

    if(!isPositionValid(rowIndex)){
        return{};
    }
    return QVariant::fromValue(m_rawBoard[rowIndex].value);
}

void GameBoard::shuffle()
{
    static auto seed = ::chrono::system_clock::now().time_since_epoch().count();
    static ::mt19937 generator(seed);

    ::shuffle(m_rawBoard.begin(), m_rawBoard.end(), generator);

    if (m_dimension == 3)
    {
        vector<vector<int>> unsolvableConfigs{
            {1, 2, 3, 4, 5, 6, 8, 7, 9},
            {1, 2, 3, 4, 5, 6, 7, 9, 8},
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 8, 9, 7},
            {1, 2, 3, 4, 5, 6, 9, 7, 8},
            {1, 2, 3, 4, 5, 6, 9, 8, 7}
        };

        for (const auto& unsolvableConfig : unsolvableConfigs)
        {
            vector<size_t> unsolvableConfigTiles(unsolvableConfig.begin(), unsolvableConfig.end());
            bool match = true;

            for (size_t i = 0; i < m_boardSize; ++i)
            {
                if (m_rawBoard[i].value != unsolvableConfigTiles[i])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                shuffle();
            }
             return;
        }
    }
    else if (m_dimension == 4)
    {
        vector<vector<int>> unsolvableConfigs{
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 14, 16},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 14},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 15},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 16, 14, 15},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 15},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}
        };

        for (const auto& unsolvableConfig : unsolvableConfigs)
        {
            vector<size_t> unsolvableConfigTiles(unsolvableConfig.begin(), unsolvableConfig.end());
            bool match = true;

            for (size_t i = 0; i < m_boardSize; ++i)
            {
                if (m_rawBoard[i].value != unsolvableConfigTiles[i])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                shuffle();
            }
             return;
        }
    }
    else if (m_dimension == 5)
    {
        vector<vector<int>> unsolvableConfigs{
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 24},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 23},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 25, 23, 24},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 23, 22, 25, 24},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 24, 23, 25, 22},
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 24, 22, 25, 23}

        };

        for (const auto& unsolvableConfig : unsolvableConfigs)
        {
            vector<size_t> unsolvableConfigTiles(unsolvableConfig.begin(), unsolvableConfig.end());
            bool match = true;

            for (size_t i = 0; i < m_boardSize; ++i)
            {
                if (m_rawBoard[i].value != unsolvableConfigTiles[i])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                shuffle();
            }
             return;
        }
    }
}




bool GameBoard::move(int index)
{
    if(!isPositionValid((index))){
        return false;
    }

    const Position elementPosition {getRowCol(index)};

    auto hiddenElementIterator = find(m_rawBoard.begin(), m_rawBoard.end(), boardSize());

    Q_ASSERT(hiddenElementIterator != m_rawBoard.end());
    Position hiddenElementPosition {getRowCol(distance(m_rawBoard.begin(), hiddenElementIterator))};

    if(!isAdjacent(elementPosition, hiddenElementPosition)){
        return false;
    }
    swap(hiddenElementIterator->value, m_rawBoard[index].value);


    return true;
}

GameBoard::Position GameBoard::getRowCol(size_t index) const
{
    Q_ASSERT(m_dimension>0);
    size_t row = index / m_dimension;
    size_t column = index % m_dimension;
    return make_pair(row, column);
}

bool GameBoard::isPositionValid(const size_t position) const
{
    return position < m_boardSize;
}

void GameBoard::setBoardSize(int newSize)
{
    if (newSize < 2 || newSize == (int)m_dimension)
    {
        return;
    }
    m_dimension = newSize;
    m_boardSize = m_dimension * m_dimension;
    m_rawBoard.resize(m_boardSize);
    iota(m_rawBoard.begin(), m_rawBoard.end(), 1);
    shuffle();
}
bool GameBoard::isBoardValid() const
{
    int inv = 0;
    for (size_t i = 0; i < m_boardSize; ++i) {
        for (size_t j = i; j < m_boardSize; ++j) {
            if (m_rawBoard[j].value < m_rawBoard[i].value && m_rawBoard[i].value != m_boardSize) {
                ++inv;
            }
        }
    }


    for (size_t i = 0; i < m_boardSize; ++i) {
        if (m_rawBoard[i].value == m_boardSize) {
            inv++;
        }
    }

    return (inv % 2) == 0;
}

size_t GameBoard::boardSize() const
{
    return m_boardSize;
}

void GameBoard::start()
{
    shuffle();

}

size_t GameBoard::dimension() const
{
    return m_dimension;
}
