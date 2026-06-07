package com.mycompany.benchmarkjav;

import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.TreeMap;

public class BenchmarkJav {

    public static void main(String[] args) {

        final int RECORDS = 10000;

        try {

            FileWriter writer =
                    new FileWriter("java_results.csv");

            writer.write(
                    "language,operation,structure,records,time_ms\n"
            );

            // ==========================
            // HASHMAP INSERT
            // ==========================

            HashMap<Integer,Integer> hashMap =
                    new HashMap<>();

            long start =
                    System.nanoTime();

            for(int i=0;i<RECORDS;i++) {

                hashMap.put(i,i);
            }

            long end =
                    System.nanoTime();

            double hashInsert =
                    (end-start)/1_000_000.0;

            writer.write(
                    "Java,insert,HashMap,"
                    + RECORDS + ","
                    + hashInsert + "\n"
            );

            // ==========================
            // HASHMAP SEARCH
            // ==========================

            start =
                    System.nanoTime();

            for(int i=0;i<RECORDS;i++) {

                hashMap.get(i);
            }

            end =
                    System.nanoTime();

            double hashSearch =
                    (end-start)/1_000_000.0;

            writer.write(
                    "Java,search,HashMap,"
                    + RECORDS + ","
                    + hashSearch + "\n"
            );

            // ==========================
            // TREEMAP INSERT
            // ==========================

            TreeMap<Integer,Integer> treeMap =
                    new TreeMap<>();

            start =
                    System.nanoTime();

            for(int i=0;i<RECORDS;i++) {

                treeMap.put(i,i);
            }

            end =
                    System.nanoTime();

            double treeInsert =
                    (end-start)/1_000_000.0;

            writer.write(
                    "Java,insert,TreeMap,"
                    + RECORDS + ","
                    + treeInsert + "\n"
            );

            // ==========================
            // TREEMAP TRAVERSAL
            // ==========================

            start =
                    System.nanoTime();

            for(Integer key :
                    treeMap.keySet()) {

                int value =
                        treeMap.get(key);
            }

            end =
                    System.nanoTime();

            double treeTraversal =
                    (end-start)/1_000_000.0;

            writer.write(
                    "Java,traversal,TreeMap,"
                    + RECORDS + ","
                    + treeTraversal + "\n"
            );

            writer.close();

            System.out.println(
                    "java_results.csv generado."
            );

        }

        catch(IOException e) {

            e.printStackTrace();
        }
    }
}