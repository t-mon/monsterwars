#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QObject>
#include <QDebug>

class Node;
class Board;
class Monster;

class PathFinder : public QObject
{
    Q_OBJECT

public:
    explicit PathFinder(Board *board);
    QList<Node *> calculatePath(Monster *startMonster, Monster *goalMonster);

private:
    Board *m_board;
    Node* m_startNode;
    Node* m_goalNode;
    QList<Node*> m_openList;
    QList<Node*> m_closedList;

    bool m_showAlgorithm;

    double calculateDistance(Node *from, Node *to);
    double calculateManhattenDistance(Node *from, Node *to);
    void insertInOpenList(Node *node);
    void removeFromOpenList(Node *node);

    void expand(Node *currentNode);
};

bool openListLessThan(Node *a, Node *b);

#endif // PATHFINDER_H
