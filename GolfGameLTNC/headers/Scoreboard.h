#pragma once
#include <iostream>
#include <fstream>

class Scores
{
private:
	int data;
	Scores* next;
	
public:
	int count();
	void nextScore(Scores** head, int newscore);
	void topscores(Scores** head);
	void insertsort(Scores** head, int newscore);
	int getScore(int n);
	void display();
	void save();
	void deletelist(Scores** head);
};