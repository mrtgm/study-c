#include <stdio.h>
#include <stdlib.h>

// - 2分木は次数（枝分かれする数）が2の木
// - 2分木は左の子<自分自身<右の子が成り立つ
//  - 与えられた値が自分自身より大きければ右の子に、小さければ左の子に追加していく、だけ
//  - なので、通りがけ順で木を巡回すると、昇順になる

typedef struct node
{
    double item;
    struct node *left;
    struct node *right;
} Node;

static Node *make_node(double x)
{
    Node *node = malloc(sizeof(Node));
    if (node != NULL)
    {
        node->item = x;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

// 値と頂点ノードを与え、値と一致するノードがあるか探索する　あれば 0
static int search_node(double x, Node *node)
{
    while (node != NULL)
    {
        if (node->item == x)
            return 0;
        else if (x < node->item)
            node = node->left; // node を左方向の木のポインタで置き換える
                               // 二分木は節の左方向に小さい値、右方向に大きい値を配置するデータ構造
        else
            node = node->right;
    }
    return 1;
}

// 再帰的にノードをリーフまで探索し、値を追加する
static Node *insert_node(double x, Node *node)
{
    if (node == NULL)
        return make_node(x);
    else if (x < node->item)
    {
        node->left = insert_node(x, node->left);
    }
    else if (x > node->item)
    {
        node->right = insert_node(x, node->right);
    }
    return node;
}

// 頂点ノードを与えて、最小値を返す
static double search_min(Node *node)
{
    while (node->left != NULL)
        node = node->left;
    return node->item;
}

// ノードを与えて、左方向に再帰的に探索　
// それ以上左方向にノードを辿れなくなったらその節をその木の最小値と見なし、節の右方向ノードを一時変数に確保しつつ削除
static Node *delete_min(Node *node)
{
    if (node->left == NULL)
    {
        Node *temp = node->right;
        free(node);
        return temp;
    }
    node->left = delete_min(node->left);
    return node;
}

static Node *delete_node(double x, Node *node)
{

    if (node == NULL) // 木が空の場合は NULL
        return NULL;
    if (x == node->item) // 値が一致する場合は削除処理に移行
    {
        // 子が一つだけの場合
        if (node->left == NULL) // 左方向に子がない場合、その節を削除　右方向の子を返却
        {
            Node *temp = node->right;
            free(node);
            return temp;
        }
        if (node->right == NULL) // 左方向に子があり、右方向に子がない場合、その節を削除　左方向の子を返却
        {
            Node *temp = node->left;
            free(node);
            return temp;
        }

        // 左方向、右方向にも子がある場合
        node->item = search_min(node->right);  // 右方向の子から最小値の子を探し、自分自身の値とする
        node->right = delete_min(node->right); // 右方向の子から最小値の子を削除
    }
    else if (x < node->item)                       // 値が小さい場合は左方向に探索
        node->left = delete_node(x, node->left);   // 親の left に temp が代入される
    else                                           // 値が大きい場合は右方向に探索
        node->right = delete_node(x, node->right); // 親の right に temp が代入される

    return node; // 自分自身を返しながら再帰から抜ける
}

// 木の巡回　すべての要素を辿る方法
// 通りがけ順
static void foreach_node(void (*func)(double), Node *node)
{
    if (node != NULL)
    {
        foreach_node(func, node->left);  // 左方向に再帰的に探索
        func(node->item);                // 限界まで左方向に探索したら、その節を処理
        foreach_node(func, node->right); // 右方向に再帰的に探索
    }
}
// 行きがけ順
static void foreach_node_v2(void (*func)(double), Node *node)
{
    if (node != NULL)
    {
        func(node->item);
        foreach_node_v2(func, node->left);
        foreach_node_v2(func, node->right);
    }
}
// 帰りがけ順
static void foreach_node_v3(void (*func)(double), Node *node)
{
    if (node != NULL)
    {
        foreach_node_v3(func, node->left);
        foreach_node_v3(func, node->right);
        func(node->item);
    }
}

typedef struct
{
    Node *root;
} Tree;

Tree *make_tree(void)
{
    Tree *tree = malloc(sizeof(Tree));
    if (tree != NULL)
    {
        tree->root = NULL;
    }
    return tree;
}

int search_tree(double x, Tree *tree)
{
    return search_node(x, tree->root);
}

void insert_tree(double x, Tree *tree)
{
    tree->root = insert_node(x, tree->root);
}

void delete_tree(double x, Tree *tree)
{
    printf("%lf:before\n", tree->root->item);
    tree->root = delete_node(x, tree->root);
    printf("%lf:after\n", tree->root->item);
}

static void destroy_node(Node *node)
{
    if (node != NULL)
    {
        destroy_node(node->left);
        destroy_node(node->right);
        free(node);
    }
}

void destroy_tree(Tree *tree)
{
    destroy_node(tree->root);
    free(tree);
}

void foreach_tree(void (*func)(double), Tree *tree)
{

    foreach_node_v2(func, tree->root);
}

void print_item(double x)
{
    printf("%.3f ", x);
}

void print_tree(Tree *tree)
{
    foreach_tree(print_item, tree);
    printf("\n");
}

#define N 10

int main()
{
    double buff[N] = {5,
                      6,
                      4,
                      7,
                      3,
                      8,
                      2,
                      9,
                      1,
                      0};

    Tree *tree = make_tree();
    for (int i = 0; i < N; i++)
    {
        insert_tree(buff[i], tree);
        print_tree(tree);
    }

    delete_tree((double)8, tree);
    delete_tree((double)5, tree);
    print_tree(tree);

    return 0;
}
