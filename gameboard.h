#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QAbstractListModel>
#include <vector>

using namespace std;

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)
    Q_PROPERTY(int hiddenElementValue READ boardSize CONSTANT)

public:
    static constexpr size_t defaultPuzzleDimension {4};
    explicit GameBoard(QObject* parent = nullptr, const size_t boardDimension = defaultPuzzleDimension);
    void setBoardSize(int newSize);

    struct Tile{
        size_t value{};
        Tile& operator =(const size_t newValue){
            value = newValue;
            return *this;
        }
        bool operator ==(const size_t other) {
            return other == value;
        }
    };

    void start();

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    size_t dimension() const;

    Q_INVOKABLE bool move(int index);
    using Position = pair<size_t,size_t>;
    size_t boardSize() const;
    Position getRowCol(size_t index) const;
    void shuffle();

    bool isPositionValid(const size_t position)const;

    bool isBoardValid() const;
private:
    vector<Tile> m_rawBoard;
    size_t m_dimension;
    size_t m_boardSize;
};

#endif
