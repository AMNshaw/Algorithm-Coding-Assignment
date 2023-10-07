#include <cmath>
#include <iostream>
#include <vector>
#include <cfloat>

using namespace std;

void swap(float** pt1, float** pt2)
{
    float* temp = *pt1;
    *pt1 = *pt2;
    *pt2 = temp;
}

int partition(float** pt, int low, int high, int axis)
{
    float pivot = pt[high][axis];
    int i = low - 1;
    for(int j = low; j<high; j++)
    {
        if(pt[j][axis] < pivot)
        {
            i++;
            swap(&pt[i], &pt[j]);
        }
    }

    swap(&pt[i + 1], &pt[high]);
    return i + 1;
}

void quickSort(float** pt, int low, int high, int axis)
{
    if(low < high)
    {
        int pivotIndex = partition(pt, low, high, axis);
        quickSort(pt, low, pivotIndex-1, axis);
        quickSort(pt, pivotIndex+1, high, axis);
    }
}

void releaseMem(float ** pts, int num)
{
    for(int j = 0; j < num; j++)
            delete[] pts[j];
    delete[] pts;
}

float computeDistance(float* pt1, float* pt2)
{
    return sqrt(pow(pt1[0] - pt2[0], 2) + pow(pt1[1] - pt2[1], 2));
}

float bruteForce(float** pt, int n)
{
    float shortest = FLT_MAX;
    float dist = 0;
    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            dist = computeDistance(pt[i], pt[j]);
            if(dist < shortest)
                shortest = dist;
        }
    }
    return shortest;
}

float stripClosest(float** s, int num, float delta)
{
    quickSort(s, 0, num-1, 1);
    float min = delta;
    for(int i = 0; i < num-1; i++)
        for(int j = i+1; j < num; j++)
        {
            float dist = computeDistance(s[i], s[j]);
            if(dist < min)
                min = dist;
        }
    return min;
}

float devideTillBase(float** pt, int n)
{
    if(n <= 3)
        return bruteForce(pt, n);
    int mid = n/2;
    float* midPt = pt[mid];
    float deltaL = devideTillBase(pt, mid);
    float deltaR = devideTillBase(pt + mid, n - mid);
    float delta = min(deltaL, deltaR);
    
    float** s = new float*[n];
    for(int i = 0; i < 2; i++)
        s[i] = new float[n];

    int stripNum = 0;
    for(int i=0; i < n; i++)
        if(abs(pt[i][0] - midPt[0]) < delta)
        {
            s[stripNum] = pt[i];
            stripNum++;
        }        
    
    float min = stripClosest(s, stripNum, delta);
    releaseMem(s, n);

    return min;
}


int main()
{
    int test_cases = 0;
    int locationNum = 0;
    vector<float> min;
    cin >> test_cases;
    for(int i = 0; i < test_cases; i++)
    {
        cin >> locationNum;
        float **pts = new float*[locationNum];
        for(int k = 0; k < locationNum; k++)
            pts[k] = new float[2];
        for(int j = 0; j < locationNum; j++)
            cin >> pts[j][0] >> pts[j][1];

        // cout << endl;
        // for(int j = 0; j<locationNum; j++)
        //     cout << pts[j][0] << ", " << pts[j][1] << endl;
        quickSort(pts, 0, locationNum-1, 0);
        // cout << endl;
        // for(int j = 0; j<locationNum; j++)
        //     cout << pts[j][0] << ", " << pts[j][1] << endl;
        min.push_back(devideTillBase(pts, locationNum));
        //std::cout << "min: " << devideTillBase(pts, locationNum) << endl;
        //releaseMem(pts, locationNum);        
    }
    for(int i = 0; i < test_cases; i++)
        cout << min[i] << endl;

    return 0;
}


