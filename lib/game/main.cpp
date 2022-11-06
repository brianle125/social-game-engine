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

	string out = std::visit(toStringVisitor(), i);

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


	cout << out << " " << std::visit(toStringVisitor(), b) << endl;
	cout << std::visit(toStringVisitor(), v) << endl;
	cout << std::visit(toStringVisitor(), m) << endl;

	return 0;
}