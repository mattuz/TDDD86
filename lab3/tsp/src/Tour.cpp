/*
 * This file contains the implementation of the Tour class.
 * See Tour.h for comments about each member.
 */

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour(Point a, Point b, Point c, Point d)
{
    Node* nodeA = new Node(a,nullptr);
    Node* nodeB = new Node(b,nullptr);
    Node* nodeC = new Node(c,nullptr);
    Node* nodeD = new Node(d,nullptr);


    nodeA->next = nodeB;
    nodeB->next = nodeC;
    nodeC->next = nodeD;
    nodeD->next = nodeA;

    m_front = nodeA;
}

Tour::Tour()
{
}

Tour::~Tour()
{
    if(m_front->next != nullptr){

        m_current = m_front->next;
        Node* first = m_current->next;


        while(first != m_front)
        {
            delete m_current;
            m_current = first;
            if(first != m_front)
            {
                first = m_current->next;
            }
        }

        delete m_current;
        delete m_front;
    }
}

void Tour::show()
{
    if(m_front != nullptr)
    {
        bool lastnode = false;
        m_current = m_front;

        while(!lastnode){
            cout <<  m_current->point << endl;
            if(m_current->next == m_front){
                lastnode = true;
            }
            m_current = m_current->next;
        }
    }
}

void Tour::draw(QGraphicsScene *scene)
{
    if(m_front != nullptr)
    {
        bool lastnode = false;
        m_current = m_front;

        while(!lastnode){
            m_current->point.drawTo(m_current->next->point, scene);
            if(m_current->next == m_front){
                lastnode = true;
            }
            m_current = m_current->next;
        }
    }
}

int Tour::size()
{
    int size = 0;
    if(m_front != nullptr)
    {
        bool lastnode = false;
        m_current = m_front;

        while(!lastnode){
            size++;
            if(m_current->next == m_front){
                lastnode = true;
            }
            m_current = m_current->next;
        }
    }
    return size;
}

double Tour::distance()
{
    double distance = 0;
    if(m_front != nullptr)
    {
        bool lastnode = false;
        m_current = m_front;

        while(!lastnode){
            distance += m_current->point.distanceTo(m_current->next->point);
            if(m_current->next == m_front){
                lastnode = true;
            }
            m_current = m_current->next;
        }
    }
    return distance;
}

void Tour::insertNearest(const Point p)
{
    double shortestRoute = -1;
    Node* closestPoint = nullptr;
    Node* nodeP = new Node(p, nullptr);

    if(m_front != nullptr)
    {
        bool lastnode = false;
        m_current = m_front;

        while(!lastnode){
            if(shortestRoute == -1 || m_current->point.distanceTo(p) < shortestRoute)
            {
                shortestRoute = m_current->point.distanceTo(p);             //Lästa i FAQ att vi typ inte ska använda distanceTo, blir dubbelloop.
                closestPoint = m_current;
            }

            if(m_current->next == m_front)
            {
                lastnode = true;
            }
            m_current = m_current->next;
        }
        nodeP->next = closestPoint->next;
        closestPoint->next = nodeP;
    }
    else
    {
        m_front = nodeP;
        nodeP->next = nodeP;
    }


}

void Tour::insertSmallest(const Point p)
{
    double smallestIncrease = -1;
    Node* closestPoint = nullptr;
    Node* nodeP = new Node(p, nullptr);

    if(m_front != nullptr)
    {
        bool lastnode = false;
        m_current = m_front;

        while(!lastnode){
            double currentToP = m_current->point.distanceTo(p);
            double pToNext = m_current->next->point.distanceTo(p);
            double currentToNext = m_current->point.distanceTo(m_current->next->point);
            double increase = pToNext + currentToP - currentToNext;

            if(smallestIncrease == -1 || increase < smallestIncrease)
            {
                smallestIncrease = increase;
                closestPoint = m_current;
            }

            if(m_current->next == m_front)
            {
                lastnode = true;
            }
            m_current = m_current->next;
        }
        nodeP->next = closestPoint->next;
        closestPoint->next = nodeP;
    }
    else
    {
        m_front = nodeP;
        nodeP->next = nodeP;
    }


}
