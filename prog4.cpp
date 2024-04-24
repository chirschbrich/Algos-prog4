#include <iostream>
#include <vector>
#include <algorithm>
#include "prog4.h"


istream& operator>>(istream& is, Applicant& a);
ostream& operator<<(ostream& os, Applicant& a);

pair<int, vector<Applicant> >pickTeam(int budget, vector< vector<Applicant> >& alist)
{
   float optimalProfit = 0.0;
   vector<Applicant> chosen;

   
   for (int i = 0; i < alist.size(); i++)
	for (int j = 0; j < alist[i].size(); j++)
	    chosen.push_back(alist[i][j]);

   return make_pair(optimalProfit, chosen);
}


pair<int, vector<Applicant> >pickTeam_2(int budget, vector< vector<Applicant> >& alist)
{
   float optimalProfit = 0.0;
   vector<Applicant> chosen;

   
   for (int i = 0; i < alist.size(); i++)
	for (int j = 0; j < alist[i].size(); j++)
	    chosen.push_back(alist[i][j]);

   return make_pair(optimalProfit, chosen);
}
