// #include<iostream>
// #include<vector>
// #include<string>


// class Student{
// private:
//  std::string name;
//  int age;


// public:
// Student(std::string n,int a):name(n),age(a){};

// void display(){
//     std::cout<<name<<"  "<<age<<std::endl;
// }

// };


// class School{

//     private:
//     std::vector<Student> Students;

//     public:
//     void addstudents(std::string name,int age){
//         Students.push_back(Student(name,age) );
//     }

//     void displyStudents()
//     {
//         for(Student& s: Students){
//             s.display();
//         }
//     }


// };

// int main(){
//     School school;
//     school.addstudents("kuldeep",25);
//     school.addstudents("sumit",26);
//     school.addstudents("AKshay",28);

//     school.displyStudents();
// }
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<condition_variable>

std::vector<int> v;
std::mutex mtx;
std::condition_variable cv;

bool oddTurn=true;

void oddNum(){
    for(int i=1;i<=99;i+=2){
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock,[]{ return oddTurn;});
        v.emplace_back(i);
        oddTurn=false;

        cv.notify_one();

    }

};

void evenNum(){
      for(int i=2;i<=100;i+=2){
         std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock,[]{ return !oddTurn;});
        v.emplace_back(i);
        oddTurn=true;

        cv.notify_one();
      }

};




int main(){
    std::thread t1(oddNum);
    std::thread t2(evenNum);

    t1.join();
    t2.join();

    for(auto i : v){
        std::cout<<i<<" ";
    }


    return 0;
}