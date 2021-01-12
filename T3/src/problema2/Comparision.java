import QuickSort.QuickSort;
import QuickSort.QuickSortThreading;
import java.util.Random;
import java.util.Arrays;
import java.util.concurrent.ForkJoinPool;

public class Comparision {
	/*
	 * Method: 		generateArray
	 * Parameters: 	no recibe
	 * Return: 		arreglo de enteros
	 * Description: Genera un arreglo de tamaño aleatorio y
	 * 				de elementos aleatorios.
	 */
	public static int[] generateArray() {
		Random rand = new Random();
		int number  = rand.nextInt(16)+5;
		int[] array   = new int[number];

		for (int i=0; i<array.length; i++)
			array[i] = rand.nextInt(101);
		return array;
	}
	/*
	 * Method: 		printArray
	 * Parameters:	arreglo de enteros
	 * Return:		no retorna
	 * Description: Muestra un arreglo por consola.
	 */
	public static void printArray(int[] array) {
		System.out.print("[ ");
		for (int i=0; i<array.length; i++)
			System.out.print(array[i]+" ");
		System.out.println("]");
	}

	public static void main (String[] args) {
		Random rand  = new Random();
		int N_ARRAYS = rand.nextInt(6)+5;

		for (int i=0; i<N_ARRAYS; i++) {
			int N_ELEMENTS 			= rand.nextInt(151)+50;
			int[] arrayNotThreading = new int[N_ELEMENTS];
			int[] arrayThreading	= new int[N_ELEMENTS];
			for (int j=0; j<N_ELEMENTS; j++) {
				arrayNotThreading[j] = rand.nextInt(201);
				arrayThreading[j]	 = arrayNotThreading[j];
			}
			System.out.println("Arreglo a Ordenar:");
			printArray(arrayNotThreading);

			QuickSort sortingWithoutThreading = new QuickSort();
			long start, end, time1, time2;

			start = System.nanoTime();
			sortingWithoutThreading.sort(arrayNotThreading,0,N_ELEMENTS-1);
			end   = System.nanoTime();
			time1 = end - start;

			System.out.println("\nArreglo Ordenado con QuickSort:");
			printArray(arrayNotThreading);
			System.out.println("tiempo: "+time1+" [ns]");

			System.out.println("\nArreglo a Ordenar:");
			printArray(arrayThreading);

			ForkJoinPool pool = ForkJoinPool.commonPool();
			start			  = System.nanoTime();
			pool.invoke(new QuickSortThreading(0,N_ELEMENTS-1,arrayThreading));
			end				  = System.nanoTime();
			time2			  = end - start;

			System.out.println("\nArreglo Ordenado con QuickSort y Hebras:");
			printArray(arrayThreading);
			System.out.println("tiempo: "+time2+" [ns]\n");

			if (time1 < time2)
				System.out.println("QuickSort sin Threads: Mejor Tiempo: "+time1+" [ns]\n");
			else if (time1 > time2)
				System.out.println("QuickSort con Threads: Mejor Tiempo: "+time2+" [ns]\n");
			else
				System.out.println("Tiempos Iguales\n");
		}
	}
}
