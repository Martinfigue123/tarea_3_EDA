#include "trees/rb.hpp"
#include "trees/abb.hpp"
#include "trees/avl.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>

void exportTimes(std::string filename, std::vector<int>& times) {
    std::ofstream fout(filename);
    for (const auto& time : times) {
        fout << time << "\n";
    }
    fout.close();
}

void measureBuildTimeABB(trees::ABB& tree, int* data, int n_data) {
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n_data; i++) {
        tree.insert(data[i]);
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "ABB Build Time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

void measureSearchTime(trees::ABB& tree, int* queries, int n_queries) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n_queries; i++) {
        tree.find(queries[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "ABB Search Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

int* readKeysFromFile(std::string filename, int* n_keys){
    std::ifstream  fin(filename, std::ios::binary); 
    char* val = new char[4];
    int n = 0;
    fin.read(val, 4);
    while (!fin.eof()){
        n = n + 1;        
        fin.read(val, 4);
    }
    fin.close();
    fin.open(filename, std::ios::binary); 
    int* keys = new int[n];
    for(int i=0; i < n; i++){
        fin.read(val, 4);
        keys[i] = *reinterpret_cast<int*>(val);
    }
    fin.close();
    *n_keys = n;
    delete[] val;
    return keys;
}

int main(int nargs, char** vargs){
    int n_data = 0;
    int* data = readKeysFromFile("keys_sorted.bin", &n_data);
    trees::RB rbtree;
    for(int i=0; i<n_data;i++){
        std::cout<< "inserting " << data[i] << std::endl;
        rbtree.insert(data[i]);
    } 
    rbtree.traverse();

    return 0;
}