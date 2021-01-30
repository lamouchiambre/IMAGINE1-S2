package tp1;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Writer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;




public class Application {
	
	public void lire(BufferedReader in) throws Exception {
		ArrayList<ArrayList<ArrayList<String>>>cnf = new ArrayList<ArrayList<ArrayList<String>>>();
		String str = "";
		while((str=in.readLine())!=null && str.length()!=0){
			
			String[] varDeclaration = str.split(" ");
			ArrayList<ArrayList<String>>clause = new ArrayList<ArrayList<String>>();
			ArrayList<String> positif = new ArrayList<String>(); 
			ArrayList<String> negatif = new ArrayList<String>();
			if( ! (varDeclaration[0].startsWith("p") || varDeclaration[0].startsWith("c") || varDeclaration[0].startsWith("%"))) {
				for(int i = 0; i < varDeclaration.length -1 ; i++) {
					if(varDeclaration[i].contains("-")) {
						negatif.add(varDeclaration[i].substring(1));
					}else {
						positif.add(varDeclaration[i]);
					}
				}
				
				clause.add(positif);
				clause.add(negatif);
				
				cnf.add(clause);
			}
			
			

		}
		
		for(int i = 0; i< cnf.size(); i++) {
			int taillep =  cnf.get(i).get(0).size();
			int taillen =  cnf.get(i).get(1).size();
			
			System.out.print(" ( ");
			for(int k = 0; k <taillep; k++) {
				System.out.print(cnf.get(i).get(0).get(k) + " ^ ");
			}
			
			//System.out.print(cnf.get(i).get(0).get(taillep-1));
			
			for(int k = 0; k < taillen; k++) {
				System.out.print(" !" + cnf.get(i).get(1).get(k) + " ^ ");
			}
			
			//System.out.print(" !" + cnf.get(i).get(1).get(taillen-1));
			System.out.print(" ) ");
			System.out.println(" v ");
		}
		
		
	}
	
	
	public static void lectureFichier(String fileName) {
		
		try {
			System.out.println("Chargement du fichier : "+new java.io.File( "." ).getCanonicalPath()+"/"+fileName);
			BufferedReader readFile= new BufferedReader(new FileReader (fileName));
			
			Application a = new Application();
			a.lire(readFile);
			readFile.close();

		} catch (Exception e) {
			System.out.println("erreur survenue: " + e.toString());
		}
		
	}

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub

		File fichier =  new File("bonjour.txt") ;
		
		Writer writer = new FileWriter(fichier);
		writer.write("La première ligne");
		writer.write("La deuxième ligne");
		writer.close();
		
		
		Application a = new Application();
		Application.lectureFichier("testCNF.txt");
		Application.lectureFichier("uf20-01.cnf");
	}

}
