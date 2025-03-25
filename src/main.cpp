#include "util.h"
#include "service.h"
#include <iostream>
static std::vector<Card> carddb;
int main(int argc, char** argv)
{
    std::string deck_name{"popular_cards.md"};
    if(argc >=2 ) {
        deck_name=argv[1];
    }
    auto relation = init_service(deck_name, carddb);
    std::cout<<"输入手卡中一张怪兽的名字：";
    std::string hand;
    while(std::cin>>std::skipws>>hand) {
        handle_request(hand, carddb, relation);
        std::cout<<"输入手卡中一张怪兽的名字：";
    }
    return 0;
}
