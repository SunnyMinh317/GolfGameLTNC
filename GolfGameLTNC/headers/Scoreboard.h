#pragma once
#include <iostream>
#include <fstream>

class Scores
{
private:
	int data;
	Scores* next;
	std::string name;
	
public:
	int count();
	void nextScore(Scores** head, int newscore, std::string newname );
	void topscores(Scores** head);
	void insertsort(Scores** head, int newscore, std::string newname);
	Scores* getScore(int n);
	int getdata();
	std::string getname();
	void display();
	void save();
	void deletelist(Scores** head);
};