#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Point
{
    double x, y;
};

struct Segment
{
    Point p1, p2;
};

struct AVLNode
{
    Segment segment;
    AVLNode* left;
    AVLNode* right;
    int height;
};

bool foundAny = false;

AVLNode* createNode(Segment segment)
{
    AVLNode* newNode = new AVLNode;
    newNode->segment = segment;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

int getHeight(AVLNode* node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(AVLNode* node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(AVLNode* node)
{
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = max(leftHeight, rightHeight) + 1;
}

AVLNode* rotateRight(AVLNode* node)
{
    AVLNode* leftChild = node->left;
    AVLNode* leftRightChild = leftChild->right;

    leftChild->right = node;
    node->left = leftRightChild;

    updateHeight(node);
    updateHeight(leftChild);

    return leftChild;
}

AVLNode* rotateLeft(AVLNode* node)
{
    AVLNode* rightChild = node->right;
    AVLNode* rightLeftChild = rightChild->left;

    rightChild->left = node;
    node->right = rightLeftChild;

    updateHeight(node);
    updateHeight(rightChild);

    return rightChild;
}

AVLNode* insertSegment(AVLNode* root, Segment segment)
{
    if (root == nullptr)
        return createNode(segment);

    if (segment.p1.x < root->segment.p1.x)
        root->left = insertSegment(root->left, segment);
    else
        root->right = insertSegment(root->right, segment);

    updateHeight(root);

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && segment.p1.x < root->left->segment.p1.x)
        return rotateRight(root);

    // Right Right Case
    if (balance < -1 && segment.p1.x > root->right->segment.p1.x)
        return rotateLeft(root);

    // Left Right Case
    if (balance > 1 && segment.p1.x > root->left->segment.p1.x) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left Case
    if (balance < -1 && segment.p1.x < root->right->segment.p1.x) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

bool areCollinear(Point p1, Point p2, Point p3)
{
    double area = (p1.x * (p2.y - p3.y) +
                   p2.x * (p3.y - p1.y) +
                   p3.x * (p1.y - p2.y));
    return (area == 0);
}

void doSegmentsIntersect(Segment seg1, Segment seg2)
{
    Point p1 = seg1.p1, p2 = seg1.p2;
    Point p3 = seg2.p1, p4 = seg2.p2;

    if (p1.x == p3.x && p1.y == p3.y || p1.x == p4.x && p1.y == p4.y ||
        p2.x == p3.x && p2.y == p3.y || p2.x == p4.x && p2.y == p4.y)
        return;

    if (areCollinear(p1, p2, p3) || areCollinear(p1, p2, p4) ||
        areCollinear(p3, p4, p1) || areCollinear(p3, p4, p2)) {
        if (p1.x >= min(p3.x, p4.x) && p1.x <= max(p3.x, p4.x) &&
            p1.y >= min(p3.y, p4.y) && p1.y <= max(p3.y, p4.y))
            return;
        if (p2.x >= min(p3.x, p4.x) && p2.x <= max(p3.x, p4.x) &&
            p2.y >= min(p3.y, p4.y) && p2.y <= max(p3.y, p4.y))
            return;
        if (p3.x >= min(p1.x, p2.x) && p3.x <= max(p1.x, p2.x) &&
            p3.y >= min(p1.y, p2.y) && p3.y <= max(p1.y, p2.y))
            return;
        if (p4.x >= min(p1.x, p2.x) && p4.x <= max(p1.x, p2.x) &&
            p4.y >= min(p1.y, p2.y) && p4.y <= max(p1.y, p2.y))
            return;
    }

    double slope1 = (p2.y - p1.y) / (p2.x - p1.x);
    double slope2 = (p4.y - p3.y) / (p4.x - p3.x);

    if (slope1 == slope2)
        return;

    double intersectX = (p3.y - p1.y + slope1 * p1.x - slope2 * p3.x) / (slope1 - slope2);
    double intersectY = p1.y + slope1 * (intersectX - p1.x);

    if (intersectX >= min(p1.x, p2.x) && intersectX <= max(p1.x, p2.x) &&
        intersectY >= min(p1.y, p2.y) && intersectY <= max(p1.y, p2.y) &&
        intersectX >= min(p3.x, p4.x) && intersectX <= max(p3.x, p4.x) &&
        intersectY >= min(p3.y, p4.y) && intersectY <= max(p3.y, p4.y)) {
        cout << "Intersection Point: (" << intersectX << ", " << intersectY << ")" << endl;
        foundAny = true;
        return;
    }
}

void findIntersections(AVLNode* root) {
    if (root == nullptr)
        return;

    if (root->left != nullptr) {
        doSegmentsIntersect(root->segment, root->left->segment);
    }

    if (root->right != nullptr) {
        doSegmentsIntersect(root->segment, root->right->segment);
    }

    findIntersections(root->left);
    findIntersections(root->right);
}

int main()
{
    ifstream in("input.txt");
    int n;
    in >> n;
    AVLNode* root = nullptr;
    for (int i = 0; i < n; i++)
    {
        Segment segment;
        in >> segment.p1.x;
        in >> segment.p1.y;
        in >> segment.p2.x;
        in >> segment.p2.y;
        root = insertSegment(root, segment);
    }
    findIntersections(root);
    if(!foundAny)
        cout << "No intersections found.";
    return 0;
}
