from numpy import random
import time

class Vector:
    def __init__(self, colection) -> None:
        self._v = []
        for x in colection:
            self._v.append(x)

    def getData(self):
        return self._v
    
    def __str__(self) -> str:
        return str(self._v)
    
    def __getitem__(self, key):
        return self._v[key]
    
    def __setitem__(self, key, value):
        self._v[key] = value

    def FindMaxAndSwap(self, right):
        # Implementation of FindMaxAndSwap in O(n)
        mx = right
        for j in range(right):
            if self[j] > self[mx]:
                mx = j
        if mx != right:
            self[right], self[mx] = self[mx], self[right]


class Heap:
    def __init__(self, colection) -> None:
        self._v = []
        for x in colection:
            self._v.append(x)

        # Make the list a maxheap
        N = len(self._v)
        for i in range(N // 2 - 1, -1, -1):
            self.heapify(i, N)

    def getData(self):
        return self._v
    
    def __str__(self):
        return str(self._v)
    
    def __getitem__(self, key):
        return self._v[key]
    
    def heapify(self, root, N):
        mx = root
        l = 2 * root + 1
        r = 2 * root + 2

        # Verify that left child exists and is maximum
        if l < N and self[mx] < self[l] :
            mx = l

        # Verify that right child exists and is maximum
        if r < N and self[mx] < self[r] :
            mx = r

        if mx != root:
            self._v[mx], self._v[root] = self._v[root], self._v[mx]
            self.heapify(mx, N)
    
    def FindMaxAndSwap(self, right):
        # The maximum element is swapped in O(1)
        self._v[0], self._v[right] = self._v[right], self._v[0]
        # However, we need to call heapify() in O(log n)
        self.heapify(0, right)


def Sort(v : Vector | Heap) -> None:
    n = len(v.getData())
    for i in range(n-1, 0, -1):
        v.FindMaxAndSwap(i)


if __name__ == '__main__':
    n = 20000
    #print(vector)
    #print(heap)
    
    for i in range(5):
        print(f"Test {i}:")
        perm = random.permutation(n)
        print(f"Generated permutation with {n} elements.")

        ts = time.perf_counter()
        vector = Vector(perm)
        Sort(vector)
        tf = time.perf_counter()
        print(f"Sort on vector performed in {tf - ts:0.4f} seconds.")

        ts = time.perf_counter()
        heap = Heap(perm)
        Sort(heap)
        tf = time.perf_counter()
        print(f"Sort on heap performed in {tf - ts:0.4f} seconds.")
        print()

    #print(vector)
    #print(heap)
