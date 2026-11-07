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
    cout << "Task added successfully (ID: " << id << ")" << endl;
}
//A function to print one task
void printTask(const Task& task)
{
    cout<<"[ "<<task.id<<" ] "<<task.description<<" ("<<task.status<<") "
    <<" created: "<<task.createdAt
        <<" updated: "<<task.updatedAt<<endl;
}
//A function to list tasks.
void listTasks(const vector<Task>& tasks, const string& filter)
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
//Find a task by id.
int findTaskIndex(const vector<Task>& tasks, int id)
{
    for (int i=0; i<tasks.size(); i++)
    {
        if (tasks[i].id == id)
        {
            return i;
        }
    }
    return -1;
}
//Update Task
void updateTask(vector<Task>& tasks, int id, const string& newDescription)
{
    int index = findTaskIndex(tasks, id);
    if (index == -1)
    {
        cout<<"Error: Task with ID "<<id<<" not found"<<endl;
        return;
    }
    tasks[index].description = newDescription;
    tasks[index].updatedAt = getCurrentTime();
    cout<<"Task updated Successfully "<<id<<endl;
}
//Delete Task
void deleteTask(vector<Task>& tasks, int id)
{
    int index = findTaskIndex(tasks, id);
    if (index == -1)
    {
        cout<<"Error: Task with ID "<<id<<" not found"<<endl;
        return;
    }
    tasks.erase(tasks.begin()+index);
    cout<<"Task deleted Successfully"<<endl;
}
//mark-in-progress and mark-done
void markTask(vector<Task>& tasks, int id,const string& newStatus)
{
    int index = findTaskIndex(tasks, id);
    if (index == -1)
    {
        cout<<"Error: Task with ID "<<id<<" not found"<<endl;
        return;
    }
    tasks[index].status= newStatus;
    tasks[index].updatedAt = getCurrentTime();
    cout << "Task " << id << " marked as " << newStatus << endl;


}
//Convert text to a number
bool parseId(const string& text, int& id)
{
    try
    {
        size_t pos;
        id = stoi(text, &pos);
        return pos == text.size();

    }catch (...)
    {
        return false;
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
            cout << "Usage: task-cli add \"description\"" << endl;
            return 1;
        }
        addTask(tasks,argv[2]);
        for (const Task& task : tasks)
        {
            cout<<task.id<<" | "<<task.description<<" | "<<
                task.status<< " | " <<task.createdAt<<endl;
        }
    }else if (command == "update")
    {
        int id;
        if (argc!=4||!parseId(argv[2],id))
        {
            cout<<"Usage: task-cli update [id]\"new Description\""<<endl;
            return 1;
        }
        updateTask(tasks,id,argv[3]);
    }else if (command == "delete")
    {
     int id;
        if (argc!=3||!parseId(argv[2],id))
        {
            cout<<"Usage: task-cli delete [id]"<<endl;
            return 1;
        }
        deleteTask(tasks,id);
    }else if (command == "mark-in-progress"||command == "mark-done"){
      int id;
        if (argc!=3||!parseId(argv[2],id))
        {
            cout << "Usage: task-cli " << command << " [id]" << endl;
            return 1;
        }
        string newStatus = (command == "mark-done") ? "done" : "in-progress";
        markTask(tasks, id, newStatus);
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