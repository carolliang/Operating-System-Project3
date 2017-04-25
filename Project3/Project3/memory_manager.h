#include <iostream>
#include<vector>
#include "virtualMemoryManagerInterface.hpp"
#include <unordered_map>
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class memory_manager : public virtualMemoryManagerInterface{
public:
	memory_manager(ReplacementPolicy p, unsigned int pS, unsigned int nF, unsigned int vA) :virtualMemoryManagerInterface( p, pS, nF, vA){}
	int firstinfirstout(unsigned int nF, unsigned int pagenumber, int &counter, vector<unsigned int>&frames);
	int leastrecent(unsigned int numFrames, unsigned int pagenumber, int& counter);
	virtual unsigned long long memoryAccess(unsigned long long);
	ListNode* memory_manager::buildlist2(ListNode* head, ListNode* curr);
	int counter = 0;
	vector<unsigned int>frames;
	//ListNode* head =NULL;
	//ListNode* head2 = NULL;
	bool LRUhit = false;
	unordered_map<int, int>mymap;
};

