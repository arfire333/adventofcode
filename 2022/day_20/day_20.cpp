#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

/* 
 * Thanks to https://www.twitch.tv/qiqi_impact for helping realize
 * I was overcomplicating the modulus for part b.  Of course other
 * parts may still be over complicated but it works. :)
 */

struct Node {
    int64_t val = 0;
    int64_t bigval = 0;
    Node *prev = nullptr;
    Node *next = nullptr;
};

void print_list(Node *start) {
    Node *curr = start;
    while (curr->next != start) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << curr->val << "\n";
}
void print_list_big(Node *start) {
    Node *curr = start;
    while (curr->next != start) {
        cout << curr->bigval << " ";
        curr = curr->next;
    }
    cout << curr->bigval << "\n";
}
void shift_right(Node *&curr, int64_t n = 1) {

    while (n > 0LL) {
        Node *left = curr->prev;
        Node *right = curr->next;
        curr->prev = right;
        curr->next = right->next;
        curr->prev->next = curr;
        curr->next->prev = curr;
        right->prev = left;
        left->next = right;
        n--;
    }
}
void shift_left(Node *&curr, int64_t n = 1) {

    while (n > 0LL) {
        Node *left = curr->prev;
        Node *right = curr->next;
        curr->prev = left->prev;
        curr->next = left;
        curr->prev->next = curr;
        curr->next->prev = curr;
        right->prev = left;
        left->next = right;
        n--;
    }
}

int64_t problem_a(vector<Node *> file) {
    for (auto node : file) {
        int64_t shift = node->val;
        if (node->val > 0) {
            while (shift > 0) {
                shift_right(node);
                shift--;
            }
        } else if (shift < 0) {
            while (shift < 0) {
                shift_left(node);
                shift++;
            }
        }
    }
    int64_t zero_idx = 0;
    for (zero_idx = 0; zero_idx < file.size(); zero_idx++) {
        if (file[zero_idx]->val == 0) {
            break;
        }
    }
    cout << "Zero Idx: " << zero_idx << "\n";
    int64_t sum = 0;
    Node *curr = file[zero_idx]->next;
    for (int64_t i = 1; i <= 3000; i++) {
        if ((i % 1000) == 0) {
            cout << curr->val << "\n";
            sum += curr->val;
        }
        curr = curr->next;
    }

    return sum;
}

int64_t problem_b(vector<Node *> file) {
    Node *zero_node = nullptr;
    for (int i = 0; i < file.size(); i++) {
        if (file[i]->val == 0) {
            zero_node = file[i];
        }
        if (file[i]->bigval < 0) {
            file[i]->val = -file[i]->bigval;
        }
        int64_t before = file[i]->val;
        int64_t after = file[i]->val % (file.size() - 1);
        file[i]->val = after;
    }
    for (int i = 0; i < 10; i++) {
        for (auto node : file) {
            int64_t shift = node->val;
            if (node->bigval > 0) {
                shift_right(node, shift);
            } else if (node->bigval < 0) {
                shift_left(node, shift);
            }
        }
    }
    int64_t zero_idx = 0;
    for (zero_idx = 0; zero_idx < file.size(); zero_idx++) {
        if (file[zero_idx]->bigval == 0) {
            break;
        }
    }
    cout << "Zero Idx: " << zero_idx << "\n";
    int64_t sum = 0;
    Node *curr = zero_node->next;
    for (int64_t i = 1; i <= 3000; i++) {
        if ((i % 1000) == 0) {
            cout << curr->bigval << "\n";
            sum += curr->bigval;
        }
        curr = curr->next;
    }

    return sum;
}

int main(int argc, char **argv) {
    string s;
    vector<Node *> file;
    vector<Node *> fileb;
    Node *first = nullptr;
    Node *next = nullptr;
    Node *firstb = nullptr;
    Node *nextb = nullptr;
    int64_t key = 811589153;
    
    Node *zero_node = nullptr;
    while (std::getline(cin, s)) {
        int64_t val = std::stoi(s);
        next = new Node();
        nextb = new Node();
        next->val = val;

        nextb->bigval = val * key;
        nextb->val = nextb->bigval;

        if (first == nullptr) {
            first = next;
            firstb = nextb;
        } else {
            file.back()->next = next;
            fileb.back()->next = nextb;
            next->prev = file.back();
            nextb->prev = fileb.back();
        }
        if (next->val == 0) {
            zero_node = next;
        }
        file.push_back(next);
        fileb.push_back(nextb);
    }
    next->next = first;
    first->prev = next;
    nextb->next = firstb;
    firstb->prev = nextb;
    // File created    
    cout << "File Size: " << file.size() << "\n";
    int64_t ans1 = problem_a(file);
    int64_t ans2 = problem_b(fileb);

    cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
    return 0;
}