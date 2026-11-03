//
// Created by Ankit Rai on 03-11-2026.
//
#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include <vector>
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
vector<Task> tasks;
string getCurrentTime()
{
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    char buffer[20];
    strftime(buffer,sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    return string(buffer);
}
//A function to generate unique ids
int genNextId(const vector<Task>& tasks)
{
    int maxId = 0;
    for (const Task& task : tasks)
    {
        if (task.id > maxId)
        {
            maxId = task.id;
        }
    }
    return maxId+1;
}
//Write an addTask Function.
void addTask(vector<Task>& tasks, const string& description)
{
    string now = getCurrentTime();
    int id = genNextId(tasks);
    tasks.push_back(Task(id,description,"todo",now,now));
    cout<< "Task added Successfully(ID: " << id << ")" << endl;
}
//A function to print one task
void printTask(const Task& task)
{
    cout<<"[ "<<task.id<<" ] "<<task.description<<" ("<<task.status<<") "
    <<" created: "<<task.createdAt
        <<" updated: "<<task.updatedAt<<endl;
}
//A function to list tasks.
void listTasks(vector<Task>& tasks, const string& filter)
{
    bool found = false;
    for (const Task& task : tasks)
    {
        if (filter == "all"||task.status==filter)
        {
            printTask(task);
            found = true;
        }
    }
    if (!found)
    {
        cout<<"Tasks not found"<<endl;
    }
}
int main(int argc, char* argv[])
{
    vector<Task> tasks;
    string t0 = getCurrentTime();
    tasks.push_back(Task(1, "Buy groceries", "todo", t0, t0));
    tasks.push_back(Task(2, "Learn C++", "in-progress", t0, t0));
    tasks.push_back(Task(3, "Finish OOP notes", "done", t0, t0));
    if (argc < 2)
    {
        cout<<"Usage: task-cli <command> "<<endl;
        return 1;
    }
    string command = argv[1];
    if (command == "add")
    {
        if (argc!=3)
        {
            cout<<"Usage: task-cli add\"description\""<<endl;
            return 1;
        }
        addTask(tasks,argv[2]);
        for (const Task& task : tasks)
        {
            cout<<task.id<<" | "<<task.description<<" | "<<
                task.status<< " | " <<task.createdAt<<endl;
        }
    }else if (command == "list")
    {
        string filter = "all";
        if (argc == 3)
        {
            filter = argv[2];
            if (filter != "todo" && filter != "in-progress" && filter != "done")
            {
                cout << "Usage: task-cli list [todo|in-progress|done]" << endl;
                return 1;
            }
        }
        else if (argc > 3)
        {
            cout << "Usage: task-cli list [todo|in-progress|done]" << endl;
            return 1;
        }
        listTasks(tasks, filter);
    }
    else
    {
        cout << "Unknown Command" << endl;
        return 1;
    }
    return 0;
}