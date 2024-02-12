#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

using namespace std;

//fill function in a person message based on user input

void PromptForAddress(tutorial::Person* person){
    cout << "Enter person ID number:";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Enter name:";
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none):";
    string email;
    getline(cin, email);
    if (!email.empty()){
        person->set_email(email);
    }

    while(true) {
        cout << "Enter a phone number (or leave blank):";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        tutorial::Person::PhoneNumber *phone_number = person->add_phones();
        phone_number->set_number(number);

        cout << "Is it mobile/home/work phone?";
        string type;
        getline(cin, type);
        if (type == "mobile") {
            phone_number->set_type(tutorial::Person::PHONE_TYPE_MOBILE);
        } else if (type == "home") {
            phone_number->set_type(tutorial::Person::PHONE_TYPE_HOME);
        } else if (type == "work") {
            phone_number->set_type(tutorial::Person::PHONE_TYPE_WORK);
        } else {
            cout << "Unknown phone type.  Using default." << endl;
        }
    }
}

int main(int argc, char* argv[]){
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2){
        cerr << "Usage:    "<<argv[0] << "Address_book_file" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    {
        // read existing address book
        fstream input(argv[1], ios::in | ios::binary);
        if (!input) {
            cout << argv[1] << "file not found, creating new file" << endl;
        } else if (!address_book.ParseFromIstream(&input)){
            cerr << "Error parse the file" << endl;
            return -1;
        }
    }

    PromptForAddress(address_book.add_people());

    {
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if (!address_book.SerializeToOstream(&output)){
            cerr << "Error write address book" << endl;
            return -1;
        }
    }
    // Delete all global object in allocated by libprotobuf
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

