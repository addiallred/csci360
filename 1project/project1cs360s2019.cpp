#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct tile
{
	int row;
	int col;
	int f;
	int g; 
	int h;
};

class CompareTile {
public:
    bool operator()(tile& t1, tile& t2)
    {
    	//max
       if (t1.f > t2.f){
       	return false;
       }
       //will probably want to change based on what the h and g value are
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
int aStar(int c, int** grid, int n, int a){
	vector< vector<int> > gridV;
	for(int i = 0; i < n; i++){
		vector<int> temp;
		for(int j = 0; j < n; j++){
			temp.push_back(grid[i][j]);
		}
		gridV.push_back(temp);
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << gridV[i][j];
		}
		cout << endl;
	}
	priority_queue<tile, vector<tile>, CompareTile> queue;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int f = gridV[i][j] + 2;
			//will come in here later once i have figured out a good heuristic
			//for now i will leave it as it is
			tile temp = { i, j, f, gridV[i][j], 0};
			queue.push(temp);
		}
	}
	int score = 0;
	//my problem is once i have popped all of them, it does not 
	//have anything to back track to so first my heuristic could not be
	//correct and or i do need to do some type of back tracking
	//to make sure it is correct
	while(c > 0){
		vector<tile> explored;
		tile top = queue.top();
		queue.pop();
		bool safeP = safe(grid, top.row, top.col, n);
		//i am thinking probably will change something along this line
		//if it isn't a safe option, however it has a higher value, than 
		//it there ar no longer any options than perhaps we start a new iteration
		if(safeP){
			c--;
			grid[top.row][top.col] = -2;
			explored.push_back(top);
			score += gridV[top.row][top.col];
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
	int results;
	int resultsA = 0;
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