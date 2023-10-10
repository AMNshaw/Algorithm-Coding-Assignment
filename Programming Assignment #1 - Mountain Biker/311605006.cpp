// A divide and conquer program in C++ to find the smallest distance from a 
// given set of points. 

#include <iostream> 
#include <float.h> 
#include <stdlib.h> 
#include <math.h> 
using namespace std; 

struct Point
{
    float x, y;
};
 
int xCompare(const void *a, const void *b)
{
	const Point *p1 = (const Point*)a;
	const Point *p2 = (const Point*)b;
	return p1->x - p2->x;
}
int yCompare(const void *a, const void *b)
{
	const Point *p1 = (const Point*)a;
	const Point *p2 = (const Point*)b;
	return p1->y - p2->y;
}
float squDist(Point &a, Point &b)
{
	return float(a.x - b.x)*(a.x - b.x) + float(a.y - b.y)*(a.y - b.y);
}
 
float bruteSolve(Point P[], int n)
{
	float clo_dist = FLT_MAX;
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			float t = squDist(P[i], P[j]);
			if (clo_dist > t)  clo_dist = t;
		}
	}
	return clo_dist;
}

float midClosest(Point P[], int n, float d)
{
	qsort(P, n, sizeof(Point), yCompare);
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n && P[j].y - P[i].y < d; j++)
		{
			float t = squDist(P[j], P[i]);
			if (t < d) d = t;
		}
	}
	return d;
}
 
float squClosest(Point P[], int n)
{
	if (n <= 3) return bruteSolve(P, n);
	int m = n>>1;;
 
	float ld = squClosest(P, m);
	float rd = squClosest(P+m, n-m);
	float d = ld < rd? ld:rd;
 
	Point *strip = new Point[n];
	int j = 0;
	for (int i = 0; i < n; i++)
		if (abs(P[i].x - P[m].x) < d) strip[j++] = P[i];
 
	float t = midClosest(strip, j, d);
	return d < t? d:t;
}
 
float closest(Point P[], int n)
{
	qsort(P, n, sizeof(Point), xCompare);
	return sqrt(squClosest(P, n));
}

// Driver program to test above functions 
int main() 
{ 
    int test_cases = 0;
    int locationNum = 0;
    float x, y;
    Point* P;
    float* CP;
    cin >> test_cases;
    CP = new float[test_cases];
    for(int i = 0; i < test_cases; i++)
    {
        cin >> locationNum;
        P = new Point[locationNum];
        for(int j = 0; j < locationNum; j++)
        {
            cin >> x >> y;
            P[j] = Point{x, y};
        }
        CP[i] = closest(P, locationNum);
    }
    for(int i = 0; i < test_cases; i++)
        cout << CP[i] << endl;

    return 0;
}