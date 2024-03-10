#include <iostream>
#include <vector>

struct avltree {
    int key;

    int height;
    struct avltree* left;
    struct avltree* right;
};

void avltree_free(struct avltree* tree)
{
    if (tree == NULL)
        return;
    avltree_free(tree->left);
    avltree_free(tree->right);
    free(tree);
}

struct avltree* avltree_lookup(struct avltree* tree, int key)
{
    while (tree != NULL) {
        if (key == tree->key) {
            return tree;
        } else if (key < tree->key) {
            tree = tree->left;
        } else {
            tree = tree->right;
        }
    }
    return tree;
}

struct avltree* avltree_create(int key)
{
    struct avltree* node;
    node = (struct avltree*)malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }
    return node;
}

int avltree_height(struct avltree* tree)
{
    return (tree != NULL) ? tree->height : -1;
}

int avltree_balance(struct avltree* tree)
{
    return avltree_height(tree->left) - avltree_height(tree->right);
}

struct avltree* avltree_right_rotate(struct avltree* tree)
{
    struct avltree* left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree->height = std::max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    left->height = std::max(avltree_height(left->left), tree->height) + 1;
    return left;
}

struct avltree* avltree_left_rotate(struct avltree* tree)
{
    struct avltree* right;
    right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->height = std::max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    right->height = std::max(avltree_height(right->right), tree->height) + 1;
    return right;
}

struct avltree* avltree_leftright_rotate(struct avltree* tree)
{
    tree->left = avltree_left_rotate(tree->left);
    return avltree_right_rotate(tree);
}

struct avltree* avltree_rightleft_rotate(struct avltree* tree)
{
    tree->right = avltree_right_rotate(tree->right);
    return avltree_left_rotate(tree);
}

struct avltree* avltree_add(struct avltree* tree, int key)
{
    if (tree == NULL) {
        return avltree_create(key);
    }
    if (key < tree->key) {
        /* Insert into left subtree */
        tree->left = avltree_add(tree->left, key);
        if (avltree_height(tree->left) - avltree_height(tree->right) == 2) {
            /* Subtree is unbalanced */
            if (key < tree->left->key) {
                /* Left left case */
                tree = avltree_right_rotate(tree);
            } else {
                /* Left right case */
                tree = avltree_leftright_rotate(tree);
            }
        }
    } else if (key > tree->key) {
        /* Insert into right subtree */
        tree->right = avltree_add(tree->right, key);
        if (avltree_height(tree->right) - avltree_height(tree->left) == 2) {
            /* Subtree is unbalanced */
            if (key > tree->right->key) {
                /* Right right case */
                tree = avltree_left_rotate(tree);
            } else {
                /* Right left case */
                tree = avltree_rightleft_rotate(tree);
            }
        }
    }

    tree->height = std::max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    return tree;
}

void print(avltree* root, int level)
{
    if (!root)
        return;

    level++;
    print(root->left, level);
    std::cout << root->key << ' ' << level - 1 << '\n';
    print(root->right, level);
}

int min(avltree* tree)
{
    if (!tree)
        return -1;

    while (tree->left) {
        tree = tree->left;
    }

    return tree->key;
}

int next(avltree* root, int k)
{
    std::vector<avltree*> parents;
    avltree* parent = NULL;
    if (!root)
        return -1;

    while (root) {
        if (root->key == k)
            break;
        else if (root->key > k) {
            parent = root;
            parents.push_back(root);
            root = root->left;
        } else {
            parent = root;
            parents.push_back(root);
            root = root->right;
        }
    }
    if (root) {
        return root->key;
    }

    if (parent == NULL) {
        return -1;
    }

    size_t n = parents.size();
    if (!root) {
        if (parent->right)
            return std::min(parent->key, min(parent->right));
        else if (parent->key > k)
            return parent->key;

        root = parent;
        n--;
    }

    int next_min = -1;
    for (int i = n - 1; i >= 0; i--) {
        parent = parents[i];
        if (parent->left && parent->left == root) {
            if (parent->right)
                return std::min(parent->key, min(parent->right));
            return parent->key;
        }

        if (parent->right && parent->right == root)
            root = parent;
        else
            return parent->key;
    }

    return next_min;
}

int main()
{
    size_t n;
    std::cin >> n;
    char action;
    int num;
    std::cin >> action;
    std::cin >> num;

    auto tree = avltree_create(num);
    bool is_quetion = false;

    int next_k = -1;

    for (size_t i = 0; i < n - 1; i++) {
        std::cin >> action;
        std::cin >> num;

        if (action == '+') {
            if (is_quetion) {
                tree = avltree_add(tree, (num + next_k) % 1000000000);
                is_quetion = false;
            } else
                tree = avltree_add(tree, num);
        } else {
            is_quetion = true;
            next_k = next(tree, num);
            std::cout << next_k << '\n';
        }
    }

    return 0;
}