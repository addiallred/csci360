#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;



void print(int** grid, int n){
	cout << "***********************" << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}
//set this to a gload variable for max;
bool safe(int** grid, int row, int col, int n){
	int i = 0; 
	int j = 0;
	for(i = 0; i < n; i++){
		if(grid[row][i] == -2){
			return false;
		}else if(grid[i][col] == -2){
			return false;
		}
	}for(i = row, j = col; i < n && j < n; i++, j++){
		if(grid[i][j] == -2){
			return false;
		}
	}for(i = row, j = col; i < n && j < n; i++, j--){
		if(grid[i][j] == -2){
			return false;
		}
	}for(i = row, j = col; i >= 0 && j < n; i--, j++){
		if(grid[i][j] == -2){
			return false;
		}
	}for(i = row, j = col; i >= 0 && j >= 0; i--, j--){
		if(grid[i][j] == -2){
			return false;
		}
	}
	return true;
}

//need to 
int placeC(int c, int** grid, int n, int a, int points, int max){
	if(c <= 0){
		return points;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			bool safeP = safe(grid, i, j, n);
			if(safeP){
				int original = grid[i][j];
				grid[i][j] = -2;
				int points2 = points;
				int maxTemp = placeC(c-1, grid, n, a, points2 += original, max);
				if(maxTemp > max){
					max = maxTemp;
				}
				grid[i][j] = original;
			}
		}
	}
	return max;
}
int dfs(int c, int** grid, int n, int a){
	int max = 0;
	for(int i = 0; i <= n-c; i++){
		for(int j = 0; j < n; j++){
			int original = grid[i][j];
			grid[i][j] = -2; //-2 a camera is in that location
			int points = placeC(c-1, grid, n, a, original, max);
			if(points > max){
				max = points;
			}
			grid[i][j] = original;
			
		}
	}
	return max;
}
int aStar(int c, int** grid, int n, int a){
	
	return 0;
}

int main(int argc, char* argv[]){
	if(argc < 2){
		cout << "Provide input file" << endl;
		return 0;
	}
	int n = 0;
	int c = 0;
	int a = 0;
	string algorithm = "";
	ifstream input(argv[1]);
	string line;
	if(input.is_open()){
		getline(input, line);
		n = stoi(line);
		getline(input, line);
		c = stoi(line);
		getline(input, line);
		a = stoi(line);
		getline(input, line);
		algorithm = line;
	}
	else{
		return 0;
	}
	int** grid = new int*[n];
	for(int i = 0; i < n; ++i){
    	grid[i] = new int[n];
    	for(int j = 0; j < n; j++){
    		grid[i][j] = 0;
    	}
	}
	while(getline(input, line)){
		char line1 = line[0];
		char line2 = line[2];
		int i = line1 - '0';
		int j = line2 - '0';
		grid[i][j]++;
	}
	int results;
	if(algorithm == "dfs"){
		results = dfs(c, grid, n, a);
	}else{
		results = aStar(c, grid, n, a);
	}
	input.close();
	ofstream outfile;
	outfile.open("output.txt");
	outfile << results;
	outfile.close();
	return 0;
}