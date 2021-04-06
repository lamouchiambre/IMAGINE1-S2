package arbres;

import java.util.ArrayList;

public class TreeNode<T> {

	private ArrayList<TreeNode> children = null;
	private T data = null;

	public TreeNode(){}

	public TreeNode(T data)
	{
		this.data = data
	}
	
	public T getData()
	{
		return data;
	}

	public ArrayList<TreeNode> getChildren()
	{
		return children;
	}	

	public void addChild(TreeNode<T> child)
	{
		//a faire
	}
}
