#include <stdlib.h>
#include <math.h>
#include <iostream>

struct Point
{
    float x;
    float y;
};

float compareX(const void* p1, const void* p2)
{
    Point *pt1;
    Point *pt2;
    pt1 = (Point*)p1;
    pt2 = (Point*)p2;
    return (pt1->x - pt2->x);
}
float compareY(const void* p1, const void* p2)
{
    Point *pt1;
    Point *pt2;
    pt1 = (Point*)p1;
    pt2 = (Point*)p2;
    return (pt1->y - pt2->y);
}

float computeDist(Point pt1, Point pt2)
{
    return sqrt(pow((pt1->x - pt2->x), 2) + pow((pt1->y - pt2->y), 2));
}

float bruteForce(Point* pts, int num)
{
    float min = 999999;
    for(int i = 0; i < num-1; i++)
        for(int j = i+1; j< num; j++)
            if(dist(pts[i], pts[j]) < min)
                min = dist(pts[i], pts[j]);
    
    return min;
}

float devideTillBase(Point& pts, int n)
{
   if(n <= 3)
        return bruteForce(pts, n);

    int mid = n/2;
    Point midPt = pts[mid];

    float delta_left = devideTillBase(pts, mid);
    float delta_right = devideTillBase(pts+mid, n - mid);
    float delta = (delta_left < delta_right)? delta_left:delta_right;

    
}