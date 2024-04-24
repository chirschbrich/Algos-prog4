#include <iostream>
#include <vector>
#include <algorithm>
#include "prog4.h"

using namespace std;

// This is used for sorting list of applicants 
struct CompareId {
   bool operator()(const Applicant& a1, const Applicant& a2) {return (a1.id < a2.id);};
} compare1;

// input of applicants
istream& operator>>(istream& is, Applicant& a)
{
   is >> a.id >> a.cost >> a.benefit;
   return is;
}

// output of applicants
ostream& operator<<(ostream& os, Applicant& a)
{
   os << a.id << " (" << a.cost <<  " " << a.benefit << ")";
   return os;
}


pair<int, vector<Applicant> >pickTeam(int budget, vector< vector<Applicant> >& alist);

main()
{
    float budget;
    int p, k;
    vector< vector<Applicant> > alist;
    
    //  read data from input
    cin >> budget >> p >> k;
    for (int i = 0; i < p; i++)
	{
	   vector<Applicant> curlist;
           for (int j = 0; j < k; j++)
		{
		    Applicant app;	
		    cin >> app;
		    curlist.push_back(app);
		}
          alist.push_back(curlist);
	}

    // display list of applicants

    for (int i = 0; i < alist.size(); i++)
	{
    	    for (int j = 0; j < alist[i].size(); j++)
		cout << alist[i][j] << " ";
 	    cout << endl;
	}
   
    // finding the optimal team
    pair<int, vector<Applicant> > res = pickTeam(budget,  alist);

    // sort the list of selected applicants by id
    sort(res.second.begin(), res.second.end(), compare1);

    // output the results
    cout << "=========\n";
    cout << res.first << " | ";
    for (int i = 0; i < res.second.size(); i++)
	cout << res.second[i] << " ";
    cout <<endl;

    return(0);
}
