#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <deque>
#include <ctime>
#include <algorithm>

class Person
{
public:
    Person(string name,int score)
    {
        this->m_name = name;
        this->m_score = score;
    }
    string m_name;
    int m_score;
};

void person_init(vector<Person> &v)
{
    string name_num = "ABCDE";
    
    for (int i = 0; i < 5;i++)
    {
        string name = "Player";
        name += name_num[i];
        int score = 0;
        Person person(name, score);
        v.push_back(person);
    }
}

void get_score(vector<Person> &v)
{
    for (vector<Person>::iterator it = v.begin(); it != v.end();it++)
    {
        deque<int> d_score;
        int score = 0;
        for (int i = 0; i < 10; i++)
        {
            score = rand() % 41 + 60;
            d_score.push_back(score);
        }
        sort(d_score.begin(),d_score.end());
        d_score.pop_back();
        d_score.pop_front();
        int sum = 0;
        for (deque<int>::iterator dit = d_score.begin(); dit != d_score.end(); dit++)
        {
            sum += *dit;
        }
        int avg = sum / d_score.size();
        it->m_score = avg;

#if 0
        for (deque<int>::iterator it=d_score.begin(); it != d_score.end();it++)
        {
            cout << *it << " ";
        }
        cout << endl;
#endif
    }
}

void show_player(const vector<Person> &v)
{
    for (vector<Person>::const_iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "player name: " << it->m_name << "   " << "player score: " << it->m_score << endl;
    }
}

void syswork()
{
    vector<Person> v;
    person_init(v);
    get_score(v);
    show_player(v);
}

int main()
{
    syswork();
    return 0;
}