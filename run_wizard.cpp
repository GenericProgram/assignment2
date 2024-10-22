/*
 * Author: <Dean Leon>
 * Program description: <A small business program that iterates through dynamic arrays of structs & and appends data to and from files. Wizard themed.>
 */

#include "catalog.hpp"

using namespace std;

int main()
{
	// TODO Complete the main() function (remember to keep it small for
	// modularity)

	int input, wizardID, wizardIndex;
	string strInput;
	bool running = true;
	ifstream wizardFile;
	ifstream spellFile;
	int numOfWizards=0, numOfSpellBooks=0, loginAttempts=0;
/*
	cout << "Enter wizard databse file name (include file extention ie. .txt): " << endl;
	cin >> strInput;
	wizardFile.open(strInput);

	if(!wizardFile.is_open()){
        cerr << "Error: Could not open the file " << strInput << endl;
        return 1; // Return a non-zero value to indicate an error
    }

	cout << "Enter spells databse file name (include file extention ie. .txt): " << endl;
	cin >> strInput;
	spellFile.open(strInput);

	if(!spellFile.is_open()){
        cerr << "Error: Could not open the file " << strInput << endl;
        return 1; // Return a non-zero value to indicate an error
    }
*/
	wizardFile.open("wizards.txt");
	spellFile.open("spellbooks.txt");
    spellFile >> numOfSpellBooks;
    spellbook* spellBookArr = create_spellbooks(numOfSpellBooks);
    for(int i=0;i<numOfSpellBooks;i++){
        spellBookArr[i] = read_spellbook_data(spellFile);
    }

    wizardFile >> numOfWizards;
    wizard* wizardArr = create_wizards_database(numOfWizards);
    for(int i=0;i<numOfWizards;i++){
        wizardArr[i] = read_wizard_data(wizardFile);
    }

	while(running){
		cout << "Enter wizard ID: " << endl;
		cin >> wizardID;
		if(wizardID>999999999){
			cin.clear();
		}
		cout << "Enter wizard password: " << endl;
		cin >> strInput;
		for(int i=0;i<numOfWizards;i++){
			if(wizardArr[i].id == wizardID && wizardArr[i].password == strInput){
				running = false;
				wizardIndex=i;
				break;
			}
		}
		if(loginAttempts == 3){
			cout << "Maximum login attempts reached." << endl;
			delete_spellbooks(spellBookArr, numOfSpellBooks);
			delete_wizard_database(wizardArr);
			return 0;
		} 
		if(running == true) {
			loginAttempts++;
			cout << "Invalid ID or password, try again." << endl;
		}
	}
	running = true;
	displayWizard(wizardArr, wizardIndex);
	
	while(running) {
		cin.clear();
		printMenu();
		input = handleInput(1,4,input);
		if(input == 1){
			printAllSpells(wizardArr, spellBookArr, numOfSpellBooks, wizardIndex);
			break;
		} else if(input == 2){
			cout << "Enter name of spellbook (no whitespace, case-sensitive): " << endl;
			cin >> strInput;
			if(findSpellBook(spellBookArr, strInput, numOfSpellBooks) == -1){
				cout << "No spellbooks by that name found, remember that it is case-sensitive." << endl;
			} else {
				cout << "Do you want to (1) view inside terminal or (2) append to text file?" << endl;
				input = handleInput(1,2,input);
				if(input == 1) {
					printSpellBook(spellBookArr, findSpellBook(spellBookArr, strInput, numOfSpellBooks));
				} else if(input == 2){
					ofstream outfile;
					outfile.open("output.txt", ios::app);
					writeSpellBook(outfile, spellBookArr, findSpellBook(spellBookArr, strInput, numOfSpellBooks));
					cout << "Appened to \"output.txt\"" << endl;
				}
			}
		} else if(input == 3) {
			while(running) {
				cout << "Which spell effect do you want to see?" 
					<< " (fire, bubble, memory_loss, death, and poison)"
					<< "\npoision and death are only availible to Teacher+"
					<< "\nType your answer(case-sensitive): " << endl;
				cin >> strInput;
				if((strInput == "poison" || strInput == "death") && wizardArr[wizardIndex].position_title == "Student"){
					cout << "Invalid type or restricted access. Try again." << endl;
				} else if(isValidEffect(strInput)){
					cout << "Do you want to (1) view inside terminal or (2) append to text file?" << endl;
					input = handleInput(1,2,input);
					if(input == 1){
						printSpellByType(strInput, spellBookArr, numOfSpellBooks);
					} else if(input == 2) {
						ofstream outfile;
						outfile.open("effects.txt", ios::app);
						writeSpellsByType(strInput, spellBookArr, numOfSpellBooks, outfile);
						cout << "Appened to \"effects.txt\"" << endl;
					}
					break;
				} else {
					cout << "Unrecognized spell type, try again." << endl;
				}
			}
		} else if(input == 4){
			break;
		}
	}

	delete_spellbooks(spellBookArr, numOfSpellBooks);
	delete_wizard_database(wizardArr);

	return 0;
}
