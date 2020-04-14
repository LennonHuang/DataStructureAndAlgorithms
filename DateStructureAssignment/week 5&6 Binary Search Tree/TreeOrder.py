

# python3

import sys, threading
sys.setrecursionlimit(10**6) # max depth of recursion
threading.stack_size(2**27)  # new thread will get stack of such size

class TreeOrders:
  def read(self):
    self.n = int(sys.stdin.readline())
    self.key = [0 for i in range(self.n)]
    self.left = [0 for i in range(self.n)]
    self.right = [0 for i in range(self.n)]
    for i in range(self.n):
      [a, b, c] = map(int, sys.stdin.readline().split())
      self.key[i] = a
      self.left[i] = b
      self.right[i] = c

  def inOrder(self):
    self.result = []
    # Finish the implementation
    # You may need to add a new recursive method to do that
    def inOrderRecur(root: int,result):
        if(self.left[root] != -1):
            inOrderRecur(self.left[root],self.result)
        result.append(self.key[root])
        if(self.right[root] != -1):
            inOrderRecur(self.right[root],self.result)
    inOrderRecur(0,self.result)#Assume index 0 is the root
    return self.result

  def preOrder(self):
    self.result = []
    def preOrderRecur(root: int,result):
        result.append(self.key[root])
        if(self.left[root] != -1):
            preOrderRecur(self.left[root],self.result)
        if(self.right[root] != -1):
            preOrderRecur(self.right[root],self.result)
    preOrderRecur(0,self.result)#Assume index 0 is the root
    # Finish the implementation
    # You may need to add a new recursive method to do that
    return self.result

  def postOrder(self):
    self.result = []
    # Finish the implementation
    # You may need to add a new recursive method to do that
    def postOrderRecur(root: int,result):
        if(self.left[root] != -1):
            postOrderRecur(self.left[root],self.result)
        if(self.right[root] != -1):
            postOrderRecur(self.right[root],self.result)
        result.append(self.key[root])
    postOrderRecur(0,self.result)#Assume index 0 is the root
    return self.result

def main():
	tree = TreeOrders()
	tree.read()
	print(" ".join(str(x) for x in tree.inOrder()))
	print(" ".join(str(x) for x in tree.preOrder()))
	print(" ".join(str(x) for x in tree.postOrder()))

threading.Thread(target=main).start()
