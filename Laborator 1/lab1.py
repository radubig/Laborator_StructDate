# Comparatie Selection Sort vs Heapsort pt o permutare aleatoare

import numpy;

def selection_sort(v: list):
    n = len(v)
    for i in range(n-1):
        mn = i
        for j in range(i+1, n):
            if v[j] < v[mn]:
                mn = j
        v[mn], v[i] = v[i], v[mn]


def heapify(v: list, ind: int, lmax: int):
    fr_st = ind*2+1
    fr_dr = ind*2+2
    val_st = v[fr_st] if fr_st <= lmax else lmax+1
    val_dr = v[fr_dr] if fr_dr <= lmax else lmax+1
    val_mx = min(val_st, val_dr)
    fr_mx = fr_st if val_st >= val_dr else fr_dr
    if v[ind] > val_mx:
        v[ind], v[fr_mx] = v[fr_mx], v[ind]
        heapify(v, fr_mx, lmax)


def heapsort(v: list):
    n = len(v)
    # Build max heap
    for i in range(n//2-1, -1, -1):
        heapify(v, i, n-1)
    # Actual sorting by constantly removing the maximum element
    for i in range(n-1, 0, -1):
        v[0], v[i] = v[i], v[0]
        heapify(v, 0, i-1)


if __name__ == '__main__':
    lst1 = numpy.random.permutation(8)
    print("sir initial:")
    print(lst1)
    lst2 = [x for x in lst1]
    selection_sort(lst1)
    print("selection sort:")
    print(lst1)
    print("\nheap sort:")
    heapsort(lst2)
    print(lst2)