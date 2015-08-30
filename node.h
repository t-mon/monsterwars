#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QDebug>
#include <QColor>

class Monster;

class Node : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x CONSTANT)
    Q_PROPERTY(int y READ y CONSTANT)
    Q_PROPERTY(int number READ number CONSTANT)
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

public:
    explicit Node(int x, int y, int nodeNumber, QObject *parent = 0);

    int x() const;
    int y() const;
    int number() const;

    void setMonster(Monster* monster);
    Monster* monster() const;
    void setColor(const QColor &color);
    QColor color() const;

    // f = g + h (A* algorithm)
    double f() const;

    // g... costs from start to this node
    void setG(const int &g);
    int g() const;

    // h...heuristic estimate (vector length
    void setH(const double &h);
    double h() const;

    void setNorthNode(Node* node);
    Node *northNode() const;

    void setNorthWestNode(Node* node);
    Node *northWestNode() const;

    void setNorthEastNode(Node* node);
    Node *northEastNode() const;

    void setSouthNode(Node* node);
    Node *southNode() const;

    void setSouthWestNode(Node* node);
    Node *southWestNode() const;

    void setSouthEastNode(Node* node);
    Node *southEastNode() const;

    void setEastNode(Node* node);
    Node *eastNode() const;

    void setWestNode(Node* node);
    Node *westNode() const;

    // needed for the pathfinding algorithm
    void setNextNode(Node* node);
    Node *nextNode() const;

    void setPreviousNode(Node* node);
    Node *previousNode() const;

private:
    int m_x;
    int m_y;
    int m_nodeNumber;
    Monster *m_monster;
    int m_playerId;
    QColor m_color;

    // f = g + h (A* algorithm)
    int m_g;
    double m_h;
    double m_f;

    // needed for the pathfinding algorithm
    Node *m_nextNode;
    Node *m_previousNode;

    Node *m_northNode;
    Node *m_northWestNode;
    Node *m_northEastNode;
    Node *m_southNode;
    Node *m_southWestNode;
    Node *m_southEastNode;
    Node *m_eastNode;
    Node *m_westNode;

signals:
    void colorChanged();

};
#endif // NODE_H
