#include"headers\Scoreboard.h"


void Scores::nextScore(Scores** head, int data, std::string name) {
	Scores* p = new Scores();
	p->data = data;
	p->name = name;
	p->next = NULL;

	if (*head == NULL) {
		*head = p;
		return;
	}

	Scores* tmp = *head;
	while (tmp->next != NULL) tmp = tmp->next;
	tmp->next = p;
}

void Scores::topscores(Scores** head) {
	int sc,i=0;
	std::string scn;
	std::string s = "headers/high.txt";
	std::ifstream infile;
	infile.open(s.c_str());
	while (infile >> sc && infile >> scn && i<5) {
		nextScore(head, sc, scn);
		i++;
	}
	infile.close();
}

void Scores::insertsort(Scores** head, int data, std::string name) {
	Scores* p = new Scores();

	p->data = data;
	p->name = name;
	// since this will be the last Scores so it will point to NULL
	p->next = NULL;

	if (*head == NULL) {
		*head = p;
		return;
	}

	Scores* temp = *head;
	if (temp->data >= data) {
		p->next = temp;
		*head = p;
		return;
	}
	while (temp->next != NULL) {
		if (temp->next->data >= data && temp->data <= data) {
			Scores* temp1 = temp->next;
			temp->next = p;
			p->next = temp1;
			return;
		}
		else temp = temp->next;
	}
	temp->next = p;
}

Scores* Scores::getScore(int n) {
	Scores* head = this;
	int i = 0;
	Scores* ans = head;
	while (head != NULL && i <=n) {
		ans = head;
		head = head->next;
		i++;
	}
	return ans;
}

int Scores::getdata() {
	if (this == NULL) return -1;
	return data;
}

std::string Scores::getname() {
	if (this == NULL) return "";
	return name;
}

int Scores::count(){
	int i = 0;
	Scores* p = this;
	while (p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}

void Scores::display() {
	Scores* p = this;
	while (p != NULL) {
		std::cout << p->data << " ";
		p = p->next;
	}
	std::cout<<std::endl;
}

void Scores::save() {
	Scores* p = this;
	std::string s = "headers/high.txt";
	std::ofstream outfile;
	outfile.open(s.c_str());
	while (p!=NULL) {
		outfile << p->data <<" "<< p->name<< std::endl;
		p = p->next;
	}
	outfile.close();
}

void Scores::deletelist(Scores** head) {
	Scores* current = *head;
	Scores* next = NULL;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	*head = NULL;
}