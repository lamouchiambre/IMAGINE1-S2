package tsp;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class AlgoGenTSP{
	private int distance[][];
	private int nbVilles;
	private ArrayList<Individu> populations;
	
	public class Individu implements Comparable<Individu> {

		private int cheminVille[]; 
		
		Individu(){
			this.cheminVille = new int[nbVilles - 1];
		}
		
		//getter setter
		public int[] getCheminVille() {
			return cheminVille;
		}

		public void setCheminVille(int[] cheminVille) {
			this.cheminVille = cheminVille;
		}

		public int compareTo(Individu compare) {
			// a remplir retourne 0 si egaux, negatif si plus petit, positif si plus grand 
			
		   return this.score() < compare.score() ? -1 : this.score() == compare.score()? 0 : 1;
		}
		
		public int score() {
			TSPMain tsp = new TSPMain();
			
			return tsp.calculerCout(distance, cheminVille, nbVilles);
			
		}
		
		public void mutation() {
			Random random = new Random();
			int nb1, nb2;
			nb1 = random.nextInt(nbVilles-1);
			nb2 = random.nextInt(nbVilles-1);
			
			while(nb1 == nb2) {
				nb2 = random.nextInt(nbVilles-1);
			}
			int tmp = this.cheminVille[nb1];
			this.cheminVille[nb1] = this.cheminVille[nb2];
			this.cheminVille[nb2] = tmp;
		}
		
		@Override
		public String toString(){
			String result = " ";
			for (int i=0; i< cheminVille.length; i++){
				result += cheminVille[i];
				result += " -> ";
				}
			result += score();
			
			return result;
			
		}
	}

	public AlgoGenTSP(int dist[][],int nbVilles){
		this.distance = dist;
		this.nbVilles = nbVilles;
		this.populations = new ArrayList<Individu>();
	}
	
	public Individu aleaIndividu() {
		Individu ind = new Individu();
		TSPMain tsp = new TSPMain();
		int chemin[] = new int[nbVilles - 1];
		
		tsp.genererChemin(chemin, nbVilles);
		
		ind.setCheminVille(chemin);
		
		return ind;
	}
	
	public Individu croisement(Individu i1, Individu i2) {
		Individu ind = new Individu();
		Random random = new Random();
		int pivot;
		pivot = random.nextInt(nbVilles - 1);
		System.out.println("pivot = " + pivot );
		int chemin[] = new int[nbVilles - 1];
		for(int i = 0; i < nbVilles-1; i++) {
			if ( i < pivot ) {
				chemin[i] = i1.getCheminVille()[i];
			}else {
				chemin[i] = i2.getCheminVille()[i];
			}
		}
		ind.setCheminVille(chemin);
		
		return ind;
	}
	
	public void genererPopulationAlea(int N) {
		for(int i  = 0; i < N ; i++) {
			this.populations.add(this.aleaIndividu());
		}
	}
	
	public void cycle() {
		//result = taillePopulation - (taillePopulation * 30 /100)
		this.triePopulation();
		Random random = new Random();
		
		ArrayList<Individu> new_populations = new ArrayList<Individu>();
		ArrayList<Individu> best_populations = new ArrayList<Individu>();
		
		int nbPolgen = this.getPopulations().size() - (this.getPopulations().size()*30)/100 ;
		int new_N = this.getPopulations().size();
		
		int nb_mut = random.nextInt(nbPolgen);
		
		for(int i = 0; i < nbPolgen; i++) {
			best_populations.add(this.populations.get(i)); 
			new_populations.add(this.populations.get(i)); 
		}
		
		for(int i = 0; i < nb_mut  ; i++) {
			 int nb1 = random.nextInt(nbPolgen);
			 new_populations.get(nb1).mutation(); 
			
		 }
		
		 for(int i = 0; i < new_N - nbPolgen ; i++) {
			 int nb1 = random.nextInt(nbPolgen);
			 int nb2 = random.nextInt(nbPolgen);
			 while(nb1 == nb2) {
					nb2 = random.nextInt(nbPolgen);
				}
			 new_populations.add(this.croisement(best_populations.get(nb1),best_populations.get(nb2)));
		 }
		 
		 this.setPopulations(new_populations);
		
	}
	
	public void triePopulation() {
		Collections.sort(populations);
	}

	public int[][] getDistance() {
		return distance;
	}

	public void setDistance(int[][] distance) {
		this.distance = distance;
	}

	public int getNbVilles() {
		return nbVilles;
	}

	public void setNbVilles(int nbVilles) {
		this.nbVilles = nbVilles;
	}

	public ArrayList<Individu> getPopulations() {
		return populations;
	}

	public void setPopulations(ArrayList<Individu> populations) {
		this.populations = populations;
	} 
}
