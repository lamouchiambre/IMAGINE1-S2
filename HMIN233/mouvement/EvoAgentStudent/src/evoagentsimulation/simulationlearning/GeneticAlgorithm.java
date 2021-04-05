/*******************************************************************************
 *  * EvoAgentStudent : A simulation platform for agents using neurocontrollers
 *  * Copyright (c)  2020 Suro François (suro@lirmm.fr)
 *  *
 *  * This program is free software: you can redistribute it and/or modify
 *  * it under the terms of the GNU General Public License as published by
 *  * the Free Software Foundation, either version 3 of the License, or
 *  * any later version.
 *  *
 *  * This program is distributed in the hope that it will be useful,
 *  * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  * GNU General Public License for more details.
 *  *
 *  * You should have received a copy of the GNU General Public License
 *  * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *******************************************************************************/

package evoagentsimulation.simulationlearning;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;


public class GeneticAlgorithm {
	private int populationSize = 200;
	private int maxGeneration = 100;
	private int repetitions = 1;
	int genomeSize = 0;
	ArrayList<Individual> population;
	
	public class Individual implements Comparable<Individual> {
		double score = 0;
		double genome[]; 

		public Individual(){
			genome = new double[genomeSize];
		}

		public int compareTo(Individual compare) {
		   return (int) (this.getScore() - compare.getScore());
		}

		public void random(){
			// ...
			Random random = new Random();
			for(int i = 0; i < genomeSize ; i++) {
				genome[i] = random.nextDouble();
			}
		}
		
		public boolean sansDoublon(double tab[], int n) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					if(tab[i] == tab[j] && i != j ) {
						return true;
					}
				}
			}
			return false;
		}
		

		public Individual crossbreed(Individual i2){
			// ...
			Individual ind = new Individual();
			Random random = new Random();
			double gem[] = new double[genomeSize];
			int pivot = random.nextInt(genomeSize-2)+1;
			for(int i = 0; i < pivot; i++) {
				gem[i] = this.genome[i];
			}
			for(int i = pivot; i < genomeSize; i++) {
				gem[i] = this.genome[i];
			}
			ind.genome = gem;
			
			return ind;
		}

		public void mutation(double probabilite)
		{
			// ...
			for (int i= 0; i < probabilite*populationSize; i++) {
				Random random = new Random();
				int ind = random.nextInt(populationSize) - 1;
				int pivot = random.nextInt(genomeSize-2)+1;
				population.get(ind).genome[pivot] = random.nextDouble();
			}
			
		}

		public double[] getGenome() {
			return genome;
		}

		public double getScore() {
			return score;
		}

		public void setScore(double val) {
			score = val;
		}
	}

	public GeneticAlgorithm(int genomeS){
		genomeSize=genomeS;
	}

	public void initialise(){
		population = new ArrayList<Individual>();
		for(int i = 0; i < populationSize; i++) {
			Individual ind = new Individual();
			ind.random();
			population.add(ind);
		}
		// ...
	}	

	public void breedNew(){
		// ...
		while(this.repetitions < maxGeneration) {
			Collections.sort(this.population);
			ArrayList<Individual> best_populations = new ArrayList<Individual>();
			ArrayList<Individual> new_populations = new ArrayList<Individual>();
			Random random = new Random();
			
			int nbPolgen = (this.populationSize*30)/100 ;
			int new_N = this.populationSize;
			
			int nb_mut = random.nextInt(nbPolgen);
			//on prend les 30% les mieux
			
			for(int i = 0; i < new_N - (nbPolgen + nb_mut) ; i++) {
				 int nb1 = random.nextInt(nbPolgen);
				 int nb2 = random.nextInt(nbPolgen);
				 while(nb1 == nb2) {
						nb2 = random.nextInt(nbPolgen);
					}
				 Individual inf = new Individual();
				 inf = new_populations.get(nb1).crossbreed(new_populations.get(nb2));
				 new_populations.add(inf);
			 }
			
			for(int i = 0; i < nbPolgen; i++) {
				Individual ind = new Individual();
				int piv = random.nextInt(new_N - nbPolgen - 1) + nbPolgen;
				//best_populations.add(this.population.get(i)); 
				new_populations.get(piv).mutation(0.2);
				//add(this.population.get(i)); 
			}
			
			this.repetitions++;
			
			
			
		}
	}
	
	@Override
	protected Object clone() throws CloneNotSupportedException {
		// TODO Auto-generated method stub
		return super.clone();
	}

	public Individual getBest(){
		// ...
		Collections.sort(this.population);
		return this.population.get(0);
	}

	public ArrayList<Individual> getPopulation()
	{
		return population;
	}

	public int getMaxGeneration() {
		return maxGeneration;
	}

	public int getPopulationSize() {
		return populationSize;
	}

	public void setPopulationSize(int populationSize) {
		this.populationSize = populationSize;
	}

	public void setMaxGeneration(int maxGeneration) {
		this.maxGeneration = maxGeneration;
	}

	public int getRepetitions() {
		return repetitions;
	}

	public void setRepetitions(int repetitions) {
		this.repetitions = repetitions;
	}
}
