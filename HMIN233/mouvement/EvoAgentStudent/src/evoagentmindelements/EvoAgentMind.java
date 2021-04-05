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


package evoagentmindelements;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import evoagentmindelements.modules.ActuatorModule;
import evoagentmindelements.modules.SensorModule;

public class EvoAgentMind {
	private ArrayList<ActuatorModule> actuatorModules = new ArrayList<>();
	private ArrayList<SensorModule> sensorModules = new ArrayList<>();
	private int hiddenLayerCount = 0;
	private int hiddenLayerSize = 0;
	private boolean hasBiasNeurons = false;
	double weights[];

	public EvoAgentMind()
	{
		
	}
	
	public int genomeSize() {
        //si ya des neurones biais il faut les compter ici on en a pas

        //return sensorModules.size() * hiddenLayerSize + hiddenLayerSize * hiddenLayerSize + hiddenLayerSize + actuatorModules.size();
        int biasCount =0;
        if(hasBiasNeurons) {
            biasCount =1;
        }
        if(hiddenLayerCount ==0) {
            return (actuatorModules.size() * (sensorModules.size() + biasCount));

        }else if (hiddenLayerCount ==1) {
            return ((sensorModules.size() + biasCount)*hiddenLayerSize)+((hiddenLayerSize + biasCount) * actuatorModules.size());
        }else
            return ((sensorModules.size()+biasCount)*hiddenLayerSize)+ ((hiddenLayerSize + biasCount) * actuatorModules.size() + (hiddenLayerSize+biasCount) * hiddenLayerSize * (hiddenLayerCount-1));
    }
	
	private void initTab(double tab[]){
		for(int i = 0; i < tab.length; i++){
			tab[i] = 0;
		}
	}
	
	private void copyTab(double tab[], double source[]){
		for(int i = 0; i < source.length; i++){
			tab[i] = source[i];
		}
	}
	
	private void applyTransferToTab(double tab[]){
		for(int i = 0; i < tab.length; i++){
			tab[i] = this.applyTransfer(tab[i]);
		}
	}
	
	 public void doStep() {
		 
	        double prevHidden[] = new double[hiddenLayerSize];
	        double nextHidden[] = new double[hiddenLayerSize];
	        double output[] = new double[hiddenLayerSize];
	        int curentLayer = 1;
	        int poidsIndex = 0;
	        
	        if (hiddenLayerCount > 0) {
	            initTab(prevHidden);
	            initTab(nextHidden);
	            
	            //remplissage de la premier couche 
	            for (int i = 0; i < sensorModules.size(); i++) {
	                for (int j = 0; j < prevHidden.length; j++) {
	                    prevHidden[j] += sensorModules.get(i).getValue() * weights[poidsIndex];
	                    System.out.println(j + " " + prevHidden[j]+ " = " + sensorModules.get(i).getValue() + " * " + weights[poidsIndex]);
	                    poidsIndex++;
	              
	                }
	                System.out.println("_______");
	            }
	            
	            if (hasBiasNeurons) {
	                for (int j = 0; j < hiddenLayerSize; j++) {
	                    prevHidden[j] += weights[poidsIndex];
	                    poidsIndex++;
	                }
	            }

	            applyTransferToTab(prevHidden);
	            
	            while (curentLayer < hiddenLayerCount) {
	            	System.out.println("couche");

	                for (int i = 0; i < hiddenLayerSize; i++) {
	                    for (int j = 0; j < hiddenLayerSize; j++) {
	                        nextHidden[j] += prevHidden[i] * weights[poidsIndex];
	                        poidsIndex++;
	                    }
	                }
	                if (hasBiasNeurons) {
	                    for (int j = 0; j < hiddenLayerSize; j++) {
	                        nextHidden[j] += weights[poidsIndex];
	                        poidsIndex++;
	                    }
	                }
	                applyTransferToTab(prevHidden);
	                copyTab(nextHidden, prevHidden);
	                initTab(nextHidden);
	                curentLayer++;
	            }
	            
	            initTab(output);
	            for (int j = 0; j < hiddenLayerSize; j++) {
	                for (int k = 0; k < actuatorModules.size(); k++) {
	                    output[j] += prevHidden[j] * weights[poidsIndex];
	                    System.out.println(j + " " + output[j] + " = " + prevHidden[j] + " * " + weights[poidsIndex]);
	                    poidsIndex++;
	                }
	                System.out.println("__________");
	            }
	            if (hasBiasNeurons)
	                for (int j = 0; j < actuatorModules.size(); j++) {
	                    output[j] += weights[poidsIndex];
	                    poidsIndex++;
	                }

	            applyTransferToTab(output);
	            for (int i = 0; i < actuatorModules.size(); i++) {
	                actuatorModules.get(i).setMotorValue(normalize(output[i]));
	                //System.out.println(normalize(output[i]));
	            }
	        }
	    }
	
	public double normalize(double v)
	{
		return (v+1.0)/2.0;
	}
	
	public double applyTransfer(double v)
	{
		return Math.tanh(v);
	}
	
	public void setHiddenLayerCount(int n) {
		hiddenLayerCount = n;
	}

	public void setHiddenLayerSize(int n) {
		hiddenLayerSize = n;
	}
	
	public ArrayList<ActuatorModule> getActuatorModules()
	{
		return actuatorModules;
	}
	
	public ArrayList<SensorModule> getSensorModules()
	{
		return sensorModules;
	}
	
	public void addActuator(String actuatorID)
	{
		actuatorModules.add(new ActuatorModule(actuatorID));
	}

	public void addSensor(String sensorID)
	{
		sensorModules.add(new SensorModule(sensorID));
	}
	
	public void setWeights(double w[])
	{
		weights = w;
	}
	
	public void toFile(File f)
	{
		if(f.exists())
			f.delete();
		try {
			f.createNewFile();
			PrintWriter pw = new PrintWriter(new FileWriter(f),true);
			pw.println(hiddenLayerCount + " " 
					+ hiddenLayerSize + " " 
					+ sensorModules.size() + " " 
					+ actuatorModules.size() + " "
					+ genomeSize());
			for(int i = 0 ; i < sensorModules.size();i++)
				pw.println(sensorModules.get(i).getID());
			for(int i = 0 ; i < actuatorModules.size();i++)
				pw.println(actuatorModules.get(i).getID());
			for(int i = 0 ; i < weights.length;i++)
				pw.println(weights[i]);
			pw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void fromFile(File f)
	{
		if(f.exists())
		{
			InputStream ips = null;
			try {
				ips = new FileInputStream(f);
			} catch (FileNotFoundException e) {
				e.printStackTrace();
				System.out.println("file not found : " + f);
				return ;
			} 
			InputStreamReader ipsr=new InputStreamReader(ips);
			BufferedReader br=new BufferedReader(ipsr);
			try {
				String line = br.readLine();
				hiddenLayerCount = Integer.parseInt(line.split(" ")[0]);
				hiddenLayerSize = Integer.parseInt(line.split(" ")[1]);
				int sensorCount = Integer.parseInt(line.split(" ")[2]);
				int actuatorCount = Integer.parseInt(line.split(" ")[3]);
				int weightCount = Integer.parseInt(line.split(" ")[4]);
				weights = new double[weightCount];
				for(int i = 0 ; i < sensorCount; i++)
					addSensor(br.readLine());
				for(int i = 0 ; i < actuatorCount; i++)
					addActuator(br.readLine());
				for(int i = 0 ; i < weightCount; i++)
					weights[i] = Double.parseDouble(br.readLine());
			br.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static void main(String[] args) {
		System.out.println("Mind test");
		EvoAgentMind mind = new EvoAgentMind();
		mind.addActuator("A1");
		//mind.addActuator("A2");
		mind.addSensor("S1");
		mind.addSensor("S2");
		mind.setHiddenLayerCount(1);
		mind.setHiddenLayerSize(3);
		double weights[] = new double[mind.genomeSize()];
		System.out.println("size weights : " + weights.length);
		for(int i = 0 ; i < mind.genomeSize(); i++)
			//weights[i] = (Math.random() * 2.0) - 1.0;
		weights[0] = 0.2;
		weights[1] = -0.3;
		weights[2] = 0.1;
		weights[3] = 0.9;
		weights[4] = 0.2;
		weights[5] = -0.6;
		weights[6] = -0.4;
		weights[7] = -0.1;
		weights[8] = 0.8;
		mind.setWeights(weights);
		mind.getSensorModules().get(0).setValue(0.8);
		mind.getSensorModules().get(1).setValue(0.3);
		//mind.getActuatorModules().get(0).setMotorValue(0);
		mind.doStep();
		
		
		for(SensorModule s : mind.getSensorModules())
			System.out.println("S = "+s.getValue());
		
		for(ActuatorModule a: mind.getActuatorModules())
			System.out.println("A = "+a.getMotorValue());	
//		for(int i = 0 ; i < 10 ; i++)
//		{
//			System.out.println(i);
//			for(SensorModule s : mind.getSensorModules())
//				s.setValue(i/10.0);
//			mind.doStep();
//			for(ActuatorModule a: mind.getActuatorModules())
//				System.out.println(a.getMotorValue());		
//		}
	}		
}
