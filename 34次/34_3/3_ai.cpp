#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

// 用于存放单词信息的结构体
struct Word {
    vector<int> tokens; // 当前单词被切分后的 token ID 序列
    int freq;           // 该单词在输入中出现的频率
};

// 简单的 hash 函数，用于 unordered_map 加速
struct PairHash {
    size_t operator()(const long long& key) const {
        uint64_t x = key;
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
};

int main() {
    // 提高输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<pair<string, int>> raw_words(n);
    set<char> char_set;
    for (int i = 0; i < n; ++i) {
        cin >> raw_words[i].first >> raw_words[i].second;
        // 收集所有出现的字符
        for (char c : raw_words[i].first) char_set.insert(c);
    }

    vector<string> vocab; // 词表：存储字符串
    
    // 1. 初始化：将所有字符按字典序加入词表
    // 根据题目保证 m >= 字符种类数，直接全部加入
    for (char c : char_set) {
        vocab.push_back(string(1, c));
    }

    // 将字符映射到对应的 ID
    unordered_map<string, int> string_to_id;
    for (int i = 0; i < (int)vocab.size(); ++i) {
        string_to_id[vocab[i]] = i;
    }

    // 初始化所有单词的 token 序列
    vector<Word> words(n);
    for (int i = 0; i < n; ++i) {
        words[i].freq = raw_words[i].second;
        for (char c : raw_words[i].first) {
            words[i].tokens.push_back(string_to_id[string(1, c)]);
        }
    }

    // 2. 迭代合并，直到词表大小达到 m
    while ((int)vocab.size() < m) {
        // 统计所有相邻对的频率
        unordered_map<long long, long long, PairHash> counts;
        bool can_merge = false;
        for (int i = 0; i < n; ++i) {
            if (words[i].tokens.size() < 2) continue;
            can_merge = true;
            for (size_t j = 0; j < words[i].tokens.size() - 1; ++j) {
                // 将两个 32 位 ID 组合成一个 64 位 long long 作为 key
                long long key = ((long long)words[i].tokens[j] << 32) | (unsigned int)words[i].tokens[j+1];
                counts[key] += words[i].freq;
            }
        }

        // 如果没有任何对可以合并，提前退出
        if (!can_merge) break;

        long long max_f = -1;
        int best_l = -1, best_r = -1;
        string best_s = "";

        // 寻找最佳合并对
        for (auto const& [key, f] : counts) {
            if (f < max_f) continue; // 剪枝

            int l_id = (int)(key >> 32);
            int r_id = (int)(key & 0xFFFFFFFFLL);
            string cur_s = vocab[l_id] + vocab[r_id];

            bool update = false;
            if (f > max_f) update = true;
            else { // 频率相同时的抉择
                if (cur_s.length() < best_s.length()) update = true;
                else if (cur_s.length() == best_s.length() && cur_s < best_s) update = true;
            }

            if (update) {
                max_f = f;
                best_l = l_id;
                best_r = r_id;
                best_s = cur_s;
            }
        }

        // 将新词加入词表
        int new_id = vocab.size();
        vocab.push_back(best_s);

        // 更新所有单词的序列
        for (int i = 0; i < n; ++i) {
            vector<int> &tks = words[i].tokens;
            if (tks.size() < 2) continue;

            vector<int> next_tks;
            next_tks.reserve(tks.size());
            bool changed = false;
            for (int j = 0; j < (int)tks.size(); ++j) {
                // 寻找匹配的最佳对并合并
                if (j + 1 < (int)tks.size() && tks[j] == best_l && tks[j+1] == best_r) {
                    next_tks.push_back(new_id);
                    j++; // 跳过右侧元素，实现左到右合并
                    changed = true;
                } else {
                    next_tks.push_back(tks[j]);
                }
            }
            if (changed) tks = std::move(next_tks);
        }
    }

    // 3. 输出词表中的前 m 个词
    for (int i = 0; i < (int)vocab.size() && i < m; ++i) {
        cout << vocab[i] << "\n";
    }

    return 0;
}