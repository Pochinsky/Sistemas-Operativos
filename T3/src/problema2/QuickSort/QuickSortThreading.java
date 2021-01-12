package QuickSort;

import java.io.*; 
import java.util.Random; 
import java.util.concurrent.RecursiveTask; 
  
public class QuickSortThreading extends RecursiveTask<Integer> {
    int start, end; 
    int[] arr; 
  
    private int partion(int start, int end, int[] arr) {
        int i 	    = start, j = end; 
        int pivote  = new Random().nextInt(j - i)+ i; 
        int t 	    = arr[j]; 
        arr[j]		= arr[pivote]; 
        arr[pivote] = t; 
        j--; 
  
        while (i <= j) { 
            if (arr[i] <= arr[end]) { 
                i++; 
                continue; 
            } 
            if (arr[j] >= arr[end]) { 
                j--; 
                continue; 
            } 
            t 	   = arr[j]; 
            arr[j] = arr[i]; 
            arr[i] = t; 
            j--; 
            i++; 
        } 
  
        t 		   = arr[j + 1]; 
        arr[j + 1] = arr[end]; 
        arr[end]   = t; 
        return j + 1; 
    } 
  
    public QuickSortThreading(int start, int end, int[] arr) {
        this.arr   = arr; 
        this.start = start; 
        this.end   = end; 
    } 
  
    @Override
    protected Integer compute() {
        if (start >= end) 
            return null; 
  
        int p = partion(start, end, arr); 
  
        QuickSortThreading left  = new QuickSortThreading(start, p - 1, arr);
        QuickSortThreading right = new QuickSortThreading(p + 1, end, arr);
  
        left.fork(); 
        right.compute(); 
  
        left.join(); 
  
        return null; 
    } 
} 
