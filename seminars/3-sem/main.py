import random
import copy


class TreapNode:
    def __init__(self, x):
        self.x = x
        self.y = random.random()
        self.left = None
        self.right = None


class Treap:
    @staticmethod
    def add(tree: TreapNode, node: TreapNode):
        if tree is None:
            return node

        t1, t2 = Treap.split(tree, node.x)
        t1 = Treap.merge(t1, node)
        t1 = Treap.merge(t1, t2)
        return t1

    @staticmethod
    def split(origin_tree: TreapNode, x: int):
        tree = copy.deepcopy(origin_tree)

        if tree is None:
            return None, None

        if tree.x < x:
            tree1, tree2 = Treap.split(tree.right, x)
            tree.right = tree1
            return tree, tree2
        else:
            tree1, tree2 = Treap.split(tree.left, x)
            tree.left = tree2
            return tree1, tree

    @staticmethod
    def merge(tree1: TreapNode, tree2: TreapNode) -> TreapNode:
        if tree1 is None:
            return tree2
        if tree2 is None:
            return tree1

        if tree1.y > tree2.y:
            tree1.right = Treap.merge(tree1.right, tree2)
            return tree1
        else:
            tree2.left = Treap.merge(tree1, tree2.left)
            return tree2

    @staticmethod
    def find(tree: TreapNode, x: int) -> TreapNode:
        while tree is not None:
            if x == tree.x:
                return tree
            elif x < tree.x:
                tree = tree.left
            else:
                tree = tree.right

        return tree

    @staticmethod
    def remove(tree: TreapNode, x: int) -> TreapNode:
        node = tree
        parent = None

        while node is not None:
            if x == node.x:
                break
            elif x < node.x:
                parent = node
                node = node.left
            else:
                parent = node
                node = node.right

        if node is None:
            return tree

        new_node = Treap.merge(node.left, node.right)
        if parent is None:
            return new_node

        if parent.left == node:
            parent.left = new_node
        else:
            parent.right = new_node

        return tree

    @staticmethod
    def output(tree: TreapNode, level: int):
        if tree is None:
            return

        level += 1
        Treap.output(tree.left, level)
        print(f"({tree.x}, {tree.y}) on level {level}")
        Treap.output(tree.right, level)

    @staticmethod
    def to_vec(tree: TreapNode) -> list:
        l = []
        if (tree is None):
            return []

        l = l + Treap.to_vec(tree.left)
        l.append(tree.x)
        l = l + Treap.to_vec(tree.right)

        return l


if __name__ == '__main__':
    root = TreapNode(1)
    for i in range(1, 25):
        root = Treap.add(root, TreapNode(i))
    x = 12

    t1, t2 = Treap.split(root, x)
    t2 = Treap.remove(t2, x)
    Treap.output(t2, 0)

    next_k = Treap.to_vec(t2)
    print('\n', next_k)
