//
// Created by ZhouRan on 25-3-25.
//

#ifndef YUGIOH_MASTER_DUEL_KIT_SERVICE_H
#define YUGIOH_MASTER_DUEL_KIT_SERVICE_H
#include <set>
#include <locale>
enum Attribute {
    light, dark, water, fire, wind, earth, divine
};
enum MonsterType {
    huanlong, konglong, yanshi, tianshi, emo, busi, jixie, zhiwu, kunchong, yan, lei, shui,
    yu, hailong, chuangzaoshen, pachonglei, longzu, mofashi, niandongli, huanshenshou, shou, niaoshou,
    shouzhanshi, zhanshi, dianzijie, huanxiangmo
};
struct Card {
    std::string name;
    unsigned level{114514};
    std::string attr;
    std::string type;
    unsigned atk{114514};
    unsigned def{114514};
    std::set<std::string> alias;
};
std::vector<std::vector<bool>> init_service(std::string_view deck_name, std::vector<Card>&);
void handle_request(std::vector<std::string> const& hand, std::vector<Card> const&, std::vector<std::vector<bool>> const& relation);
#endif //YUGIOH_MASTER_DUEL_KIT_SERVICE_H
