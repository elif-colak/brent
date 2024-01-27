#include "brent.h"
using namespace std;
#include <iostream>
#include <fstream>

Brent::Brent(int table_size){
  data_vec.resize(table_size);
}
 int Brent::hash(int key) const {
        return key % data_vec.size();
}
int Brent::hash2(int key) const{
        return int(key/data_vec.size())%data_vec.size();
    }
vector<int> Brent::calculateLQ(int index, int step) {
        vector<int> temp;
        temp.push_back(index);
        while (data_vec[index].valid == true) {
            // Collision: Linear quotient
            index = (index + step)%data_vec.size();
            temp.push_back(index);
        }
     
        return temp;
}
void Brent::insert(int key){
     //Initialization using the first hash function
    int index = hash(key);

    //I checked if there is a empty space in the table or not
    bool notempty = true;
    for (int m = 0; m < data_vec.size(); m++) {
        if (data_vec[m].valid == false) {
            notempty = false;
            break;
        }
    }

    //Inserting if there is an empty space
    if (notempty == false) {
        //Inserting the key if that index is empty
        if (data_vec[index].valid == false) {
            data_vec[index].valid = true;
            data_vec[index].data = key;
        } 
        //Collusion
        else{
            int step = hash2(key);
            vector<int> indexes = calculateLQ(index, step);
            int s = indexes.size();
            int is = 0;
            int js = 0;
            vector<int> s_I; // keeping every i value for each item
            vector<int> s_J; // keeping every j value for each item
            
            // Finding i and j's
            for (int i = 0; i < indexes.size(); i++) {
                int step2 = hash2(data_vec[indexes[i]].data);
                vector<int> temp = calculateLQ(indexes[i], step2);
                js = temp.size() - 1;
                s_I.push_back(is);
                s_J.push_back(js);
                is++;
                
            }
            
            //Comparing s values
            int ijmin = s_I[1] + s_J[1];
            int i_min = 0;
            int j_min = 1;
            int ijsum = 0;

            //Finding i_min j_min
            for (int i = 0; i < s_I.size(); i++) {
                for (int j = 1; j < s_J.size(); j++) {
                    if (data_vec[indexes[i]].valid && data_vec[indexes[j]].valid) {
                        ijsum = s_I[i] + s_J[j];
                        if (ijmin >= ijsum) {
                            ijmin = ijsum;
                            i_min = i;
                            j_min = j;
                        }
                    }
                }
            }
            

            if( ijmin+1 >= s){
                i_min = s_I.size()-1;
                j_min = 0;

            }
            
             // If i+j of min < s
            if (ijmin < s && j_min != 0) {
                int hashVal = hash(data_vec[indexes[i_min]].data);
                int step3 = hash2(data_vec[indexes[i_min]].data);
                vector<int> temp2 = calculateLQ(indexes[i_min], step3);
                int size = temp2.size() - 1;
                int originalIndex = indexes[i_min]; 
                 for (int i = 0; i < size; i++) {
                hashVal = (hashVal + step3) % data_vec.size();
                 if (hashVal < 0) {
                     hashVal += data_vec.size(); 
                }
            }

                //Doing the change
                data_vec[hashVal].data = data_vec[indexes[i_min]].data;
                data_vec[hashVal].valid = true;
                data_vec[indexes[i_min]].data = key;
                
            }
            
              
            else {
                data_vec[indexes[i_min]].data = key;
                data_vec[indexes[i_min]].valid = true; 
            
            }
            
        }
        
        
    }
    
   

}



int Brent::find_num_probes(int key) const{
    int probes = 1;
    int index = hash(key);
    int step = hash2(key);

    while (data_vec[index].data != key) {
        index = (index + step) % data_vec.size();
        probes++;
    }

    return probes;

}



double Brent::find_average_num_probes() const{
    double probes = 0.0;
    int valid = 0;

    for (int i = 0; i < data_vec.size(); ++i) {
        if (data_vec[i].valid) {
            probes += find_num_probes(data_vec[i].data);
            valid++;
        }
    }
    double result = probes / valid;
    return result;
}