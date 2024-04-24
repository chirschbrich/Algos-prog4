#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// this is a structure to store the information for each applicant
struct Applicant {

public:
   int   id;              // use to "identify" each applicant. No effort is made to ensure this is unique
   int   cost;            // cost for applicant
   int   benefit;	  // benefit for applicant
};

