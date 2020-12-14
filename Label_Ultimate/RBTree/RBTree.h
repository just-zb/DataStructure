enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    int data;
    int color;
    Node *left, *right, *parent;

    explicit Node(int);
};

class RBTree
{
    private:
        Node *root;
    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRBTree(Node *&);
        void fixDeleteRBTree(Node *&);
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node *minValueNode(Node *&);
        Node *maxValueNode(Node *&);
        Node* insertBST(Node *&, Node *&);
        Node* deleteBST(Node *&, int);
        Node* Find(Node*&,int);
        int getBlackHeight(Node *);
    public:
        RBTree();
        void insertValue(int);
        void deleteValue(int);
        int find(int);
        void merge(RBTree);
};
