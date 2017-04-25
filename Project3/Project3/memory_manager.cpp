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
		int framnumber = leastrecent(numFrames, pagenumber,counter);
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
int memory_manager::leastrecent(unsigned int numFrames, unsigned int pagenumber, int& counter)// take index from list1 and take the least freq node from list2
{

	if (counter < numFrames)// frame not full
	{
		if (mymap.empty())
		{
			mymap.insert(pair<int, int>(pagenumber, counter));
			counter++;
			return counter - 1;
		}
		else// not empty 
		{
			if (mymap.count(pagenumber) == 0)// no hit
			{
				mymap.insert(pair<int, int>(pagenumber, counter));
				counter++;
				return counter - 1;
			}
			else if (mymap.count(pagenumber) > 0)//hit
			{
				for (unordered_map<int, int>::iterator it = mymap.begin(); it != mymap.end(); it++)
				{
					if (it->first == pagenumber)
					{
						int temppgenumber = it->first;
						int tempframenumber = it->second;
						mymap.erase(it);
						mymap.insert(pair<int, int>(temppgenumber, tempframenumber));
						return tempframenumber;
					}
				}
			}
		}
	}

	else// frame is full
	{
		if (mymap.count(pagenumber) > 0)//hit
		{
			for (unordered_map<int, int>::iterator it = mymap.begin(); it != mymap.end(); it++)
			{
				if (it->first == pagenumber)
				{
					int temppgenumber = it->first;
					int tempframenumber = it->second;
					mymap.erase(it);
					mymap.insert(pair<int, int>(temppgenumber, tempframenumber));
					return tempframenumber;
				}
			}
		}
		else if (mymap.count(pagenumber) == 0)//not hit 1save frame number 2. delete head of the map 3 insert new pagenumber with old fram number return framenumber 
		{
			unordered_map<int, int>::iterator it = mymap.begin();
			int framenumber = it->second;
			mymap.erase(it);
			mymap.insert(pair<int, int>(pagenumber, framenumber));
			swap(framenumber, pagenumber);
			return framenumber;
		}


	}
}


