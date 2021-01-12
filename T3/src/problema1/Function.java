import java.io.IOException;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.script.ScriptException;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

public class Function {
	public static void main (String[] args) throws ScriptException, IOException, ScriptException {
		try {
			/* Se obtiene la cantidad de funciones */
			File arch 		= new File("./problema1/funciones.txt");
			Scanner reader	= new Scanner(arch);
			int number		= Integer.parseInt(reader.nextLine());

			String function;
			Map <String, String> hash = new HashMap<String, String>();
			String divide[] 		  = new String[2];

			/* Se obtienen las funciones */
			for (int i=0; i<number; i++) {
				function = reader.nextLine();
				divide = function.split("=");
                String n = divide[0].substring(0,1);
				hash.put(n,divide[1]);
			}

			Iterator<Map.Entry<String, String>> it = hash.entrySet().iterator();
			while (it.hasNext()) {
				Map.Entry<String, String> element = it.next();
				System.out.println(element.getKey()+" : "+element.getValue());
			}
            System.out.println("Funciones Cargadas!");
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            System.out.println("Ingrese Operacion:");
            String funcion= br.readLine();
            while(!funcion.equals("salir")){
            	String letra = funcion.substring(0,1);
            	String aux = funcion.substring(1);
                String[] aux2 = aux.split("\\(");
                String[] aux3 = aux2[1].split("\\)");
                String variable =aux3[0];
                Resolver hebra= new Resolver(hash,letra,variable);
                hebra.start();
                while(hebra.isAlive()){
                	/* Esperar terminen hebras (while culiao challa)*/
                }
                ScriptEngineManager mgr = new ScriptEngineManager();
                ScriptEngine engine = mgr.getEngineByName("JavaScript");
                System.out.println(engine.eval(hebra.resultado));
                System.out.println(funcion+"->"+engine.eval(hebra.resultado));
                System.out.println("Ingrese nueva Operacion o escriba salir:");
                funcion= br.readLine();
            }
		}
		 
		catch (FileNotFoundException e) {
			System.out.println("ERROR DE LECTURA");
			e.printStackTrace();
		}	
	}
}

class Resolver extends Thread{
    public Map<String, String> hash;
    public String letra;
    public String variable;
    public String resultado;
    public ArrayList<String> posibles_funciones;
    public ArrayList<Resolver> funciones_adicionales;
    public String funcion;
    public ArrayList<String> resultados;
    
	/* constructor */
    public Resolver(Map<String, String> hash, String letra, String variable){
        this.hash= hash;
        this.letra=letra;
        this.variable=variable;
        this.posibles_funciones= new ArrayList<String>();
        this.funciones_adicionales= new ArrayList<Resolver>();
    }
    
	/* Method:		run
	 * Parameters: 	no recibe
	 * Return: 		no retorna
	 * Description:	Reemplaza el nombre de la funcion
	 * 				por su ecuacion
	 */
    public void run(){
        Iterator<Map.Entry<String, String>> iter = hash.entrySet().iterator();
        this.funcion= hash.get(letra);
        String funcion_reemplazada= this.funcion.replace("x",this.variable);
        this.resultado=funcion_reemplazada;

		/* revisa si una funcion sigue sin ser reemplazada por su ecuacion */
        if (funcion_reemplazada.matches(".*[a-z].*")){
            String[] posibles_func= funcion_reemplazada.split("[\\+\\/\\-\\*]");
            for (int i = 0; i < posibles_func.length; i++){
                if(posibles_func[i].matches(".*[a-z].*")){
                    if(posibles_func[i].substring(0,1).equals("(")){
                        String pos_letra= posibles_func[i].substring(1,2);
                        this.posibles_funciones.add(pos_letra);
                    }else{
                        String pos_letra= posibles_func[i].substring(0,1);
                        this.posibles_funciones.add(pos_letra);
                    }
                }
            }

	        for (String f : this.posibles_funciones){
    	        Resolver hebra= new Resolver(this.hash,f,this.variable);
        	    hebra.start();
            	this.funciones_adicionales.add(hebra);
            }
	        for (Resolver h : this.funciones_adicionales){
    	        while(h.isAlive()){
        	        /* Esperar terminen hebras */
            	}
        	}
	        for (Resolver h: this.funciones_adicionales){
    	        this.resultado= this.resultado.replace(h.letra+"("+h.variable+")","("+h.resultado+")");
        	}
        }
        else{
            this.resultado= funcion_reemplazada;
        }
    }
 }
