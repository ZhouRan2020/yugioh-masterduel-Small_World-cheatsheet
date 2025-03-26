//
// Created by ZhouRan on 25-3-25.
//
#include "service.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include "util.h"
bool is_know(const Card& c1, const Card& c2);
std::vector<std::vector<bool>> init_service(std::string_view deck_name, std::vector<Card>& cdb)
{
    cdb.clear();
    std::string cdb_name{deck_name};
    std::fstream fs{cdb_name};
    std::string line;
    while(std::getline(fs,line)) {
        if(line.empty() || line[0]=='#' || line == "---") {
            continue;
        }
        Card card;
        std::stringstream ss{line};
        if(ss >> card.name >> card.level >> card.attr >> card.type >> card.atk >> card.def) {
            cdb.push_back(card);
        }
        std::string optional_alias;
        while(ss>>optional_alias) {
            cdb.back().alias.insert(optional_alias);
        }
    }
    int n = cdb.size();
    std::vector<std::vector<bool>> relation(n,std::vector<bool>(n,false));
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++){
            if(is_know(cdb[i],cdb[j])) {
                relation[i][j]=true;
            }
        }
    }
    std::cout<< "初始化成功，卡组的不同怪兽种类数 "<<cdb.size()<<'\n';
    return relation;
}
void handle_request(std::vector<std::string> const& hand_cards, std::vector<Card> const& cdb, std::vector<std::vector<bool>> const& relation)
{
    std::map<int,std::map<int,std::set<int>>> final_res;
    for(std::string hand:hand_cards) {
        auto it = std::find_if(cdb.begin(), cdb.end(),
                               [&](const Card &c) {
                                   return c.name == hand || find(c.alias.begin(), c.alias.end(), hand) != c.alias.end();
                               });
        if (it == cdb.end()) {
            return;
        }
        int idx = it - cdb.begin();
     //   std::cout << "卡片编号 " << idx << "，";
        std::map<int, std::set<int>> res;
        for (int i = 0; i < relation[idx].size(); i++) {
            if (relation[idx][i]) {
                for (int j = 0; j < relation[i].size(); j++) {
                    if (relation[i][j]) {
                        res[j].insert(i);
                    }
                }
            }
        }
        for (auto const &[i, mid]: res) {
            for (auto j: mid) {
                final_res[i][idx].insert(j);
            }
        }
    }
    for(auto const & [tar, paths]: final_res) {
        std::cout<<"** 检索"<<RED<< std::quoted(cdb[tar].name) <<RESET<< " via ";
        for(auto pr : paths) {
            std::cout<< "手卡"<<GREEN<<std::quoted(cdb[pr.first].name)<<RESET;
            std::cout << "卡组{";
            for(auto v = pr.second.begin();v!=pr.second.end();++v) {
                if(v!=pr.second.begin()) {
                    //std::cout << ",";
                }
                std::cout << std::quoted(cdb[*v].name);
            }
            std::cout<<"}";
        }
        std::cout<<'\n';
    }
}
bool is_know(const Card& c1, const Card& c2) {
    std::vector<bool> checklist(5,false);
    checklist[0]=c1.type==c2.type;
    checklist[1]=c1.attr==c2.attr;
    checklist[2]=c1.atk==c2.atk;
    checklist[3]=c1.def==c2.def;
    checklist[4]=c1.level==c2.level;
    return count(checklist.begin(),checklist.end(),true)==1;
}