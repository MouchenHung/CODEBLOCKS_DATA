#include <iostream>
#include <unistd.h>
#include <thread>
#include <pthread.h>
using namespace std;

class MyClass
{
  public:
    MyClass(int i);
    //MyClsss(char i)=delete;  //刪除char版本的建構函式
};

class GAME_settings
{
private:
    int PG_X=31, PG_Y=10;
    int score;

public:
    int T_interval;
    int pos_x, pos_y;
    GAME_settings() = default;
    GAME_settings(int _pos_x, int _pos_y, int _score, int _T_interval);
    GAME_settings(float _pos_x, float _pos_y, float _score, float _T_interval) = delete;
    void GAME_dinamic();
    void GAME_ctl(string action);
    void GAME_print();
};

GAME_settings::GAME_settings(int _pos_x, int _pos_y, int _score, int _T_interval)
{
    pos_x = _pos_x;
    pos_y = _pos_y;
    score = _score;
    T_interval = _T_interval;
}

void GAME_settings::GAME_dinamic()
{
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


int main()
{
    MyClass m2('d');
    int ver0 = 5;
    char ver1 = 'a';
    char lst[3] = {'i','j','k'};
    string letter = "i am mouchen", letter1 = ", who are you?";
    cout << "Hello world! " << ver0 << endl << ver1 << endl << lst << " 2 ele = "<< lst[1] << endl;
    cout << letter << " ,size="<< letter.size() << " or " << letter.length() << endl;
    cout << letter+letter1 << endl;

    // reference
    int var3=5;
    const int &var4 = var3;
    cout << "var = " <<var4 << endl;
    cout << "change constant var4 by var3: ";
    cin >> var3;
    cout << "var = " << var4 << endl;

    cout << "[GAME TEST]" << endl;
    GAME_settings GAME_S(15,9,0,2.6);
    GAME_settings GAME_S_copy(GAME_S);
    GAME_settings GAME_S_emptyP();

    cout << "Check initial class sets:" << endl;
    GAME_S.GAME_dinamic();
    cout << "Check copy class sets:" << endl;
    GAME_S_copy.GAME_dinamic();
    cout << "Check non-init class sets:" << endl;
    //cout << GAME_S_emptyP.PG_X << endl;

    cout << "Game Start. . ." << endl << endl;



    char c;
    string ac;
    int cnt=0;
    while(1){
        cout << cnt << endl;
        system("stty raw");
        c = getchar();
        //system("stty cooked");
        //system("clear");
        std::cout << c << " was pressed."<< std::endl;

        if(c=='A'){
            cout << "Up" << endl;
            ac = "up";
        }
        else if(c=='D'){
            cout << "Left" << endl;
            ac = "left";
        }
        else if(c=='C'){
            cout << "Right" << endl;
            ac = "right";
        }
        else if(c=='B'){
            cout << "Down" << endl;
            ac = "down";
        }
        else if(c == '.') {
            system("stty cooked");
            exit(0);
        }

        GAME_S.GAME_ctl(ac);
        system("stty cooked");
        GAME_S.GAME_print();
        sleep(GAME_S.T_interval);
        cnt+=1;
    }


    /*
   // Set the terminal to raw mode
    while(1) {
        system("stty raw");
        c = getchar();
        // terminate when "." is pressed
        system("stty cooked");
        system("clear");
        std::cout << c << " was pressed."<< std::endl;

        if(c=='A'){
            cout << "left" << endl;
        }

        else if(c == '.') {
            system("stty cooked");
            exit(0);
        }
    }*/

    return 0;
}
