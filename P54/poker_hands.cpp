/*
 * Implementation of hand poker game in c++
 *
 * To-Dos:
 * 1) Implementation is super big. can be heavily optimized and make it nicer
 * 2) Missing some of the corner cases. Need to figure them out
 *
 * @Author: Rohith Uppala
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <string>
#include <map>
#include "../misc/utils.hpp"

using namespace std;

map<char, int> card_value_map = {
    {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
    {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
    {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}
};

int count_pairs(map<char, map<char, int> > cards) {
    map<char, int> value_map;
    for(auto& suit: cards) {
        for(auto &card_count: suit.second) {
            if(value_map.find(card_count.first) == value_map.end()) {
                value_map[card_count.first] = 1;
            } else {
                value_map[card_count.first] += 1;
            }
        }
    }
    int pair_count = 0;
    for(auto& elem: value_map) {
        if(elem.second == 2) pair_count += 1;
    }
    return pair_count;
}

bool has_three_pairs(map<char, map<char, int> > cards) {
    map<char, int> value_map;
    for(auto& suit: cards) {
        for(auto& card_count: suit.second) {
             if(value_map.find(card_count.first) == value_map.end()) {
                 value_map[card_count.first] = 1;
             } else {
                 value_map[card_count.first] += 1;
             }
        }
    }
    for(auto& elem: value_map) {
        if(elem.second == 3) return true;
    }
    return false;
}

bool has_straight_values(map<char, map<char, int> > cards) {
    vector<int> values;
    for(auto& suit: cards) {
        for(auto& card_count: suit.second) {
            values.push_back(card_value_map[card_count.first]);
        }
    }
    sort(values.begin(), values.end());
 
    if(values[values.size() - 1] - values[0] == values.size() + 1) return true;
    else return false;
}    

bool has_flush(map<char, map<char, int> > cards) {
    int suit_count = 0;
    for(auto& suit: cards) {
        suit_count = suit_count + 1;
    }
    return suit_count == 1 ? true : false;
}

bool has_straight(map<char, map<char, int> > cards) {
    return has_straight_values(cards);
}

bool has_full_house(map<char, map<char, int> > cards) {
    return has_three_pairs(cards) && count_pairs(cards) ? true : false;
}

bool has_four_of_a_kind(map<char, map<char, int> > cards) {
    for(auto& suit: cards) {
        for(auto& card_count: suit.second) {
            if(card_count.second == 4)
                return true;
        }
    }
    return false;
}

bool has_straight_flush(map<char, map<char, int> > cards) {
    return has_flush(cards) && has_straight_values(cards) ? true : false;
}

bool has_royal_flush(map<char, map<char, int> > cards) {
    vector<char> rf {'T', 'J', 'Q', 'K', 'A'};

    if(has_flush(cards) && has_straight_values(cards)) {
        for(auto& suit: cards) {
            for(auto& card_count: suit.second) {
                if(find(rf.begin(), rf.end(), card_count.first) == rf.end()) return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

int poker_rank(map<char, map<char, int> > cards) {
    int pair_count = count_pairs(cards);
     
    if(has_royal_flush(cards)) return 9;
    else if(has_straight_flush(cards)) return 8;
    else if(has_four_of_a_kind(cards)) return 7;
    else if(has_full_house(cards)) return 6;
    else if(has_flush(cards)) return 5;
    else if(has_straight(cards)) return 4;
    else if(has_three_pairs(cards)) return 3;
    else if(pair_count == 2) return 2;
    else if(pair_count == 1) return 1;
    else return 0;
}

map<char, map<char, int> > parse_player_cards(vector<string> player_cards) {
    map<char, map<char, int> > pc_map;
    
    for(auto player_card: player_cards) {
        char value = player_card[0], suit = player_card[1];
        if(pc_map.find(suit) == pc_map.end()) {
            map<char, int> suit_map;
            suit_map[value] = 1;
            pc_map[suit] = suit_map;
        } else {
            map<char, int> existing_suit_map = pc_map[suit];
            if(existing_suit_map.find(value) == existing_suit_map.end()) {
                existing_suit_map[value] = 1;
            } else {
                existing_suit_map[value] += 1;
            }
            pc_map[suit] = existing_suit_map;
        }
    }

    return pc_map;
}


vector<vector<map<char, map<char, int> > > > process_file() {
    string line;
    ifstream input_file("poker.txt");
    vector<vector<map<char, map<char, int> > > > input;

    if(input_file.is_open()) {
        while(getline(input_file, line)) {
            vector<map<char, map<char, int> > > game;
            vector<string> cards;
            boost::split(cards, line, boost::is_any_of(" "));

            const int mid = cards.size() / 2;
            vector<string> p1(cards.begin(), cards.begin() + mid);
            vector<string> p2(cards.begin() + mid, cards.end());
            
            map<char, map<char, int> > p1_cards = parse_player_cards(p1);
            map<char, map<char, int> > p2_cards = parse_player_cards(p2);
        
            game.push_back(p1_cards);
            game.push_back(p2_cards);
        
            input.push_back(game);
        }
    }

    return input;
}


vector<int> get_values_of_cards(map<char, map<char, int> > cards) {
    vector<int> card_values;
    for(auto& suit: cards) {
        for(auto& card_count: suit.second) {
            card_values.push_back(card_value_map[card_count.first]);
        }
    }
    return card_values;
}

// you don't have a winner here, as it's a tie
int get_winner_from_royal_flush(map<char, map<char, int> > p1, map<char, map<char, int> > p2) {
    return 0;
}

int get_winner_from_straight_flush(map<char, map<char, int> > p1, map<char, map<char, int> > p2) {
    vector<int> p1_cards = get_values_of_cards(p1);
    vector<int> p2_cards = get_values_of_cards(p2);

    sort(p1_cards.begin(), p1_cards.end());
    sort(p2_cards.begin(), p2_cards.end());

    for(int i=p2_cards.size()-1; i>=0; i--) {
        if(p1_cards[i] > p2_cards[i]) return 1;
        else if(p1_cards[i] < p2_cards[i]) return 2;
    }
    return 0;
}


int get_winner_from_four_of_a_kind(map<char, map<char, int> > p1, map<char, map<char, int> > p2) {
    vector<int> p1_cards = get_values_of_cards(p1);
    vector<int> p2_cards = get_values_of_cards(p2);
    
    map<int, int> p1_count, p2_count;
    int p1_common_value, p1_value, p2_common_value, p2_value;
    
    for(auto& elem: p1_cards) {
        if(p1_count.find(elem) == p1_count.end()) p1_count[elem] = 1;
        else p1_count[elem] += 1;
    }

    for(auto& elem: p2_cards) {
        if(p2_count.find(elem) == p2_count.end()) p2_count[elem] = 1;
        else p2_count[elem] += 1;
    }

    for(auto& elem: p1_count) {
        if(elem.second == 4) p1_common_value = elem.first;
        else p1_value = elem.first;
    }

    for(auto& elem: p2_count) {
        if(elem.second != 4) p2_value = elem.first;
        else p2_common_value = elem.first;
    }

    int winner = 0;
    if(p1_common_value > p2_common_value) winner = 1;
    else if(p1_common_value < p2_common_value) winner = 2;
    else {
        if(p1_value > p2_value) winner = 1;
        else if(p1_value < p2_value) winner = 2;
    }

    return winner;
}


int get_winner_from_full_house(map<char, map<char, int> > p1, map<char, map<char, int> > p2) {
    vector<int> p1_cards = get_values_of_cards(p1);
    vector<int> p2_cards = get_values_of_cards(p2);
 
    map<int, int> p1_count, p2_count;
    int p1_first, p1_second, p2_first, p2_second;
 
    for(auto& elem: p1_cards) {
        if(p1_count.find(elem) == p1_count.end()) p1_count[elem] = 1;
        else p1_count[elem] += 1;
    }   
 
    for(auto& elem: p2_cards) {
        if(p2_count.find(elem) == p2_count.end()) p2_count[elem] = 1;
        else p2_count[elem] += 1;
    }
           
    for(auto& elem: p1_count) {
        if(elem.second == 3) p1_first = elem.first;
        else p1_second = elem.first;
    }   
 
    for(auto& elem: p2_count) {
        if(elem.second == 3) p2_first = elem.first;
        else p2_second = elem.first;
    }

    int winner = 0;
    if(p1_first > p2_first) winner = 1;
    else if(p1_first < p2_first) winner = 2;
    else {
        if(p1_second > p2_second) winner = 1;
        else if(p1_second < p2_second) winner = 2;
    }
 
    return winner;
}


int get_winner_from_flush(map<char, map<char, int> > p1, map<char, map<char, int> > p2) {
    return get_winner_from_straight_flush(p1, p2);
}

int get_winner_from_straight(map<char, map<char, int> > p1, map<char, map<char, int> > p2) {
    return get_winner_from_straight_flush(p1, p2);
}

int get_winner_from_three_of_a_kind(map<char, map<char, int> > p1, map<char, map<char, int> > p2) {
    vector<int> p1_cards = get_values_of_cards(p1);
    vector<int> p2_cards = get_values_of_cards(p2);
 
    map<int, int> p1_count, p2_count;
    int p1_common_value, p2_common_value;
    vector<int> p1_others, p2_others;

    for(auto& elem: p1_cards) {
        if(p1_count.find(elem) == p1_count.end()) p1_count[elem] = 1;
        else p1_count[elem] += 1;
    }   
 
    for(auto& elem: p2_cards) {
        if(p2_count.find(elem) == p2_count.end()) p2_count[elem] = 1;
        else p2_count[elem] += 1;
    }
           
    for(auto& elem: p1_count) {
        if(elem.second == 3) p1_common_value = elem.first;
        else p1_others.push_back(elem.first);
    }   
 
    for(auto& elem: p2_count) {
        if(elem.second == 3) p2_common_value = elem.first;
        else p2_others.push_back(elem.first);
    }

    int winner = 0;
    if(p1_common_value > p2_common_value) winner = 1;
    else if(p1_common_value < p2_common_value) winner = 2;
    else {
        sort(p1_others.begin(), p1_others.end());
        sort(p2_others.begin(), p2_others.end());
        
        for(int i=p2_others.size()-1; i>=0; i--) {
            if(p1_others[i] > p2_others[i]) winner = 1;
            else if(p1_others[i] < p2_others[i]) winner = 2;
        }
    }
    return winner;
}

int get_winner_from_two_pairs(map<char, map<char, int> > p1, map<char, map<char, int> > p2) {
    vector<int> p1_cards = get_values_of_cards(p1);
    vector<int> p2_cards = get_values_of_cards(p2);
 
    map<int, int> p1_count, p2_count;
    int p1_other_value, p2_other_value;
    vector<int> p1_common, p2_common;

    for(auto& elem: p1_cards) {
        if(p1_count.find(elem) == p1_count.end()) p1_count[elem] = 1;
        else p1_count[elem] += 1;
    }   
 
    for(auto& elem: p2_cards) {
        if(p2_count.find(elem) == p2_count.end()) p2_count[elem] = 1;
        else p2_count[elem] += 1;
    }
           
    for(auto& elem: p1_count) {
        if(elem.second == 2) p1_common.push_back(elem.first);
        else p1_other_value = elem.first;
    }   
 
    for(auto& elem: p2_count) {
        if(elem.second != 3) p2_common.push_back(elem.first);
        else p2_other_value = elem.first;
    }

    int winner = 0;
    
    sort(p1_common.begin(), p1_common.end());
    sort(p2_common.begin(), p2_common.end());
        
    for(int i=p2_common.size()-1; i>=0; i--) {
        if(p1_common[i] > p2_common[i]) winner = 1;
        else if(p1_common[i] < p2_common[i]) winner = 2;
    }

    if(winner == 0) {
        if(p1_other_value > p2_other_value) winner = 1;
        else if(p1_other_value < p2_other_value) winner = 2;
    }

    return winner;
}

int get_winner_from_one_pair(map<char, map<char, int> > p1, map<char, map<char, int> > p2) {
    vector<int> p1_cards = get_values_of_cards(p1);
    vector<int> p2_cards = get_values_of_cards(p2);
 
    map<int, int> p1_count, p2_count;
    
    int p1_common_value, p2_common_value;
    vector<int> p1_others, p2_others;

    for(auto& elem: p1_cards) {
        if(p1_count.find(elem) == p1_count.end()) p1_count[elem] = 1;
        else p1_count[elem] += 1;
    }   
 
    for(auto& elem: p2_cards) {
        if(p2_count.find(elem) == p2_count.end()) p2_count[elem] = 1;
        else p2_count[elem] += 1;
    }
           
    for(auto& elem: p1_count) {
        if(elem.second != 2) p1_others.push_back(elem.first);
        else p1_common_value = elem.first;
    }
 
    for(auto& elem: p2_count) {
        if(elem.second != 2) p2_others.push_back(elem.first);
        else p2_common_value = elem.first;
    }

    int winner = 0;
    
    if(p1_common_value > p2_common_value) winner = 1;
    else if(p1_common_value < p2_common_value) winner = 2;
    else {
        sort(p1_others.begin(), p1_others.end());
        sort(p2_others.begin(), p2_others.end());
        for(int i=p2_others.size()-1; i>=0; i--) {
            if(p1_others[i] > p2_others[i]) winner = 1;
            else if(p1_others[i] < p2_others[i]) winner = 2;
        }
    }

    return winner;
}

int get_winner_from_high_card(map<char, map<char, int> > p1, map<char, map<char, int> > p2) {
    return get_winner_from_straight_flush(p1, p2);
}

int get_winner_of_poker_hand(map<char, map<char, int> > p1, map<char, map<char, int> > p2, int rank) {

    int winner;
    enum ranks { HIGH_CARD, ONE_PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH };

    switch(rank) {
        case ROYAL_FLUSH:
            winner = get_winner_from_royal_flush(p1, p2); break;
        case STRAIGHT_FLUSH:
            winner = get_winner_from_straight_flush(p1, p2); break;
        case FOUR_OF_A_KIND:
            winner = get_winner_from_four_of_a_kind(p1, p2); break;
        case FULL_HOUSE:
            winner = get_winner_from_full_house(p1, p2); break;
        case STRAIGHT:
            winner = get_winner_from_straight(p1, p2); break;
        case FLUSH:
            winner = get_winner_from_flush(p1, p2); break;
        case THREE_OF_A_KIND:
            winner = get_winner_from_three_of_a_kind(p1, p2); break;
        case TWO_PAIRS:
            winner = get_winner_from_two_pairs(p1, p2); break;
        case ONE_PAIR:
            winner = get_winner_from_one_pair(p1, p2); break;
        default:
            winner = get_winner_from_high_card(p1, p2); break;
    }

    return winner;
}


int solve(vector<vector<map<char, map<char, int> > > > input) {
    int p1_wins = 0, p2_wins = 0;
    for(auto& play: input) {
        int p1_prev_wins = p1_wins; 
        int p1_rank = poker_rank(play[0]);
        int p2_rank = poker_rank(play[1]);
        if(p1_rank > p2_rank) p1_wins += 1;
        else if(p1_rank < p2_rank) p2_wins += 1;
        else if(p1_rank == p2_rank) {
            int winner = get_winner_of_poker_hand(play[0], play[1], p1_rank);
            if(winner == 1) p1_wins += 1;
            else if(winner == 2) p2_wins += 1;
        }
    }
    return p1_wins;
}

int main() {
    vector<vector<map<char, map<char, int> > > > input = process_file();
    int result = solve(input);
    cout << "Number of times player one win: " << result << endl;
    return 0;
}
