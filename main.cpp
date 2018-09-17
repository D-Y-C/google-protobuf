#include <iostream>
#include "damon.pb.h"

using namespace std;

int main()
{
    tutorial::Person person1;
    tutorial::Person person2;
    tutorial::Person person3;
    tutorial::AddressBook addressbook1;
    tutorial::AddressBook addressbook2;

    string buff;
    string addressBookStr;
    bool result;
    int i = 0;

    cout << "Protobuf Damon!" << endl;
//    memset(buff,0,sizeof(buff));

    person1.set_name("Bob");
    person1.set_id(1);
    person1.set_email("123456@email.com");

    tutorial::Person::PhoneNumber *phoneNumber =  person1.add_phones();
    phoneNumber->set_type(tutorial::Person_PhoneType_MOBILE);
    phoneNumber->set_number("10086");

    tutorial::Person::PhoneNumber *phoneNumber2 =  person1.add_phones();
    phoneNumber2->set_type(tutorial::Person_PhoneType_HOME);
    phoneNumber2->set_number("10011");

    person2.set_name("pony");
    person2.set_id(2);
    person2.set_email("22222@email.com");

    {
        tutorial::Person* p1 = addressbook1.add_people();
        p1->MergeFrom(person1);
        tutorial::Person* p2 = addressbook1.add_people();
        p2->MergeFrom(person2);
    }
     //    bool SerializeToString(string* output) const:
    //    序列化消息，将存储字节的以string方式输出。注意字节是二进制，而非文本；
//    result = person1.SerializePartialToArray(buff,sizeof(buff));
    result = person1.SerializePartialToString(&buff);
    if(!result)
    {
        std::cout << "serial to array faild" << std::endl;
        return -1;
    }

    result = addressbook1.SerializePartialToString(&addressBookStr);
    if(!result)
    {
        std::cout << "serial to array faild" << std::endl;
        return -1;
    }


//    bool ParseFromString(const string& data):
//      解析给定的string

     std::cout <<std::endl << "[-- Person test --]" <<std::endl;

    result = person3.ParseFromString(buff);
    if(!result)
    {
        std::cout << "Parse From Array faild!!! " << std::endl;
        return -1;
    }

    std::cout <<"[name]: "<< person3.name() << std::endl;
    std::cout <<"[id]: " << person3.id() << std::endl;
    std::cout <<"[email]: " << person3.email() << std::endl;

    for(i = 0 ; i < person3.phones().size(); i++)
    {
        const tutorial::Person::PhoneNumber& phone_number = person3.phones(i);
        std::cout << "[phone][" << i <<"]-" << phoneNumber->number() << std::endl;
    }

     std::cout << std::endl <<"[-- Address Book test --]" <<std::endl;

    result = addressbook2.ParseFromString(addressBookStr);
    if(!result)
    {
        std::cout << "Parse From Array faild!!! " << std::endl;
        return -1;
    }

    for(i = 0 ; i < addressbook2.people().size() ; i++)
    {
        const ::tutorial::Person& person = addressbook2.people(i);

        std::cout <<std::endl <<"[name]: "<< person.name() << std::endl;
        std::cout <<"[id]: " << person.id() << std::endl;
        std::cout <<"[email]: " << person.email() << std::endl;

        int j = 0;
        for( j = 0 ; j < person.phones().size(); j++)
        {
            const tutorial::Person::PhoneNumber& phone_number = person.phones(j);
            std::cout << "[phone][" << i <<"]-" << phoneNumber->type() <<":" << phone_number.number() << std::endl;
        }

    }

	google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
