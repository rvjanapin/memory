#include <bits/stdc++.h>
using namespace std;

vector <char> cards;

void cardsInit();
void cardsOut(ofstream&);

int main(){
    cardsInit();
    ofstream file("out.txt");
    cardsOut(file);

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

void cardsOut(ofstream& file){
    file << '{' << '\n';   
    for(auto val : cards){
        file << '\t' <<  val << ',' << '\n';
    }
    file << '}';
}

