#include <GameCreator.h>
#include <IRule.h>
#include <iostream>
#include <vector>

using namespace std;

//THIS IS A TESTING FUNCTION
int
main(int argc, char *argv[]) {
	float f = 3.14;
	dataVariant fl = f;
	dataVariant i = 10;
	dataVariant s = "hello";
	//dataVariant f = 3.235;
	dataVariant b = true;

	dataVariant ass = 5;

	//rva::visit(addVisitor(), ass, i);

	string out = rva::visit(toStringVisitor(), i);

	map<string, dataVariant> tm;
	tm["int"] = 4;
	tm["string"] = "plzwerk";

	vector<dataVariant> e;
	dataVariant em = e;

	vector<dataVariant> t;
	t.push_back(i);
	t.push_back(s);
	t.push_back(e);
	dataVariant innerV = t;

	vector<dataVariant> temp;
	temp.push_back(15);
	temp.push_back("bye");
	temp.push_back(innerV);
	temp.push_back(false);
	temp.push_back(e);

	dataVariant m = tm;
	temp.push_back(m);

	dataVariant v = temp;

	cout << out << " " << rva::visit(toStringVisitor(), b) << endl;
	cout << rva::visit(toStringVisitor(), m) << endl;
	cout << rva::visit(toStringVisitor(), v) << endl;

	rva::visit(shuffleVisitor(), v);

	cout << rva::visit(toStringVisitor(), v) << endl;

	rva::visit(reverseVisitor(), v);

	cout << rva::visit(toStringVisitor(), v) << endl;
	return 0;
}
