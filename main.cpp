#include <bits/stdc++.h>
using namespace std;
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define RESET   "\033[0m" 
vector <char> cards;
int turns = 0;

void cardsInit();
void play();
void faceUp(int);
void cardsOut(ofstream& file);

int main(){
    cardsInit();
    ofstream file("out.txt");
    cardsOut(file);
    play();
}

void cardsInit(){
    srand(time(NULL));  
    random_device rd {};
    auto rng = default_random_engine {rd()};

    for(int i = 65; i <= 89 ; i++){
        cards.push_back(char(i));
        cards.push_back(char(i));
    }
    
    shuffle(cards.begin(), cards.end(), rng);
}

void cardsOut(ofstream& file){
    int i = 1; 
    for(char val : cards){
        file << i << " - " << val << endl;
        i++;
    }
}

void faceUp(int x){
    turns += 1;
    cout << turns << " - Card " << x+1 << " contains " << cards[x] << endl;
}

void play(){
    int candy = 0;
    map<char, int> positions;
    while(candy < 25){

        //first iteration to memorize all the positions
        for(int i = 0 ; i < cards.size(); i += 2){
            faceUp(i); faceUp(i+1); 
            if(cards[i] == cards[i+1]){ //if there's a pair of consecutive letters
                candy += 1;

                cout << "-----------------------------------------------" << endl;
                cout << GREEN << "Jack gets candy #" << candy << RESET << endl;
                cout << "-----------------------------------------------" << endl;

                replace(cards.begin(), cards.end(), cards[i], '-');
                replace(cards.begin(), cards.end(), cards[i+1], '-');
                positions.insert(pair<char, int> (cards[i], i));
                positions.insert(pair<char,int> (cards[i+1] , i+1));
            }

            else if(cards[i] != cards[i+1]){
                positions.insert(pair<char, int> (cards[i], i));
                positions.insert(pair<char,int> (cards[i+1] , i+1));

                cout << RED << "The letters are not equal" << RESET << endl;
                cout << "-----------------------------------------------" << endl;
                cout << "The grader automatically turns cards " << i+1 << " and " << i+2 << endl;
                cout << "-----------------------------------------------" << endl;
            }
            if(candy == 25)
                break;
        }

        //second iteration to match it up
        for(int i = 0 ; i < cards.size(); i++){
            if(positions[cards[i]] != i and cards[i] != '-'){
                faceUp(positions[cards[i]]);
                faceUp(i); 
                candy += 1;
                cout << "-----------------------------------------------" << endl;
                cout << GREEN << "Jack gets candy #" << candy << RESET << endl;
                cout << "-----------------------------------------------" << endl;
            }

            if(candy == 25){
                break;
            }
        }
    }
}
