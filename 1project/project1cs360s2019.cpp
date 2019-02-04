#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int max = 0; 
//set this to a gload variable for max;
int** updateGrid(int grid[n][n], int row, int col, int n){
	for(int i = 0; i < n; i++){
		if(i != col){
			grid[row][i] = -1;
		}
	}for(int i = 0; i < n; i++){
		if(i != row){
			grid[i][col] = -1;
		}
	}for(int i = row + 1; i < n; i++){
		for(int j = col + 1; i < n; i++){
			grid[i][j] =  -1;
		}for(int j = col - 1; j > 0; j--){
			grid[i][j] = -1;
		}
	}for(int i = row-1; i > 0; i--){
		for(int j = col-1; j > 0; j--){
			grid[i][j] = -1;
		}for(int j = col + 1; j < n ; j++){
			grid[i][j] = -1;
		}
	}
	return grid;
}
//need to 
void placeC(int c, int grid[n][n], int n, int a, int points){
	if(c <= 0){
		if(points > max){
			max = points;
		}
		return;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(grid[i][j] != -1 && grid[i][j] != -2){
				int original = grid[i][j];
				grid[i][j] = -2;
				int** grid2 = updateGrid(grid, i, j, n);
				placeC(c-1, grid2, n, a, points += original);
				grid[i][j] = original;
			}
		}
	}
}
int dfs(int c, int** grid, int n, int a){
	for(int i = 0; i <= n-c; i++){
		for(int j = 0; j < n; j++){
			int original = grid[i][j];
			grid[i][j] = -2; //-2 a camera is in that location
			placeC(c-1, grid, n, a, original);
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
	if(algorithm == "dfs"){
		int results = dfs(c, grid, n, a);
	}else{
		aStar(c, grid, n, a);
	}
	cout << results << endl;
	return 0;
}