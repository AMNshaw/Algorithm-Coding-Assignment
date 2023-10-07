import math


class App:

    def __init__(self, number):
        self.num = number
        self.coordinate = [[0, 0] for _ in range(self.num)]
    
    def inputCoordinate(self):
        for i in range(self.num):
            input_string = input()
            try:
                self.coordinate[i][0] = float(input_string.split()[0])
                self.coordinate[i][1] = float(input_string.split()[1])
            except ValueError:
                print("Invalid input")
        # print("coordinates:\n", self.coordinate)
        # print(computeDistance(self.coordinate[0], self.coordinate[1]))

    def devideTillBase(self, pt, n):
        if n <= 3:
            return bruteForce(pt, n)
        mid = n//2
        midPt = pt[mid]
        deltaL = self.devideTillBase(pt, mid)
        deltaR = self.devideTillBase(pt[mid:], n-mid)
        delta = min(deltaL, deltaR)
        s = []
        for i in range(n):
            if abs(pt[i][0] - midPt[0]) < delta:
                s.append(pt[i])
        minDist = self.stripClosest(s, delta)
        return minDist

    def stripClosest(self, s, delta):
        min = delta
        stripSize = len(s)
        quickSort(s, 0, stripSize-1, 1)
        for i in range(stripSize):
            for j in range(i+1, stripSize):
                if(abs(s[i][1] - s[j][1]) >= delta):
                    break
                dist = computeDistance(s[i], s[j])
                if dist < delta:
                    min = dist
        return min

def bruteForce(pt, n):
    shortest = float("inf")
    for i in range(n - 1):
        for j in range(i+1, n):
            distance = computeDistance(pt[i], pt[j])
            if distance < shortest:
                shortest = distance
    return shortest


def partition(pt, low, high, axis):

        pivot = pt[high][axis]
        
        i = low - 1
        for j in range(low, high):
            if pt[j][axis] < pivot:
                i = i+1
                (pt[i], pt[j]) = (pt[j], pt[i])

        (pt[i+1], pt[high]) = (pt[high], pt[i + 1])

        return i+1

def quickSort(pt, low, high, axis):

    if low < high:
        p = partition(pt, low, high, axis)
        quickSort(pt, low, p - 1, axis)
        quickSort(pt, p+1, high, axis)

def computeDistance(pt1, pt2):
    return math.sqrt((pt1[0] - pt2[0]) ** 2 + (pt1[1] - pt2[1]) ** 2)

def main():
    testNum = int(input())
    shortestArr = []
    for i in range(testNum):
        ptNum = int(input())
        app = App(ptNum)
        app.inputCoordinate()
        quickSort(app.coordinate, 0, ptNum-1, 0)
        shortestArr.append(app.devideTillBase(app.coordinate, ptNum))
        #shortestArr.append(bruteForce(app.coordinate, ptNum))
    for i in range(testNum):
        print(shortestArr[i])
    
if __name__ == "__main__":
    main()