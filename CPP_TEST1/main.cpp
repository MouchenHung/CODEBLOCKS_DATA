#include <iostream>
#include <unistd.h>
#include <thread>
#include <pthread.h>

#include <signal.h>
#include <csignal>

using namespace std;

class MyClass1
{
private:
    int pri_arg1;
public:
    MyClass1(int arg1, char arg2);
    MyClass1(char arg1, int arg2)=delete;  //刪除char版本的建構函式
    int pub_arg1;
    void F1();
};

void MyClass1::F1(){
    cout << "Public arg: " << pub_arg1 << endl;
    cout << "Private arg: " << pri_arg1 << endl;
}

MyClass1::MyClass1(int ele1, char ele2){
    pri_arg1 = ele1;
    pub_arg1 = ele2;
}

class MyClass2
{
private:
    int pri_arg1;
    float pri_arg2;
    string pri_arg3;
public:
    MyClass2()=default;
    MyClass2(int A=10, float B=20.5, string C="Hello MyClass2")
    {
        pri_arg1 = A;
        pri_arg2 = B;
        pri_arg3 = C;
    }

    void print(){
        cout << "Return [pri_arg1] " << pri_arg1 << endl;
        cout << "Return [pri_arg2] " << pri_arg2 << endl;
        cout << "Return [pri_arg3] " << pri_arg3 << endl;
    }

    float CAL_plus();
    void CAL_comp(float p1);
};

float MyClass2::CAL_plus(){
    return (float)pri_arg1+pri_arg2;
}

void MyClass2::CAL_comp(float p1){
    if (this->CAL_plus() >= p1){
        cout << "--> default value >= given value("<< this->CAL_plus() << " >= " << p1 << ")" << endl;
    }
    else{
        cout << "--> default value < given value("<< this->CAL_plus() << " < " << p1 << ")" << endl;
    }
}




class GAME_settings
{
private:
    int PG_X=31, PG_Y=10;
    int score;

public:
    int T_interval;
    int pos_x, pos_y;
    //GAME_settings() = default;
    GAME_settings(int _pos_x, int _pos_y, int _score, int _T_interval);
    GAME_settings(float _pos_x, float _pos_y, float _score, float _T_interval) = delete;
    void GAME_dinamic();
    void GAME_ctl(string action);
    void GAME_print();
};

GAME_settings::GAME_settings(int _pos_x, int _pos_y, int _score, int _T_interval){
    pos_x = _pos_x;
    pos_y = _pos_y;
    score = _score;
    T_interval = _T_interval;
}

void GAME_settings::GAME_dinamic(){
    cout << "play ground size: (" << PG_X << "," <<  PG_Y << ")" << endl;
    cout << "now at (" << pos_x << "," <<  pos_y << ")" << endl;
    cout << "time interval: " << T_interval << endl;
    cout << "score: " << score << endl;
}

void GAME_settings::GAME_ctl(string action){
    if(action == "up"){
        if(pos_y-1 >= 1){
            pos_y-=1;
        }
    }
    else if(action == "down"){
        if(pos_y+1 < 9){
            pos_y+=1;
        }
    }
    else if(action == "left"){
        if(pos_x+1 > 1){
            pos_x-=1;
        }
    }
    else if(action == "right"){
        if(pos_x+1 < 30){
            pos_x+=1;
        }
    }
}

void GAME_settings::GAME_print(){
    for(int i=0; i<PG_Y; i++){
        for(int j=0; j<PG_X; j++){
            if(i==(pos_y) && j==(pos_x)){
                cout << "@";
            }
            else{
                cout << "-";
            }
        }
        cout << endl;
    }
    cout << "score: " << score << endl;
}

void EVENT_EndProcess(int signum){
    cout << "Process end . . ." << signum << endl;
    exit(signum);
}

void EVENT_Tick_5s(int signum){
    cout << "ticking every 5 sec..." << signum << endl;
}

void SIGNAL_HANDLER(int signum){
    /* ctrl + c */
    if (signum == 2){
        cout << "SIG[" << signum << "] Loop break . . ." << endl;
        exit(signum);
    }
    /* ctrl + 4 */
    else if (signum == 3){
        cout << "SIG[" << signum << "] Process end . . ." << endl;
    }
    else if (signum == 15){
        cout << "SIG[" << signum << "] Ticking every 5 sec . . ." << endl;
    }
    else if (signum == 10){
        cout << "SIG[" << signum << "] Ticking every 10 sec . . ." << endl;
    }
    else if (signum == 12){
        cout << "SIG[" << signum << "] Ticking every 15 sec . . ." << endl;
    }
    else{
        cout << "SIG[" << signum << "] others" << endl;
    }
}

void *PROCESS_CHILD_1(void *threadid){
    cout << "CHILD PROCESS 1: Count down" << endl;

    int T_cnt = 0;
    while(T_cnt < 40){
        if (T_cnt % 5 == 0){
            raise(SIGTERM);
        }
        if (T_cnt % 10 == 0){
            raise(SIGUSR1);
        }
        if (T_cnt % 15 == 0){
            raise(SIGUSR2);
        }
        sleep(1);
        T_cnt++;
    }
}

void *PROCESS_CHILD_2(void *threadid){
    cout << "CHILD PROCESS 1: TASK 1" << endl;

    int T_cnt = 0;
    while(T_cnt < 30){
        cout << "child2 triggered . . ." << endl;
        sleep(2);
        T_cnt++;
    }
}

int main()
{
    pthread_t PT1, PT2;
    pthread_create(&PT1, NULL, PROCESS_CHILD_1, (void *)0);
    pthread_create(&PT2, NULL, PROCESS_CHILD_2, (void *)0);

    signal(SIGINT, SIGNAL_HANDLER);
    signal(SIGTERM, SIGNAL_HANDLER);
    signal(SIGQUIT, SIGNAL_HANDLER);
    signal(SIGUSR1, SIGNAL_HANDLER);
    signal(SIGUSR2, SIGNAL_HANDLER);

    /*
    cout << "[CLASS TEST]" << endl;
    cout << "TEST1. . ." << endl << endl;
    GAME_settings GAME_S(15,9,0,2.6);
    GAME_settings GAME_S_copy(GAME_S);
    GAME_settings GAME_S_emptyP();

    cout << "Check initial class sets:" << endl;
    GAME_S.GAME_dinamic();
    cout << endl << "Check copy class sets:" << endl;
    GAME_S_copy.GAME_dinamic();
    cout << "Check non-init class sets:" << endl;
    //cout << GAME_S_emptyP.PG_X << endl;

    cout << "TEST2. . ." << endl << endl;
    // This function parameters sets has been deleted!
    //MyClass1 m1('s', 5);
    MyClass1 m1(5, 'a');
    m1.F1();

    MyClass2 m2(5, 2.12, "aaa");
    m2.print();
    m2.CAL_comp(5);
    */
    pthread_join(PT1, NULL);
    pthread_join(PT2, NULL);

    return 0;
}
