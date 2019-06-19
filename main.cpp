#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <dos.h>
#include <fstream.h>

struct cand
{
	char cname[40];
	int votes;
	char cls[5];
};

struct post
{
	char pname[30];
	post *link;
	cand *clist[20];
	int cno;
};

post *top = NULL;

void newpost()
{
	post *temp = new post;
	post *save;
	cout << "Enter name of post:" << endl;
	gets(temp->pname);
	(temp->link) = NULL;
	(temp->cno) = 0;
	for (int i = 0; i < 20; i++)
		(temp->clist[i]) = NULL;
	if (top == NULL)
		top = temp;
	else
	{
		save = top;
		top = temp;
		(temp->link) = save;
	}
	cout << "Post added\n\n";
}

void newcand()
{
	cand *newc = new cand;
	char p[30];
	post *temp;
	temp = top;
	cout << "Enter the name of the candidate:" << endl;
	gets(newc->cname);
	cout << "Enter the class of the candidate (eg:10c):" << endl;
	gets(newc->cls);
	(newc->votes) = 0;
	cout << "Enter the post that the candidate is competing for:" << endl;
	gets(p);
	while ((temp != NULL) && (strcmpi(p, (temp->pname)) != 0))
	{
		temp = (temp->link);
	}
	if (temp == NULL)
		cout << "Post not found\n";
	else
	{
		(temp->clist[(temp->cno)]) = newc;
		(temp->cno)++;
		cout << "Candidate added\n";
	}
	cout << endl;
}

void pdisp()
{
	post *temp;
	temp = top;
	int i = 1, flag = 0;
	while (temp != NULL)
	{
		cout << "Post " << i << ':' << (temp->pname) << endl;
		temp = (temp->link);
		i++;
		flag = 1;
	}
	if (flag == 0)
		cout << "No posts found\n";
	cout << endl;
}

void cdisp()
{
	char p[30];
	post *temp;
	temp = top;
	cout << "Please enter the post of the candidate\n";
	gets(p);
	while ((temp != NULL) && (strcmpi(p, (temp->pname)) != 0))
	{
		temp = (temp->link);
	}
	if (temp == NULL)
		cout << "Post not found\n";
	else
	{
		for (int i = 0; i < (temp->cno); i++)
		{
			cout << "Candidate " << (i + 1) << ":\nName:" << (temp->clist[i] - > cname) << "\nClass:" << (temp->clist[i] - > cls) << "\nVotes:" << (temp->clist[i] - > votes) << "\n\n";
		}
	}
	cout << endl;
}

void vote()
{
	post *temp;
	temp = top;
	int ch, flag = 0;
	while (temp != NULL)
	{
		flag = 1;
		cout << "Post:\n"
			 << (temp->pname) << endl;
		for (int i = 0; i < (temp->cno); i++)
		{
			cout << "Candidate " << (i + 1) << ":\nName:" << (temp->clist[i] - > cname) << "\tClass:" << (temp->clist[i]->cls) << endl;
		}
		cout << "Enter your choice:\n";
		cin >> ch;
		for (i = 0; i < (temp->cno); i++)
		{
			if ((i + 1) == ch)
				(temp->clist[i]->votes)++;
		}
		temp = (temp->link);
		cout << "Vote casted\n\n";
	}
	if (flag == 0)
		cout << "No posts found\n\n";
}

void winner()
{
	post *temp;
	temp = top;
	int highest = 0, flag = 0;
	while (temp != NULL)
	{
		flag = 1;
		cout << "Post:\n"
			 << (temp->pname) << endl;
		for (int i = 0; i < (temp->cno); i++)
		{
			if (highest < (temp->clist[i]->votes))
				highest = (temp->clist[i]->votes);
		}
		for (i = 0; i < (temp->cno); i++)
		{
			if (highest == (temp->clist[i]->votes))
				cout << "Winner is:" << (temp->clist[i]->cname) << "\tFrom class:" << (temp - > clist[i]->cls) << endl;
		}
		temp = (temp->link);
		cout << endl;
	}
	if (flag == 0)
		cout << "No posts found\n\n";
}

void pdel()
{
	char p[30];
	int flag = 0;
	cout << "Enter name of post to be deleted\n";
	gets(p);
	post *temp, *save;
	temp = top;
	while (temp != NULL)
	{
		flag = 1;
		if (strcmpi(p, (temp->link->pname)) == 0)
		{
			save = (temp->link);
			(temp->link) = (temp->link->link);
			for (int i = 0; i < (save->cno); i++)
				delete (save->clist[i]);
			delete save;
			cout << "The post and all its candidates were deleted\n\n";
			goto lab3;
		}
	}
	if (flag == 0)
		cout << "No posts found\n\n";
lab3:
}

void cdel()
{
	post *temp;
	temp = top;
	int i, flag = 0, flag1 = 0;
	char p[40];
	cout << "Enter candidate to be removed\n";
	gets(p);
	while (temp != NULL)
	{
		flag = 1;
		for (i = 0; i < (temp->cno); i++)
		{
			if (strcmpi(p, (temp->clist[i]->cname)) == 0)
			{
				delete (temp->clist[i]);
				(temp->cno)--;
				cout << "Candidate deleted\n\n";
				flag1 = 1;
				goto lab1;
			}
		}
	}
	if (flag == 0)
		cout << "No posts found\n";
	if (flag1 == 0)
		cout << "No candidates found\n\n";
lab1:
}

void store()
{
	fstream fout;
	post *temp = top;
	fout.open("Votes.DAT", ios::out | ios::binary);
	while (temp != NULL)
	{
		fout.write((char *)temp, sizeof(post));
		for (int i = 0; i < (temp->cno); i++)
		{
			fout.write((char *)temp->clist[i], sizeof(cand));
		}
		temp = temp->link;
	}
	fout.close();
}


void main()
{
	clrscr();
	int ch1, ch2, ch6;
	char ch3 = 'y', ch4 = 'y', ch5 = 'y', ch7 = 'y', ch8 = 'y';
	char pw[20], pc[20];
	cout<<"WELCOME TO THE PSBS VOTING PROGRAM\nBy Raunak, Sharon and
	Parth\n(Loading";
	delay(1000); cout<<'.'; delay(1000); cout<<'.'; delay(1000); cout<<".)"; delay(1000);
	cout<<"\nSet new admin password:\n";
	gets(pw);
	while(ch7=='y'||ch7=='Y')
	{
		clrscr();
		set:
			cout << "Are you an Administrator(1) or a Voter(2)? (1/2)\nPress 3 to exit\n";
			cin >> ch1;
			switch (ch1)
			{
				case 1:
					cout << "Enter password (case sensitive):\n";
					gets(pc);
					if (strcmp(pc, pw) != 0)
					{
						cout << "Wrong password\n";
						goto lab2;
					}
					else
					{
						ch4 = 'y';
						while (ch4 == 'y' || ch4 == 'Y')
						{
							clrscr();
							cout<< "Would you like to:\n"
								<< "1:Enter new posts\n";
							cout<<" 2:Enter new candidate (Warning: Need to enter post of candidate
							beforehand, Max 20 per post)\n";
							cout<<" 3:List all posts\n"
								<<" 4:List all candidates for a particular post\n";
							cout<< "5:Show the winner of every post\n"
								<< "6:Delete a
								post\n "
								<<" 7 : Delete a candidate\n ";
							cout<< "8:Return to welcome screen\n";
							cout<< "9:Save and exit\n";
							cin >> ch2;
							switch (ch2)
							{
								case 1:
									clrscr();
									newpost();
									break;
								case 2:
									clrscr();
									newcand();
									break;
								case 3:
									clrscr();
									pdisp();
									break;
								case 4:
									clrscr();
									ch3 = 'y';
									while (ch3 == 'y' || ch3 == 'Y')
									{
										clrscr();
										cdisp();
										cout << "Would you like to check candidate list for a different
											post
											? (y / n)\n ";
												cin >>
												ch3;
									}
									cout << endl;
									break;
								case 5:
									clrscr();
									winner();
									break;
								case 6:
									clrscr();
									pdel();
									break;
								case 7:
									clrscr();
									cdel();
									break;
								case 8:
									clrscr();
									goto set;
									break;
								case 9:
									goto lab;
									break;
								default:
									cout << "Invalid choice\n\n";
									break;
							}
							cout << "Would you like to return to Administrator Main Menu? (y/n)\n";
							cin >> ch4;
						}
						cout << endl;
					}
					break;
				case 2:
					ch5 = 'y';
					while (ch5 == 'y' || ch5 == 'Y')
					{
						clrscr();
						cout << "Would you like to:\n"
							<< "1:List all posts\n";
						cout << "2:List all candidates for a post\n";
						cout << "3:Vote for a candidate for each post\n";
						cout << "4:Return to welcome screen\n"
							<< "5:Save and exit\n";
						cin >> ch6;
						switch (ch6)
						{
							case 1:
								clrscr();
								pdisp();
								break;
							case 2:
								clrscr();
								ch8 = 'y';
								while (ch8 == 'y' || ch8 == 'Y')
								{
									clrscr();
									cdisp();
									cout << "Would you like to check candidate list for a different post?
											(y / n)\n ";
											cin >>
										ch8;
								}
								cout << endl;
								break;
							case 3:
								clrscr();
								vote();
								break;
							case 4:
								clrscr();
								goto set;
								break;
							case 5:
								goto lab;
								break;
							default:
								cout << "Invalid choice\n\n";
								break;
						}
						cout << "Would you like to return to Voter main menu? (y/n)\n";
						cin >> ch5;
					}
					cout << endl;
					break;
				case 3:
					goto lab;
					break;
				default:
					cout << "Invalid choice\n\n";
			}
		lab2:
			cout << "Would you like to return to the main menu? (y/n)\n";
			cin >> ch7;
			cout << endl;
	}
	lab:
	clrscr();
	store();
	getch();
}