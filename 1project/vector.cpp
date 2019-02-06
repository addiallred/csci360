#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void print(vector<vector<int> > grid, int n){
	cout << "********************88" << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << grid[i][j];
		}cout << endl;
	}
}
vector<vector<int> > safe(vector<vector<int > > grid, int row, int col, int n){
	int i = 0; 
	int j = 0;
	for(i = 0; i < n; i++){
		if(grid[row][i] != -2){
			grid[row][i] = -1;
		}if(grid[i][col] != -2){
			grid[i][col] = -1;
		}
	}for(i = row, j = col; i < n && j < n; i++, j++){
		if(grid[i][j] != -2){
			grid[i][j] = -1;
		}
	}for(i = row, j = col; i < n && j >= 0; i++, j--){
		if(grid[i][j] != -2){
			grid[i][j] = -1;
		}
	}for(i = row, j = col; i >= 0 && j < n; i--, j++){
		if(grid[i][j] != -2){
			grid[i][j] = -1;
		}
	}for(i = row, j = col; i >= 0 && j >= 0; i--, j--){
		if(grid[i][j] != -2){
			grid[i][j] = -1;
		}
	}
	return grid;
}
int placeC(int c, vector<vector<int> > grid, int n, int a, int points, int max, int startR){
	if(c <= 0){
		return points;
	}
	for(int i = startR; i < n; i++){
		for(int j = 0; j < n; j++){
			if(grid[i][j] > -1){
				vector<vector<int> > grid2 = safe(grid, i, j, n);
				grid2[i][j] = -2;
				int points2 = points;
				points2 += grid[i][j];
				int maxTemp = placeC(c-1, grid2, n, a, points2, max, startR);
				if(maxTemp > max){
					max = maxTemp;
				}
			}
		}
	}
	return max;
}
int dfs(int c, vector<vector<int> > grid, int n, int a){
	int max = 0;
	for(int i = 0; i < (n-c+ 1); i++){
		for(int j = 0; j < n; j++){
			int original = grid[i][j];
			vector<vector <int> >grid2 = safe(grid, i, j, n);
			grid2[i][j] = -2;
			int points = placeC(c-1, grid2, n, a, original, max, i);
			if(points > max){
				max = points;
			}
			grid[i][j] = original;
		}
	}
	return max;
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
	vector<vector<int> > grid;
	for(int i = 0; i < n; i++){
		vector<int> temp;
		for(int j = 0; j < n; j++){
			temp.push_back(0);
		}
		grid.push_back(temp);
	}
	while(getline(input, line)){
		char line1 = line[0];
		char line2 = line[2];
		int i = line1 - '0';
		int j = line2 - '0';
		grid[i][j]++;
	}
	int results;
	int resultsA = 0;
	if(algorithm == "dfs"){
		results = dfs(c, grid, n, a);
	}else{
		//results = aStar(c, grid, n, a);
	}
	input.close();
	ofstream outfile;
	outfile.open("output.txt");
	outfile << results;
	outfile.close();
	return 0;
}