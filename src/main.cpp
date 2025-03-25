#include "util.h"
#include "service.h"
#include <iostream>
#include <sstream>
static std::vector<Card> carddb;
int main(int argc, char** argv)
{
    std::string deck_name{"popular_cards.md"};
    if(argc >=2 ) {
        deck_name=argv[1];
    }
    auto relation = init_service(deck_name, carddb);
    std::cout<<"输入手卡中怪兽的名字(one or more)：";
    std::vector<std::string> hand_cards;
    std::string line;
    while(getline(std::cin,line)) {
        std::string hand;
        std::stringstream ss{line};
        while(ss>>hand) {
            hand_cards.push_back(hand);
        }
        handle_request(hand_cards, carddb, relation);
        hand_cards.clear();
        std::cout<<"输入手卡中一张怪兽的名字(one or more)：";
    }
    return 0;
}
