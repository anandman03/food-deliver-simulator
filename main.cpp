#include <bits/stdc++.h>
using namespace std;

class deliverySimulation {
private:
	unordered_set<string> restaurant;
	unordered_map<string, vector<string>> area;
	unordered_map<string, string> deliveryPerson;
	unordered_map<string, vector<pair<string, int>>> graph;
	
public:
	deliverySimulation() {
		area = {};
		graph = {};
		restaurant = {};
		deliveryPerson = {};
		srand(time(NULL));
	}

	void addEdge(const string& src, const string& dst, const int& val) {
		graph[src].push_back({dst, val});
		graph[dst].push_back({src, val});
	}

	void addRestaurant(const string& name) {
		restaurant.insert(name);
	}

	void addDeliveryPerson(const string& name, const string& blockLocation) {
		deliveryPerson[name] = blockLocation;
		area[blockLocation].push_back(name);
	}

	pair<int, string> findShortestPath(const string& src, const string& restaurantName) {
		pair<int, string> forDeliveryPerson = shortestPathToRestaurant(restaurantName);
		int forOrder = shortestPathToSource(src, restaurantName);

		pair<int, string> answer = {forOrder + forDeliveryPerson.first, forDeliveryPerson.second};
		return answer;
	}

	pair<int, string> shortestPathToRestaurant(const string& restaurantName) {
		priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> priorityQueue;
		priorityQueue.push({0, restaurantName});

		unordered_map<string, int> distance;
		distance[restaurantName] = 0;

		while(!priorityQueue.empty()) {
			pair<int, string> current = priorityQueue.top();
			priorityQueue.pop();

			int currentCost = current.first;
			string currentBlock = current.second;

			if(area.count(currentBlock)) {
				string name = getRandom(area[currentBlock]);
				return {currentCost, name};
			}

			for(pair<string, int> p : graph[currentBlock]) {
				if(!distance.count(p.first) || distance[p.first] > currentCost + p.second) {
					distance[p.first] = currentCost + p.second;
					priorityQueue.push({distance[p.first], p.first});
				}
			}
		}
		return {0, "Not Found"};
	}

	int shortestPathToSource(const string& src, const string& restaurantName) {
		priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> priorityQueue;
		priorityQueue.push({0, restaurantName});

		unordered_map<string, int> distance;
		distance[restaurantName] = 0;

		while(!priorityQueue.empty()) {
			pair<int, string> current = priorityQueue.top();
			priorityQueue.pop();

			int currentCost = current.first;
			string currentBlock = current.second;

			if(currentBlock == src) {
				return currentCost;
			}

			for(pair<string, int> p : graph[currentBlock]) {
				if(!distance.count(p.first) || distance[p.first] > currentCost + p.second) {
					distance[p.first] = currentCost + p.second;
					priorityQueue.push({distance[p.first], p.first});
				}
			}
		}
		return 0;
	}

	string getRandom(const vector<string>& persons) {
		int index = rand() % (int) persons.size();
		return persons[index];
	}

	bool findRestaurant(const string& name) {
		return restaurant.count(name);
	}

	bool findBlock(const string& block) {
		return graph.count(block);
	}
};

int32_t main()
{
	
	deliverySimulation d;

	int n1; cin >> n1;
	for(int i = 0 ; i < n1 ; ++i) {
		string src, dst;
		int value;
		cin >> src >> dst >> value;
		d.addEdge(src, dst, value);
	}

	int n2; cin >> n2;
	for(int i = 0 ; i < n2 ; ++i) {
		string name; cin >> name;
		d.addRestaurant(name);
	}

	int n3; cin >> n3;
	for(int i = 0 ; i < n3 ; ++i) {
		string name, block; 
		cin >> name >> block;
		d.addDeliveryPerson(name, block);
	}

	string block, restaurant;
	cin >> block >> restaurant;
	if(!d.findBlock(block)) {
		cout << "No Block Found\n";
	}
	if(!d.findRestaurant(restaurant)) {
		cout << "No Restaurant Found\n";
	}

	pair<int, string> ans = d.findShortestPath(block, restaurant);
	cout << ans.first << ' ' << ans.second << '\n';

	return 0;
}