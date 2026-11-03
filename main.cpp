//
// Created by Ankit Rai on 03-11-2026.
//
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
class  Task
{
    public:
    int id;
    string description;
    string status;
    string createdAt;
    string updatedAt;

    Task(int id, string description, string status, string createdAt, string updatedAt)
    {
        this->id = id;
        this->description = description;
        this->status = status;
        this->createdAt = createdAt;
        this->updatedAt = updatedAt;

    }
};
string getCurrentTime()
{
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    char buffer[20];
    strftime(buffer,sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    return string(buffer);
}
int main(int argc, char* argv[])
{
string now = getCurrentTime();
    Task t(1,"Buy Groceries", "todo", now,now);
    cout<<"Task "<<t.id<< ": "<<t.description<<" ["<<t.status<<"]"<<endl;
    cout<<"Created at "<<t.createdAt<<endl;
}