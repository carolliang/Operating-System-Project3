#include <iostream>
#include "memory_manager.h"
#include<vector>
using namespace std;


unsigned long long memory_manager::memoryAccess(unsigned long long address){
	unsigned long long p_addr;
	if (policy == FIFO){
		int pagesize = pow(2, N);
		int pagenumber = address / pagesize;
		int framnumber = firstinfirstout(numFrames, pagenumber, counter, frames);
		p_addr = framnumber* pow(2, N) + address % pagesize;
	}
	if (policy == LRU)
	{
		int pagesize = pow(2, N);
		int pagenumber = address / pagesize;
		int framnumber = leastrecent(numFrames, pagenumber, head,counter, LRUhit);
		p_addr = framnumber* pow(2, N) + address % pagesize;

	}
	return p_addr;
}

int memory_manager::firstinfirstout(unsigned int nF, unsigned int pagenumber, int &counter, vector<unsigned int>&frames){

	if (counter < nF)
	{
		if (!frames.empty() && frames.back() == pagenumber)
		{
			return counter;
		}
		else {
			frames.push_back(pagenumber);
			counter++;
			return counter - 1;
		}
	}
	else {
		for (int i = 0; i < nF; i++)
		{
			if (frames[i] == pagenumber)
			{
				return i;
			}
		}
		int index = counter%nF;
		frames[index] = pagenumber;
		swap(index, pagenumber);
		counter++;
		return index;
	}

}
int memory_manager::leastrecent(unsigned int numFrames, unsigned int pagenumber, ListNode* head, int& counter, bool& hit)// take index from list1 and take the least freq node from list2
{
	ListNode* curr = head;
	if (head == NULL)
	{
		head = new ListNode(pagenumber);
		counter++;
		return 0;
	}
	else if (counter < numFrames)
	{
		curr->next = new ListNode(pagenumber);
		curr = curr->next;
		counter++;
		return counter - 1;
	}

	else{
		curr = head;
		while (curr)
		{
			if (curr->val == pagenumber)
			{
				buildlist2(head, curr);
				break;
			}
			curr = curr->next;
		}
	}
}
ListNode* memory_manager::buildlist2(ListNode* head, ListNode* curr)
{

}