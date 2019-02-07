#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
//need to change to possibilities, have it have a vector of tiles that
//it can see
struct tile{
	int row;
	int col;
	int openPoint;
	int points;
};
struct configerations
{
	vector<tile> tiles;
	int f;
	int g; //number of points that are gained by placing a camera here 
	int h; //number of points for gain
	vector<vector<int> > grid;
};

class CompareTile {
public:
    bool operator()(configerations& t1, configerations& t2)
    {
    	//max
       if (t1.f > t2.f){
       	return false;
       }
       //will probably want to change based on what the h and g value are
       else if(t1.f < t2.f){
       	return true;
       }
       else if(t1.g > t2.g){
       	return false;
       }else if(t1.g < t2.g){
       	return true;
       }else if(t1.h > t2.h){
       	return false;
       }
       return true;
   }
};
void print(int** grid, int n){
	cout << "***********************" << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}
void printV(vector<vector<int> > grid, int n){
	cout << "********************88" << endl;
	cout << grid[0][0] << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << grid[i][j];
		}cout << endl;
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
//for placeC try to check the number of points that are left
//and compar it to the number of available animals that are left
//work on optimization after finishing astar
int placeC(int c, int** grid, int n, int a, int points, int max, int startR){
	if(startR > n){
		return 0;
	}
	if(c <= 0){
		return points;
	}
	for(int i = startR; i < n; i++){
		for(int j = 0; j < n; j++){
			bool safeP = safe(grid, i, j, n);
			if(safeP){
				int original = grid[i][j];
				grid[i][j] = -2;
				int points2 = points;
				int maxTemp = placeC(c-1, grid, n, a, points2 += original, max, i+1);
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
			int points = placeC(c-1, grid, n, a, original, max, i+1);
			if(points > max){
				max = points;
			}
			grid[i][j] = original;
			
		}
	}
	return max;
}
int conflicts(vector<vector<int> > grid, int n, int row, int col){
	grid[row][col] = 0;
	int numCons = 0;
	int i = 0; 
	int j = 0;
	for(i = 0; i < n; i++){
		if(grid[row][i] > 0){
			numCons++;
		}if(grid[i][col] > 0){
			numCons++;
		}
	}for(i = row, j = col; i < n && j < n; i++, j++){
		if(grid[i][j] > 0){
			numCons++;
		}
	}for(i = row, j = col; i < n && j >= 0; i++, j--){
		if(grid[i][j] > 0){
			numCons++;
		}
	}for(i = row, j = col; i >= 0 && j < n; i--, j++){
		if(grid[i][j] > 0){
			numCons++;
		}
	}for(i = row, j = col; i >= 0 && j >= 0; i--, j--){
		if(grid[i][j] > 0){
			numCons++;
		}
	}
	return numCons;
}
vector<int> heurisCalc(vector<vector<int > > grid, int n){
	int openSpace = 0;
	int pointsG = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(grid[i][j] >= 0){
				openSpace++;
				pointsG += grid[i][j];
			}
		}
	}
	vector<int> results;
	results.push_back(openSpace);
	results.push_back(pointsG);
	return results;
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
int aStar(int c, int** grid, int n, int a){
	priority_queue<configerations, vector<configerations>, CompareTile> queue;
	vector< vector<int> > gridV;
	for(int i = 0; i < n; i++){
		vector<int> temp;
		for(int j = 0; j < n; j++){
			temp.push_back(grid[i][j]);
		}
		gridV.push_back(temp);
	}
	printV(gridV, n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			vector<vector<int> > gridUp = safe(gridV, i, j, n);
			gridUp[i][j] = -2;
			int camera = c-1;
			vector<int> results = heurisCalc(gridUp, n);
			int openSpaces = results[0];
			int points = results[1];
			if(openSpaces >= camera){
				tile temp = {i, j, points, gridV[i][j]};
				vector<tile> tileV;
				tileV.push_back(temp);
				int f = temp.points + points;
				configerations tempResult = {tileV, f, temp.points, points, gridUp};
				queue.push(tempResult);
			}
			
		}
	}
	int score = 0;
	bool allCP = false;
	vector<configerations> explored;
	//make sure that the tiles are in there by order so that it can be easy to compare if we already
	//have a configuration in there but could do this when working on optimizing
	while(!allCP){
		configerations top = queue.top();
		queue.pop();
		cout << top.f << endl;
		if(top.tiles.size() == c){
			score = top.g;
			allCP = true;
		}
		vector<vector<int> > gridTiles = top.grid;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(gridTiles[i][j] > -1){
					vector<tile> currentTile = top.tiles;
					int newP = top.g + gridTiles[i][j];
					//could maybe optimize this by just having a vector that stores the number of confilcts 
					//per vectors
					vector<vector<int> > gridUp = safe(gridTiles, i, j, n);
					gridUp[i][j] = -2;
					cout << "trying this" << endl;
					vector<int> results = heurisCalc(gridUp, n);
					int openSpace = results[0];
					cout << openSpace << endl;
					int pointsAvailable = results[1];
					cout << pointsAvailable << endl;
					if(openSpace >= c - currentTile.size()){
						int newF = newP + pointsAvailable; 
						tile temp = {i, j, pointsAvailable, gridTiles[i][j]};
						currentTile.push_back(temp);
						configerations newCon = {currentTile, newF, newP, pointsAvailable, gridUp};
						queue.push(newCon);
					}
				}
			}
		}
	}
	return score;
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
	int results = 0;
	int resultsA = 0;
	if(algorithm == "dfs"){
		results = dfs(c, grid, n, a);
		resultsA = aStar(c, grid, n, a);
	}else{
		results = aStar(c, grid, n, a);
	}
	input.close();
	ofstream outfile;
	outfile.open("output.txt");
	outfile << results;
	outfile << " " << resultsA;
	outfile.close();
	return 0;
}