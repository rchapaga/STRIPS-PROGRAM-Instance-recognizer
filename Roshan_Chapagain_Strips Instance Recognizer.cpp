#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int white_space(char s);
vector<string> tokenize(string s);
string munch(string s, int i);
bool atomic_statement(vector<string> s);
vector<string> group_vector(vector<string> s, int a, int b);
bool literal(vector<string> s);
bool initial_state_decleration(vector<string> s);
bool NEatom_list(vector<string> s);
bool initial_state_declaration(vector<string> s);
bool atom_list(vector<string> s);
bool NEsymbol_list(vector<string> s);
bool symbol_list(vector<string> s);
bool symbols(string s);
bool goal_declaration(vector<string> s);
bool NEliteral_list(vector<string> s);
bool action_prototype(vector<string> s);
bool precondition_declaration(vector<string> s);
bool STRIPS_program(vector<string> s);
bool action_set(vector<string> s);
bool action_declaration(vector<string> s);
bool effects_declaration(vector<string> s);
bool precondition_declaration(vector<string> s);
bool action_prototype(vector<string> s);
void print_ans(bool a);
bool NEaction_declaration_list(vector<string> s);

vector<string> test(string s){
	vector<string> toks = tokenize(s);
	for (int i = 0; i < toks.size(); i++)
	{
		cout << toks[i] << " ";
	}
	cout << endl;
	return toks;
}

int main(){
	/*printf("%d",STRIPS_program(tokenize("Initial state:  At(A) Level(low), BoxAt(C), BananasAt(B)\nGoal: Have(Bananas)\n Actions:\n// move from X to Y\n_Move(X, Y)_\r\nPreconditions:At(X), Level(low) \nEffects: not At(X), At(Y)\n// climb up on the box\n_ClimbUp(Location)_\nPreconditions:  At(Location), BoxAt(Location), Level(low)\nEffects: Level(high), not Level(low)\n// climb down from the box\n_ClimbDown(Location)_\nPreconditions:  At(Location), BoxAt(Location), Level(high)\nEffects: Level(low), not Level(high)\n// move monkey and box from X to Y\n_MoveBox(X, Y)_\nPreconditions:  At(X), BoxAt(X), Level(low)\nEffects: BoxAt(Y), not BoxAt(X), At(Y), not At(X)\n// take the bananas\n_TakeBananas(Location)_\nPreconditions:  At(Location), BananasAt(Location), Level(high)\nEffects: Have(Bananas)")));

	printf("%d", NEaction_declaration_list(tokenize("_hi(m,bh)_ Preconditions : not hi(mn,nbh,mnn),i(),not i(),he(ksdj,ksj) Effects : he(j,k,l), not this (m,wjksj,kuj) _hi(m,bh)_ Preconditions : not hi(mn,nbh,mnn),i(),not i(),he(ksdj,ksj) Effects : he(j,k,l), not this (m,wjksj,kuj) _hi(m,bh)_ Preconditions : not hi(mn,nbh,mnn),i(),not i(),he(ksdj,ksj) Effects : he(j,k,l), not this (m,wjksj,kuj)")));
	*/
	return 0;
}


bool symbols(string s){
	for (int i = 0; i < s.size(); i++){
		if (!(((int)s[i] >= 97 && (int)s[i] <= 122) || ((int)s[i] >= 65 && (int)s[i] <= 90))){
			return false;
		}
	}
	return true;
}
vector<string> tokenize(string s){
	vector <string> token;
	int i = 0;
	while (i < s.size()){
		if (white_space(s[i])){
			i = i + 1;
		}
		else if (i < s.size() && s[i] == '/' && s[i + 1] == '/'){
			i = i + 2;
			while (!(s[i] == '\n' || s[i] == '\r' || (s[i] == '\n' && s[i + 1] == '\r'))){
				i = i + 1;
			}
		}
		else{
			string toks = munch(s, i);
			i = i + toks.size();
			token.push_back(toks);
		}
	}
	return token;
}

string munch(string s, int i){
	string toks2;
	if ((int)s[i] == 40 || (int)s[i] == 41 || (int)s[i] == 95 || (int)s[i] == 44 || (int)s[i] == 58){
		toks2 = toks2 + s[i];
	}
	if (((int)s[i] >= 97 && (int)s[i] <= 122) || ((int)s[i] >= 65 && (int)s[i] <= 90)){
		while (((int)s[i] >= 97 && (int)s[i] <= 122) || ((int)s[i] >= 65 && (int)s[i] <= 90)){
			toks2 = toks2 + (char)s[i];
			i = i + 1;
		}
	}

	return toks2;
}

int white_space(char s){
	if ((int)s == 9 || (int)s == 10 || (int)s == 11 || (int)s == 12 || (int)s == 13 || (int)s == 32){
		return true;
	}
	else{
		return false;
	}
}

bool atomic_statement(vector<string> s){
	if (s.size() < 3){
		return false;
	}
	else if (symbols(s[0]) && s[1] == "(" && s[s.size() - 1] == ")" && s.size() == 3){
		return true;
	}
	else if (s.size() > 3 && symbols(s[0]) && s[1] == "(" && s[s.size() - 1] == ")"){
		return (NEsymbol_list(group_vector(s, 2, s.size() - 1)));


	}
	else{
		return false;
	}
}


bool NEsymbol_list(vector<string> s){
	if (symbols(s[0]) && s.size() == 1){
		return true;
	}

	else if (symbols(s[0]) && s[1] == ","){

		return (NEsymbol_list(group_vector(s, 2, s.size())));
	}
	else{


		return false;

	}
}

bool literal(vector<string> s){
	if (s.size() <3){
		return false;
	}
	else if ((atomic_statement(s)) || (s[0] == "not" && atomic_statement(group_vector(s, 1, s.size())))){
		return true;
	}
	else{
		return false;
	}
}


vector<string> group_vector(vector<string> s, int a, int b){

	vector<string> toks;
	for (int i = a; i < b; i++){
		toks.push_back(s[i]);
	}
	for (int i = 0; i < toks.size(); i++)
	{
		cout << toks[i] << " ";
	}
	cout << endl;
	printf("\n");


	return toks;
}

bool initial_state_declaration(vector<string> s){
	if (s.size() < 3){
		return false;
	}
	else if (s[0] == "Initial" && s[1] == "state" && s[2] == ":" && s.size() == 3){
		return true;
	}
	else if ((s[0] == "Initial" && s[1] == "state" && s[2] == ":") && (NEatom_list(group_vector(s, 3, s.size())))){
		return true;
	}
	else{
		return false;
	}
}


bool NEatom_list(vector<string> s){
	if (s.size() < 3){
		return false;
	}
	if (atomic_statement(s)){
		return true;
	}
	for (int i = 0; i < s.size(); i++){

		if (s[i] == "," && (atomic_statement(group_vector(s, 0, i)))){
			return(NEatom_list(group_vector(s, i + 1, s.size())));
		}
	}
	return false;
}


bool NEliteral_list(vector<string> s){
	if (s.size() < 3){
		return false;
	}
	if (literal(s)){
		return true;
	}
	for (int i = 0; i < s.size(); i++){
		if (s[i] == "," && literal(group_vector(s, 0, i))){
			return (NEliteral_list(group_vector(s, i + 1, s.size())));
		}
	}
	return false;
}


bool goal_declaration(vector<string> s){
	if (s.size() < 2){
		return false;
	}
	if (s[0] == "Goal" && s[1] == ":" && s.size() == 2){
		return true;
	}
	else if (s[0] == "Goal" && s[1] == ":" && s.size() >2){
		return(NEliteral_list(group_vector(s, 2, s.size())));
	}
	else{
		return false;
	}
}


bool action_prototype(vector<string> s){
	if (s.size() < 3){
		return false;
	}

	else if (s[0] == "_" && s[s.size() - 1] == "_"){
		return (atomic_statement(group_vector(s, 1, s.size() - 1)));

	}
	else{
		return false;
	}
}


bool precondition_declaration(vector<string> s){
	if (s.size() <2){
		return false;
	}
	if (s[0] == "Preconditions" && s[1] == ":" && s.size() == 2){

		return true;
	}
	else if (s[0] == "Preconditions" && s[1] == ":" && s.size() > 2){
		return(NEliteral_list(group_vector(s, 2, s.size())));
	}
	else{
		return false;
	}
}

bool effects_declaration(vector<string> s){
	if (s.size() <2){
		return false;
	}
	else if (s[0] == "Effects" && s[1] == ":" && s.size() == 2){


		return true;
	}
	else if (s[0] == "Effects" && s[1] == ":" && s.size() > 2){
		return(NEliteral_list(group_vector(s, 2, s.size())));
	}
	else{
		return false;
	}
}


bool action_declaration(vector<string> s){
	if (s.size() < 9){
		return false;
	}
	for (int i = 1; i <s.size(); i++){
		if (action_prototype(group_vector(s, 0, i))){

			for (int j = i + 1; j<s.size(); j++){
				if (precondition_declaration(group_vector(s, i, j)) && effects_declaration(group_vector(s, j, s.size()))){
					return true;
				}

			}

		}
	}
	return false;

}

bool NEaction_declaration_list(vector<string> s){

	if (s.size() < 9){
		return false;
	}
	if (action_declaration(s)){

		return true;
	}
	for (int i = 1; i < s.size(); i++){
		if (action_declaration(group_vector(s, 0, i)) && s[i] == "_"){

			return NEaction_declaration_list(group_vector(s, i, s.size()));
		}
	}
	return false;
}

bool action_set(vector<string> s){
	if (s.size() < 11){
		return false;
	}
	else if (s[0] == "Actions" && s[1] == ":" && s.size() > 2){
		return(NEaction_declaration_list(group_vector(s, 2, s.size())));
	}
	else{
		return false;
	}

}

void print_ans(bool a){
	if (a == true){
		printf("true");
	}
	if (a == false){
		printf("false");
	}
}

bool STRIPS_program(vector<string> token){
	printf("Answer Key :\n1 = TRUE AND 0 = FALSE\n\n");

	if (token.size() <16){
		return false;
	}
	for (int i = 1; i <token.size(); i++){
		if (initial_state_declaration(group_vector(token, 0, i))){
			for (int j = i + 1; j<token.size(); j++){
				if (goal_declaration(group_vector(token, i, j)) && action_set(group_vector(token, j, token.size()))){
					return true;
				}
			}
		}
	}
	return false;
}