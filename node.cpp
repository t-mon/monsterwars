#include "node.h"
#include "monster.h"
#include "player.h"

Node::Node(int x, int y, int nodeNumber, QObject *parent):
    QObject(parent),
    m_monster(0),
    m_x(x),
    m_y(y),
    m_g(0),
    m_nodeNumber(nodeNumber),
    m_h(0),
    m_previousNode(0),
    m_nextNode(0)
{
}

int Node::x() const
{
    return m_x;
}

int Node::y() const
{
    return m_y;
}

int Node::number() const
{
    return m_nodeNumber;
}

void Node::setMonster(Monster *monster)
{
    if (monster == 0) {
        m_color = QColor(255, 255, 255, 100);
    } else {
        m_color = monster->color();
    }
    emit colorChanged();
    m_monster = monster;
}

Monster *Node::monster() const
{
    return m_monster;
}

void Node::setColor(const QColor &color)
{
    m_color = color;
    emit colorChanged();
}

void Node::setG(const int &g)
{
    m_g = g;
    m_f = m_g + m_h;
}

int Node::g() const
{
    return m_g;
}

void Node::setH(const double &h)
{
    m_h = h;
    m_f = m_g + m_h;
}

double Node::h() const
{
    return m_h;
}

QColor Node::color() const
{
    return m_color;
}

double Node::f() const
{
    return m_f;
}

void Node::setNorthNode(Node *node)
{
    m_northNode = node;
}

Node *Node::northNode() const
{
    return m_northNode;
}

void Node::setNorthWestNode(Node *node)
{
    m_northWestNode = node;
}

Node *Node::northWestNode() const
{
    return m_northWestNode;
}

void Node::setNorthEastNode(Node *node)
{
    m_northEastNode = node;
}

Node *Node::northEastNode() const
{
    return m_northEastNode;
}

void Node::setSouthNode(Node *node)
{
    m_southNode = node;
}

Node *Node::southNode() const
{
    return m_southNode;
}

void Node::setSouthWestNode(Node *node)
{
    m_southWestNode = node;
}

Node *Node::southWestNode() const
{
    return m_southWestNode;
}

void Node::setSouthEastNode(Node *node)
{
    m_southEastNode = node;
}

Node *Node::southEastNode() const
{
    return m_southEastNode;
}

void Node::setEastNode(Node *node)
{
    m_eastNode = node;
}

Node *Node::eastNode() const
{
    return m_eastNode;
}

void Node::setWestNode(Node *node)
{
    m_westNode = node;
}

Node *Node::westNode() const
{
    return m_westNode;
}

void Node::setNextNode(Node *node)
{
    m_nextNode = node;
}

Node *Node::nextNode() const
{
    return m_nextNode;
}

void Node::setPreviousNode(Node *node)
{
    m_previousNode = node;
}

Node *Node::previousNode() const
{
    return m_previousNode;
}
