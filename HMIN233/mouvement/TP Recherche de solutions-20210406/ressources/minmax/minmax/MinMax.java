package minmax;

public class MinMax {
	public static void main(String[] args) {

		MinMaxAI ai = new MinMaxAI();
		// preparer l'ia 
		// ex : ai.faireCeQuilFaut(x, truc, ...);
			
		TTTGame game = new TTTGame();
		//ajouter l'ia au jeu, sinon on joue tout seul
		//game.setAI(ai); 
		// si l'ia joue le premier coup
		//game.playAITurn();
		game.setVisible(true);
	}
}
