#include "gameboard.h"
#include <random>
#include <algorithm>
#include <numeric>

namespace
{
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
}

using namespace std;

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
    const int rowIndex {index.row()};

    if(!isPositionValid(rowIndex)){
        return{};
    }
    return QVariant::fromValue(m_rawBoard[rowIndex].value);
}

void GameBoard::shuffle()
{
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);

    std::shuffle(m_rawBoard.begin(), m_rawBoard.end() , generator);
}

bool GameBoard::move(int index)
{
    if(!isPositionValid(static_cast<size_t>(index))){
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

    emit dataChanged(createIndex(0,0), createIndex(m_boardSize,0));
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

    const size_t start_point = 1;
    for (size_t i = 0; i < m_boardSize; ++i) {
        if (m_rawBoard[i].value == m_boardSize) {
            inv += start_point + i / m_dimension;
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
