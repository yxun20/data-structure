import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

class Node {
    int data;
    Node left, right;

    public Node(int item) {
        data = item;
        left = right = null;
    }
}

class BST {
    Node root;

    public BST() {
        root = null;
    }

    public void insert(int data) {
        root = insertRec(root, data);
    }

    private Node insertRec(Node root, int data) {
        if (root == null) {
            root = new Node(data);
            return root;
        }

        if (data < root.data)
            root.left = insertRec(root.left, data);

        else if (data > root.data)
            root.right = insertRec(root.right, data);

        return root;
    }

    public int performDFS(int n) {
        Stack<Node> stack = new Stack<>();
        stack.push(root);
        int count = 0;
        int sum = 0;

        while (!stack.isEmpty()) {
            Node current = stack.pop();
            sum += current.data;
            count++;

            if (count == n)
                break;

            if (current.right != null)
                stack.push(current.right);

            if (current.left != null)
                stack.push(current.left);
        }

        return sum;
    }

    public int performBFS(int n) {
        Queue<Node> queue = new LinkedList<>();
        queue.add(root);
        int count = 0;
        int sum = 0;

        while (!queue.isEmpty()) {
            Node current = queue.poll();
            sum += current.data;
            count++;

            if (count == n)
                break;

            if (current.left != null)
                queue.add(current.left);

            if (current.right != null)
                queue.add(current.right);
        }

        return sum;
    }
}

public class Main {
    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader("hw3_input.txt"));
            BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"));

            int numTestCases = Integer.parseInt(reader.readLine());

            for (int i = 0; i < numTestCases; i++) {
                String traversalType = reader.readLine();
                String[] traversalInfo = traversalType.split(":");
                int n = Integer.parseInt(traversalInfo[1].trim());

                String[] numbers = reader.readLine().split(" ");
                BST bst = new BST();

                for (String number : numbers) {
                    int value = Integer.parseInt(number);
                    bst.insert(value);
                }

                if (traversalInfo[0].trim().equals("DFS")) {
                    int sum = bst.performDFS(n);
                    writer.write(Integer.toString(sum));
                    writer.newLine();
                } 
                else if (traversalInfo[0].trim().equals("BFS")) {
                    int sum = bst.performBFS(n);
                    writer.write(Integer.toString(sum));
                    writer.newLine();
                }
            }

            reader.close();
            writer.close();
        } 
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}