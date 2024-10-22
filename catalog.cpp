#include "catalog.hpp"

using namespace std;

spell* create_spells(int size){
    // Allocate memory for the array of spells
    spell* spells_array = new spell[size];

    // No need to check for nullptr since 'new' will throw std::bad_alloc on failure

    return spells_array;

}

spell read_spell_data(ifstream& file){
    spell s;
    file >> s.name >> s.success_rate >> s.effect;
    return s;
}

spellbook* create_spellbooks(int size){
    // Allocate memory for the array of spellbooks
    spellbook* spellbooks_array = new spellbook[size];

    // Return the pointer to the dynamically allocated array
    return spellbooks_array;
}

spellbook read_spellbook_data(ifstream& file){
    spellbook s;
    float avgSuccessRate=0.0f;
    file >> s.title >> s.author >> s.num_pages >> s.edition >> s.num_spells;
    s.spells = create_spells(s.num_spells);
    for(int i=0;i<s.num_spells;i++){
        s.spells[i] = read_spell_data(file);
        avgSuccessRate += s.spells[i].success_rate;
    }
    s.avg_success_rate = avgSuccessRate / s.num_spells;
    return s;
}

void delete_spells(spell*& spells) {
    delete[] spells; // Delete the dynamic array of spells
    spells = nullptr; // Set the pointer to nullptr
}

void delete_spellbooks(spellbook*& spellbooks, int size){
    for(int i=0;i<size;i++){
        delete_spells(spellbooks[i].spells);
    }
    delete[] spellbooks;
}

// TODO Function definitions go here
/**
 * @brief Used to limit user inputs from the standard input, only accepts integers and 
 * fails when an invalid type is entered. Inclusive for the minimum and maximum.
 * Loops until a valid input is given
 * 
 * @param MIN Minimum value accepted, inclusive.
 * @param MAX Maximum value accepted, inclusive.
 * @param choice The number to be computed.
 * @return int between MAX and MIN, inclusive.
 */
int handleInput(int MIN, int MAX, int choice){
    bool looping = true; //create a boolean to loop indefinitly unitl we set it to false
    while(looping) {
        cin >> choice;//get user input
        if(choice > MAX || choice < MIN){ //compute to see if its in bounds
            cin.clear(); //clear invalid input, required when accounting for huge numbers
            // prompt for another input (and remind of accepted values) 
            cout << "Input out of range, enter again." << " (" << MIN << "-" << MAX << ")" << endl; 
        } else { //if input is good
            looping = false;//escape loop
            return choice;//return vetted int
        }
    }
    return 0;//this is here so my program doesn't throw a warning
}

void displayWizard(wizard* w, int index){
    cout << "Welcome: " << w[index].name << endl;
    cout << "ID: " << w[index].id << endl;
    cout << "Position: " << w[index].position_title << endl;
    cout << "Beard length: " << w[index].beard_length << endl;
}

wizard read_wizard_data(std::ifstream& file) {
    wizard w;
    file >> w.name >> w.id >> w.password >> w.position_title >> w.beard_length;
    return w;
}

wizard* create_wizards_database(int size){
    wizard* wizard_database = new wizard[size];
    return wizard_database;
}

void delete_wizard_database(wizard*& wizard){
    delete[] wizard;
    wizard = nullptr;
}

void printMenu(){
    cout << "Choose from menu (enter corresponding integer): " << endl;
    cout << "1. Display all" << endl;
    cout << "2. Search spellbook by name" << endl;
    cout << "3. Search spells by effect" << endl;
    cout << "4. Exit" << endl;
}        

void printAllSpells(wizard* wizard, spellbook* sb, int numOfSpellBooks, int wizardIndex){
    for(int i=0;i<numOfSpellBooks;i++){
        cout << "\nSpellbook name: " << sb[i].title << "\tAuthor: " << sb[i].author << endl;
        cout << "Edition: " << sb[i].edition << "\tPages: " << sb[i].num_pages << endl;
        cout << "Average spell success rate: " << sb[i].avg_success_rate 
            << "\t Number of spells in book: " << sb[i].num_spells << endl;
        for(int j=0;j<sb[i].num_spells;j++){
            if((sb[i].spells[j].effect == "poison" || sb[i].spells[j].effect == "death") && wizard[wizardIndex].position_title == "Student"){
                continue;
            } else {
                cout << "Spell name: " << sb[i].spells[j].name 
                    << "\tSuccess rate: " << sb[i].spells[j].success_rate 
                    << "\tSpell effect: " << sb[i].spells[j].effect << endl;
            }
        }
    }
}

int findSpellBook(spellbook* sb, string name, int numOfSpellBooks){
    for(int i=0;i<numOfSpellBooks;i++){
        if(sb[i].title == name){
            return i;
        }
    }
    return -1;
}

void printSpellBook(spellbook* sb, int index){
    cout << "\nSpellbook name: " << sb[index].title << "\tAuthor: " << sb[index].author << endl;
        cout << "Edition: " << sb[index].edition << "\tPages: " << sb[index].num_pages << endl;
        cout << "Average spell success rate: " << sb[index].avg_success_rate 
        << "\t Number of spells in book: " << sb[index].num_spells << endl;
    for(int i=0;i<sb[index].num_spells;i++){
        cout << "Spell name: " << sb[index].spells[i].name 
            << "\tSuccess rate: " << sb[index].spells[i].success_rate 
            << "\tSpell effect: " << sb[index].spells[i].effect << endl;
    }
}

void writeSpellBook(ofstream& file, spellbook* sb, int index) {
    file << sb[index].title << " " << sb[index].author << " " << sb[index].num_pages
        << " " << sb[index].edition << " " << sb[index].num_spells << "\n";
    for(int i=0;i<sb[i].num_spells;i++){
        file << sb[index].spells[i].name << " " 
            << sb[index].spells[i].success_rate << " " 
            << sb[index].spells[i].effect << "\n";
    }
}

void printSpellByType(std::string type, spellbook* sb, int numOfSpellbooks){
    for(int i=0;i<numOfSpellbooks;i++){
        for(int j=0;j<sb[i].num_spells;j++){
            if(sb[i].spells[j].effect == type){
                cout << "Spell name: " << sb[i].spells[j].name 
                    << "\tSuccess rate: " << sb[i].spells[j].success_rate 
                    << "\tSpell effect: " << sb[i].spells[j].effect << endl;
            }
        }
    }
}

void writeSpellsByType(std::string type, spellbook* sb, int numOfSpellbooks, ofstream& file){
    for(int i=0;i<numOfSpellbooks;i++){
        for(int j=0;j<sb[i].num_spells;j++){
            if(sb[i].spells[j].effect == type){
                file << "Spell name: " << sb[i].spells[j].name 
                    << "\tSuccess rate: " << sb[i].spells[j].success_rate 
                    << "\tSpell effect: " << sb[i].spells[j].effect << endl;
            }
        }
    }
}

bool isValidEffect(std::string string){
    if(string == "poison") {
        return true;		
	} else if(string == "death") {
		return true;				
	} else if(string == "memory_loss") {
		return true;			
	} else if(string == "fire") {
		return true;			
	} else if(string == "bubble") {
	    return true;			
	} else {
        return false;
    }
}
