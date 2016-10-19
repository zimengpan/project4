// ENGR 151
// Project 4
// Filename: project4.cpp
//
// Authors: Zimeng Pan (lab section: 101)
// Uniqnames: zmpan
//
// Date Created: Oct. 16th
// Date Submitted: 
//
// Program Description:
// Decryption of pixel info by functions specified in orders

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct lairInfo{
    int ID;
    int total_money;
    string key;
    int alarm;
    string name;
    string decrypt;
    int x;
    int y;
};

// Decryption
string decrypt(string encrypted){
    // Remove all adjacent duplicate characters
    for(int i = 0; i < encrypted.size(); i++){
        if(encrypted[i] == encrypted[i+1]){
            int count = 0;
            for(int j = i+1; j < encrypted.size(); j++){
                if(encrypted[i] == encrypted[j]){
                    count++;
                } else {
                    break;
                }
            }
            encrypted.erase(i+1, count);
        }
    }

    // cout << encrypted << endl;
    // Remove all instances of the first three characters
    string temp = encrypted.substr(0,3);
    while(encrypted.find(temp) != encrypted.npos){
        encrypted.erase(encrypted.find(temp),3);
    }

    // cout << encrypted << endl;
    // If the fist and last two characters match, shift all characters up by 3 in the ACSII map; otherwise, shift by 5
    if(encrypted.substr(0,2) == encrypted.substr(encrypted.size()-2,2)){
        for(int i = 0; i < encrypted.size(); i++){
            encrypted[i] = encrypted[i] + 3;
        }
    } else {
        for(int j = 0; j < encrypted.size(); j++){
            encrypted[j] = encrypted[j] + 5;
        }
    }
    encrypted.erase(0,2);
    encrypted.erase(encrypted.size()-2,2);
    return encrypted;
}

// Path Finding
int dist(int x1,int y1, int x2, int y2){
    int dist = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    return dist;
}

int pathFind(int n, int x0, int y0, vector <lairInfo> map){
    int minDist = dist(x0, y0, map[0].x, map[0][3]);
    int minID = map[0][1];
    for(int i=1; i < n; i++){
        if(minDist > dist(x0, y0, map[i][2], map[i][3])){
            minDist = dist(x0, y0, map[i][2], map[i][3]);
            minID = map[i][1];
        } else if(minDist == dist(x0, y0, map[i][2], map[i][3]) || minID > map[i][1]){
            minID = map[i][1];
        }
    }
    return minID;
}


int main(){
    ifstream in_lair("lair.txt");
    ifstream in_rob("robbery.txt");
    ifstream in_map("map.txt");
    ofstream out_bonty("bounty.txt");
    ofstream out_failure("failure.txt");

    string key, name,decrypt,init_map;
    int ID, total_money, alarm, num, x_0, y_0, x_f, y_f;

    // Initialize a vector of struct lairInfo
    vector <lairInfo> info;
    int i = 0;
    in_map >> num >> x_0 >> y_0 >> x_f >> y_f;
    while(in_lair >> ID){
        info[i].ID = ID;
        in_lair >> total_money;
        info[i].total_money = total_money;
        in_lair >> key;
        info[i].key = key;
        in_lair >> alarm;
        info[i].alarm = alarm;
        in_lair >> name;
        info[i].name = name;
        in_rob >> decrypt;
        info[i].decrypt = decrypt;
        i++;
    }

}