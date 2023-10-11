import math

def closest(points):
    Px = sorted(points, key = lambda point: point[0])
    Py = sorted(points, key = lambda point: point[1])
    return recursion(Px, Py)

def computeDistance(pt1, pt2):
    return math.sqrt((pt1[0] - pt2[0]) ** 2 + (pt1[1] - pt2[1]) ** 2)

def recursion(Px, Py):
    n = len(Px)
    if(n <= 3):
        return bruteForce(Px)
    else:
        midPt = Px[n//2]
        Lx = Px[:n//2]
        Rx = Px[n//2:]
        Ly = []
        Ry = []
        for pt in Py:
            if (pt[0] <= midPt[0]):
                Ly.append(pt)
            else:
                Ry.append(pt)

        
        delta_L = recursion(Lx, Ly)
        delta_R = recursion(Rx, Ry)
        delta = min(delta_L, delta_R)
        s = []
        for pt in Py:
            if(abs(pt[0] - midPt[0]) < delta):
                s.append(pt)
        
        delta = stripClosest(s, delta)

        return delta

def stripClosest(s, delta):
    stripSize = len(s)
    for i in range(stripSize):
            for j in range(i+1, min(i+7, stripSize)):
                if(abs(s[i][1] - s[j][1]) < delta):
                    d = computeDistance(s[i], s[j])
                    if(d < delta):
                        delta = d
    return delta

def bruteForce(P):
    n = len(P)
    shortest = float("inf")
    for i in range(n - 1):
        for j in range(i+1, n):
            distance = computeDistance(P[i], P[j])
            if distance < shortest:
                shortest = distance
    return shortest

if __name__ == "__main__":
    testNum = int(input())
    shortestArr = []
    for i in range(testNum):
        ptNum = int(input())
        P = [[0, 0] for _ in range(ptNum)]
        for i in range(ptNum):
            input_string = input()
            try:
                P[i][0] = float(input_string.split()[0])
                P[i][1] = float(input_string.split()[1])
            except ValueError:
                print("Invalid input")
        shortestArr.append(closest(P))
    for i in range(testNum):
        print(shortestArr[i])