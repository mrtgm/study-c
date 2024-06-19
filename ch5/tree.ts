class TNode {
  item: number;
  right: TNode | null;
  left: TNode | null;

  constructor({ item, right, left }: { item: number; right: TNode | null; left: TNode | null }) {
    this.item = item;
    this.right = right;
    this.left = left;
  }

  static searchNode(x: number, node: TNode | null) {
    if (!node) return false;
    if (node.item === x) return true;
    if (node.item > x) {
      TNode.searchNode(x, node.right);
    } else if (node.item < x) {
      TNode.searchNode(x, node.left);
    }
    return false;
  }

  static insertNode(x: number, node: TNode | null) {
    if (!node) return new TNode({ item: x, right: null, left: null });
    if (node.item > x) {
      node.right = TNode.insertNode(x, node.right);
    } else if (node.item < x) {
      node.left = TNode.insertNode(x, node.left);
    }
    return node;
  }

  static searchMin(node: TNode): number {
    if (!node) return 0;
    if (!node.left) return node.item;
    return TNode.searchMin(node.left);
  }

  static deleteMin(node: TNode | null) {
    if (!node) return null;
    if (!node.left) return node.right;
    node.left = TNode.deleteMin(node.left);
    return node;
  }

  static deleteNode(x: number, node: TNode | null) {
    if (!node) return null;
    if (node.item === x) {
      if (!node.left) return node.right;
      if (!node.right) return node.left;

      node.item = TNode.searchMin(node.right);
      node.right = TNode.deleteMin(node.right);
    } else if (node.item > x) {
      node.left = TNode.deleteNode(x, node.left);
    } else {
      node.right = TNode.deleteNode(x, node.right);
    }
    return node;
  }

  static printNode(node: TNode | null) {
    if (!node) return;
    TNode.printNode(node.left);
    console.log(node.item);
    TNode.printNode(node.right);
  }
}

class Tree {
  root: TNode | null;

  constructor() {
    this.root = null;
  }

  search(x: number) {
    return TNode.searchNode(x, this.root);
  }

  insert(x: number) {
    this.root = TNode.insertNode(x, this.root);
  }

  delete(x: number) {
    this.root = TNode.deleteNode(x, this.root);
  }

  print() {
    TNode.printNode(this.root);
  }
}

const tree = new Tree();
tree.insert(5);
tree.insert(3);
tree.insert(7);
tree.insert(2);
tree.insert(4);
tree.insert(6);
tree.insert(8);
tree.print();
tree.delete(3);
tree.print();
