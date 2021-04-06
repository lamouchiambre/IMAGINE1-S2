package arbres;

import java.util.ArrayList;

public class testArbre{
public static void main(String[] args) {
		TreeNode<String> racine = new TreeNode<String>(null, "racine");

		// arbre de test
		for(int i = 0; i < 3 ; i++)
		{
			TreeNode<String> noeud = new TreeNode<String>(racine, "niveau 1 - " + i);
			for(int j = 0; j < 2 ; j++)
			{
				noeud.addChild(new TreeNode<String>(racine, "niveau 2 - " + j));
			}
			racine.addChild(noeud);
		}
	}
}
