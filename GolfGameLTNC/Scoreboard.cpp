#include"headers\Scoreboard.h"


void Scores::nextScore(Scores** head, int data) {
	Scores* p = new Scores();
	p->data = data;
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
	std::string s = "headers/high.txt";
	std::ifstream infile;
	infile.open(s.c_str());
	while (infile >> sc && i<5) {
		nextScore(head, sc);
		i++;
	}
	infile.close();
}

void Scores::insertsort(Scores** head, int data) {
	Scores* p = new Scores();

	p->data = data;
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

int Scores::getScore(int n) {
	Scores* head = this;
	int i = 0, ans=-1;
	while (head != NULL && i <=n) {
		ans = head->data;
		head = head->next;
		i++;
	}
	return ans;
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
		outfile << p->data << std::endl;
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