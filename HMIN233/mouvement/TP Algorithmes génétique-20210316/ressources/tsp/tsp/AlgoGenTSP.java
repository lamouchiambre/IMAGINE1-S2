package tsp;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Random;

//import tsp.AlgoGenTSP2.Individu;

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
			
		   //return this.score() < compare.score() ? -1 : this.score() == compare.score()? 0 : 1;
			return score() - compare.score();
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
		
		public Individu mutation2() {
			Individu i = new Individu();
			int chemin[] = new int[nbVilles - 1];
			for(int j = 0; j < nbVilles - 1; j++) {
				chemin[j] = this.getCheminVille()[j];
			}
			i.setCheminVille(chemin);
			Random random = new Random();
			int nb1, nb2;
			nb1 = random.nextInt(nbVilles-1);
			nb2 = random.nextInt(nbVilles-1);
			
			while(nb1 == nb2) {
				nb2 = random.nextInt(nbVilles-1);
			}
			int tmp = i.cheminVille[nb1];
			i.cheminVille[nb1] = i.cheminVille[nb2];
			i.cheminVille[nb2] = tmp;
			return i;
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

		public void clear() {
			// TODO Auto-generated method stub
			this.cheminVille = new int[nbVilles - 1];
			
		}

		public int get(int i) {
			// TODO Auto-generated method stub
			return this.cheminVille[i];
		}
	}

	public AlgoGenTSP(int dist[][],int nbVilles){
		this.distance = dist;
		this.nbVilles = nbVilles;
		this.populations = new ArrayList<Individu>();
	}
	public Individu cross(Individu i1, Individu i2) {
		int pivot = (int) (Math.random() * nbVilles - 1) + 1;
		Individu ind = new Individu();
		
		//ind.clear();
		int chemin[] = new int[nbVilles-1];
		ArrayList<Integer> list_chem = new ArrayList<Integer>(); 
		for(int i = 0 ;  i < pivot; i++) {
			list_chem.add(i1.get(i));
			;
		}
		
		for(int i = pivot ;  i < nbVilles-1; i++) {
			if(!list_chem.contains(i2.get(i)))
				list_chem.add(i2.get(i));
		}
		
		int s;
		while(list_chem.size() != nbVilles-1) {
			s = 1 + (int) (Math.random() * (nbVilles-1));
			if(!list_chem.contains(s)) {
				list_chem.add(s);
			}
		}
		for(int i = 0; i < nbVilles-1; i++) {
			chemin[i] = list_chem.get(i);
		}
		ind.setCheminVille(chemin);
		
		return ind;
	}
	public Individu aleaIndividu() {
		Individu ind = new Individu();
		TSPMain tsp = new TSPMain();
		int chemin[] = new int[nbVilles - 1];
		
		tsp.genererChemin(chemin, nbVilles);
		
		ind.setCheminVille(chemin);
		
		return ind;
	}
	
	public boolean appartient(int tab1[], int n1, int tab2[], int n2){
		for(int i = 0; i < n1; i ++) {
			for(int j = 0; j < n2; j++) {
				if(tab1[i] == tab2[j]) {
					return true;
				}
			}
		}
		
		return false;
	}
	
	public boolean sansDoublon(int tab[], int n) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(tab[i] == tab[j] && i != j ) {
					return true;
				}
			}
		}
		return false;
	}
	
	public Individu croisement(Individu i1, Individu i2) {
		Individu ind = new Individu();
		Random random = new Random();
		int pivot;
		pivot = 1 + random.nextInt(nbVilles - 2);

		int chemin[] = new int[nbVilles - 1];
		int fin = 0; 
		do{
			chemin = new int[nbVilles - 1];
			for(int i = 0; i < nbVilles-1; i++) {
				if ( i < pivot ) {
					chemin[i] = i1.getCheminVille()[i];

				}else {
					chemin[i] = i2.getCheminVille()[i];

				}
			}
			pivot = (pivot+1)%(nbVilles - 2);
			fin++;

		}while(sansDoublon(chemin,nbVilles - 1) && fin < (nbVilles - 1)  );

		ind.setCheminVille(chemin);
		
		return ind;
	}
	
	public void genererPopulationAlea(int N) {
		for(int i  = 0; i < N ; i++) {
			this.populations.add(this.aleaIndividu());
		}
	}
	
	public void cycle(int pr_max) {
		//System.out.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
		this.triePopulation();
		Random random = new Random();
		
		ArrayList<Individu> new_populations = new ArrayList<Individu>();
		ArrayList<Individu> best_populations = new ArrayList<Individu>();
		
		int nbPolgen = (this.getPopulations().size()*pr_max)/100 ;
		int new_N = this.getPopulations().size();
		
		int nb_mut = random.nextInt(nbPolgen);
		
		//on prend les 30% les mieux
		for(int i = 0; i < nbPolgen; i++) {
			best_populations.add(this.populations.get(i)); 
			new_populations.add(this.populations.get(i)); 
		}
		for(int i = 0; i < new_N - (nbPolgen + nb_mut) ; i++) {
			 int nb1 = random.nextInt(nbPolgen);
			 int nb2 = random.nextInt(nbPolgen);
			 while(nb1 == nb2) {
					nb2 = random.nextInt(nbPolgen);
				}
			 Individu inf = new Individu();
			 inf = this.cross(new_populations.get(nb1),new_populations.get(nb2));
			 new_populations.add(inf);
		 }
		//on effectue des mutation
//		for(int i = 0; i < nb_mut  ; i++) {
//			 int nb1 = random.nextInt(nbPolgen);
//			 Individu inf = new Individu();
//			 inf = best_populations.get(nb1).mutation2();
//			 new_populations.add(inf);
//		 }
		for(int i = 0; i < nb_mut  ; i++) {
		 int nb1 = random.nextInt(new_populations.size());
		 Individu inf = new Individu();
		 inf = new_populations.get(nb1).mutation2();
		 new_populations.add(inf);
	 }

		 this.setPopulations(new_populations);
	}
	
	public Individu search__sol(int nb_cycle) {
		for (int i = 0; i < nb_cycle; i++) {
			cycle(30);
		}
		triePopulation();
		return this.populations.get(0);
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
