#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> accountsMerge(const vector<vector<string>>& accounts) {
        map<string, int> email2id;
        map<int, set<string>> id2emails;
        int i = 0;
        int uid = 0;
        for (const auto& account : accounts) {
            const string& name = account[0];
            uid = i;
            set<int> mergedIds;
            for (int eid = 1; eid < account.size(); eid++) {
                const string& email = account[eid];
                auto iter = email2id.find(email);
                if (iter != email2id.end()) {
                    mergedIds.insert(iter->second);
                }
            }
            // 未出现过
            if (mergedIds.size() == 0) {
                for (int eid = 1; eid < account.size(); eid++) {
                    const string& email = account[eid];
                    // cout << "email:" << email  << endl;
                    email2id[email] = uid;
                    id2emails[uid].insert(email);
                }
            } else {
                uid = *min_element(mergedIds.begin(), mergedIds.end());
                set<string> mergedEmails;
                for (auto uidTmp : mergedIds) {
                    mergedEmails.insert(id2emails[uidTmp].begin(), id2emails[uidTmp].end());
                    for (int eid = 1; eid < account.size(); eid++) {
                        mergedEmails.insert(account[eid]);
                    }
                    if (uidTmp != uid) {
                        id2emails.erase(uidTmp);
                    }
                }
                for (const auto& emailTmp : mergedEmails) {
                    email2id[emailTmp] = uid;
                }
                id2emails[uid] = mergedEmails;
            }
            i++;
        }

        vector<vector<string>> ret(id2emails.size());
        int idx = 0;
        for (const auto& iter : id2emails) {
            ret[idx].resize(iter.second.size() + 1);
            ret[idx][0] = accounts[iter.first][0];
            const set<string>& emails = iter.second;
            int j = 1;
            for (const auto& email: emails) {
                ret[idx][j++] = email;
            }
            idx++;
        }
        return ret;

        // for (auto p : email2id) {
        //     cout << p.first << " -> "<< p.second << endl;
        // }
        // for (auto p : id2emails) {
        //     cout << p.first << "; ";
        //     for (auto e : p.second) {
        //         cout << e << ", ";
        //     }
        //     cout << endl;
        // }


    }
};

int main() {
    vector<vector<string>> accounts = {{"John", "johnsmith@mail.com", "john00@mail.com"}, {"John", "johnnybravo@mail.com"}, {"John", "johnsmith@mail.com", "john_newyork@mail.com"}, {"Mary", "mary@mail.com"}};
    Solution s;
    vector<vector<string>> ret = s.accountsMerge(accounts);
    for (auto& v : ret) {
        for (auto& s : v) {
            cout << s << ",";
        }
        cout << endl;
    }
    return 0;
}