#include "pathfinder.h"
#include "board.h"
#include "monster.h"
#include "node.h"
#include "math.h"

PathFinder::PathFinder(Board *board):
    QObject(board),
    m_board(board)
{
    m_showAlgorithm = false;
}

QList<Node *> PathFinder::calculatePath(Monster *startMonster, Monster *goalMonster)
{
    // reset board
    foreach (Node* node, m_board->nodes()) {
        node->setG(0);
        node->setH(0);
        node->setNextNode(0);
        node->setPreviousNode(0);
    }

    m_openList.clear();
    m_closedList.clear();

    // set the start and end node
    //m_goalNode = m_board->nodeAt(goalMonster->position().x(), goalMonster->position().y());
    //m_startNode = m_board->nodeAt(startMonster->position().x(), startMonster->position().y());
    //initialize the start node
    m_startNode->setG(0);
    m_startNode->setH(calculateDistance(m_startNode, m_goalNode));

    insertInOpenList(m_startNode);

    Node* currentNode;

    // A* Search algorithm
    // search until we reached the goal (path found) node or until the openList is empty (no path found)
    while (currentNode != m_goalNode && !m_openList.isEmpty()){
        currentNode = m_openList.takeFirst();
        m_closedList.append(currentNode);
        if (m_showAlgorithm)
            currentNode->setColor(QColor(100,50,0));

        expand(currentNode);

        // check if we have reached the goal
        if (currentNode == m_goalNode) {
            qDebug() << "  --> calculated path from monster " << m_startNode->monster()->id() << "  -->  " << m_goalNode->monster()->id();
            QList<Node *> path;
            while (currentNode != m_startNode) {
                path.insert(0, currentNode);
                currentNode->setColor(QColor(255,0,0));
                currentNode = currentNode->previousNode();
            }
            return path;
        }
    }
}

double PathFinder::calculateDistance(Node *from, Node *to)
{
    int dx = from->x() - to->x();
    int dy = from->y() - to->y();
    return sqrt(pow(dx,2) + pow(dy,2));
}

double PathFinder::calculateManhattenDistance(Node *from, Node *to)
{
    return abs(to->x() - from->x()) + abs((to->y() - from->y()));
}

void PathFinder::removeFromOpenList(Node *node)
{
    for (int i = 0; i < m_openList.count(); ++i) {
        if (m_openList.at(i) == node) {
            m_openList.removeAt(i);
            return;
        }
    }
}

void PathFinder::insertInOpenList(Node *node)
{
    if (m_openList.isEmpty()) {
        m_openList.append(node);
        return;
    }
    for (int i = 0; i < m_openList.count(); i++) {
        if (m_openList.at(i)->f() >= node->f()) {
            m_openList.insert(i, node);
            return;
        }
    }
}

void PathFinder::expand(Node *currentNode)
{
    QList<Node *> neighborNodes;
    neighborNodes.append(currentNode->northNode());
    neighborNodes.append(currentNode->northWestNode());
    neighborNodes.append(currentNode->northEastNode());
    neighborNodes.append(currentNode->eastNode());
    neighborNodes.append(currentNode->westNode());
    neighborNodes.append(currentNode->southNode());
    neighborNodes.append(currentNode->southWestNode());
    neighborNodes.append(currentNode->southEastNode());

    // check each neighbor node if:
    //      - it exits
    //      - it is not already checked (not in closedList)
    //      - it is not already in the queue (not in the openList)
    foreach (Node* neighbor, neighborNodes) {
        // check if we allready walked this node
        if (neighbor != 0 && !m_closedList.contains(neighbor)) {
            // check if the neighbor is walkable
            if (neighbor->monster() == 0 || neighbor->monster() == m_startNode->monster() || neighbor->monster() == m_goalNode->monster()) {
                double withCurrentNodeG = currentNode->g() + calculateDistance(currentNode, neighbor);
                // check if this node is already in the openList
                if (m_openList.contains(neighbor)) {
                    // check if this node is a better parent as the current parent of this neighbor
                    if (withCurrentNodeG <= neighbor->g()) {
                        neighbor->setPreviousNode(currentNode);
                        neighbor->setG(withCurrentNodeG);
                        qSort(m_openList.begin(), m_openList.end(), openListLessThan);
                    }
                } else {
                    // calculate/set g and h value
                    neighbor->setG(withCurrentNodeG);
                    neighbor->setH(calculateDistance(neighbor, m_goalNode));
                    // set the parent node
                    neighbor->setPreviousNode(currentNode);
                    if (m_showAlgorithm)
                        neighbor->setColor(QColor(255,255,255));

                    insertInOpenList(neighbor);
                }
            }
        }
    }
}

bool openListLessThan(Node *a, Node *b)
{
    return a->f() < b->f();
}


