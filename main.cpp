#include <bits/stdc++.h>
using namespace std;

vector <char> cards;
int turns = 0;

void cardsInit();
void cardsOut(ofstream&);
void play();
void moveOut(int);

int main(){
    cardsInit();
    ofstream file("out.txt");
    cardsOut(file);

    play();
}


void cardsInit(){
    srand(time(NULL));  
    //genreating chars
    random_device rd;
    auto rng = default_random_engine {rd()};
    for(int i = 65; i <= 89 ; i++){
        cards.push_back(char(i));
        cards.push_back(char(i));
    }
    shuffle(cards.begin(), cards.end(), rng);
}

void moveOut(int x){
    turns += 1;
    cout << turns << " - Card " << x+1 << " contains " << cards[x] << endl;
}

void cardsOut(ofstream& file){
    file << '{' << '\n';   
    for(auto val : cards){
        file << '\t' <<  val << ',' << '\n';
    }
    file << '}';
}

void play(){
    //checking the first and last pair
    int candy = 0;
    map<char, int> positions;
    while(candy < 25){
        for(int i = 0 ; i < cards.size(); i += 2){
            moveOut(i);
            moveOut(i+1);
            if(cards[i] == cards[i+1]){
                candy++;
                cout << "Jack gets candy #" << candy << endl;
                remove(cards.begin(),cards.end(), cards[i]);
            }
            else if(cards[i] != cards[i+1]){
                positions.insert(pair<char, int> (cards[i], i));
                positions.insert(pair<char,int> (cards[i+1] , i+1));
                cout << "The letters are not equal" << endl;
            }

            if(turns % 2 == 0){
                cout << "The grader automatically turns cards " << i << " and " << i+1 << endl;
            }
            if(candy == 25)
                break;
        }

        //second loop
        for(int i = 0 ; i < cards.size(); i++){
            if(positions[cards[i]] != i){
                moveOut(i);
                moveOut(positions[cards[i]]);
                candy++;
                cout << "Jack gets candy #" << candy << endl;
            }
            if(candy == 25){
                break;
            }
        }
    }

}
