/* ------------------------------------------------------------------|
给定一个单词数组和一个长度 maxWidth，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。

你应该使用“贪心算法”来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 ' ' 填充，使得每行恰好有 maxWidth 个字符。

要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。

文本的最后一行应为左对齐，且单词之间不插入额外的空格。

说明:

单词是指由非空格字符组成的字符序列。
每个单词的长度大于 0，小于等于 maxWidth。
输入单词数组 words 至少包含一个单词。
示例:

输入:
words = ["This", "is", "an", "example", "of", "text", "justification."]
maxWidth = 16
输出:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
示例 2:

输入:
words = ["What","must","be","acknowledgment","shall","be"]
maxWidth = 16
输出:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
解释: 注意最后一行的格式应为 "shall be    " 而不是 "shall     be",
     因为最后一行应为左对齐，而不是左右两端对齐。
     第二行同样为左对齐，这是因为这行只包含一个单词。
示例 3:

输入:
words = ["Science","is","what","we","understand","well","enough","to","explain",
         "to","a","computer.","Art","is","everything","else","we","do"]
maxWidth = 20
输出:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/text-justification
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/* dfs
*
*	执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
*	内存消耗：7.9 MB, 在所有 C++ 提交中击败了5.09%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

//vector<string> res;
//string tmp;
//int n;
//int cnt;
//
//void justification(string& tmp,int& cnt, const int& maxWidth) {
//    if (cnt == 1) {
//        tmp += string(maxWidth - tmp.size(), ' ');
//        return;
//    }
//    if (tmp[tmp.size() - 1] == ' ') {
//        tmp.erase(tmp.size() - 1);
//        int spacesum = maxWidth - tmp.size();
//        cnt -= 1;
//        vector<int> spaces(cnt, 0);
//        int i = 0;
//        while (spacesum) {
//            spaces[i % cnt]++;
//            i++;
//            spacesum--;
//        }
//        i = 0;
//        int nth = 0;
//        while (i < tmp.size()) {
//            if (tmp[i] == ' ') {
//                tmp.insert(i, string(spaces[nth++], ' '));
//                if (nth == spaces.size()) {
//                    return;
//                }
//                i += spaces[nth - 1] + 1;
//            }
//            else {
//                i++;
//            }
//        }
//    }
//    else {
//        return;
//    }
//}
//void dfs(int index, int& cnt, vector<string>& words, const int maxWidth) {
//    if (index == n) {
//        tmp += string(maxWidth - tmp.size(), ' ');
//        res.emplace_back(tmp);
//        return;
//    }
//    if (tmp.size() + words[index].size() > maxWidth) {
//        justification(tmp, cnt, maxWidth);
//        res.emplace_back(tmp);
//        tmp = {};
//        cnt = 0;
//        dfs(index, cnt, words, maxWidth);
//    }
//    else {
//        if (tmp.size() + words[index].size() + 1 <= maxWidth) {
//            tmp += words[index] + ' ';
//        }
//        else {
//            tmp += words[index];
//        }
//        cnt++;
//        dfs(index + 1, cnt, words, maxWidth);
//    }
//}
//
//vector<string> fullJustify(vector<string>& words, int maxWidth) {
//    n = words.size();
//    cnt = 0;
//    dfs(0, cnt, words, maxWidth);
//    return res;
//}

/*  dfs
*
*	执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
*	内存消耗：7.2 MB, 在所有 C++ 提交中击败了76.66%的用户
*/
void justification(string& tmp,int& count, const int& maxWidth) {
    if (!count) {
        tmp += string(maxWidth - tmp.size(), ' ');
        return;
    }
    if (tmp[tmp.size() - 1] == ' ') {
        count--;
        tmp.erase(tmp.size() - 1);
        int spacesnum = maxWidth - tmp.size();
        vector<int> spaces(count, 0);
        int i = 0;
        while (spacesnum) {
            spaces[i % count]++;
            i++;
            spacesnum--;
        }
        i = 0;
        int nth = 0;
        while (i < tmp.size()) {
            if (tmp[i] == ' ') {
                tmp.insert(i, string(spaces[nth], ' '));
                if (nth == spaces.size()) {
                    return;
                }
                i += spaces[nth++] + 1;
            }
            else {
                i++;
            }
        }
    }
    else {
        return;
    }
}
vector<string> fullJustify(vector<string>& words, int maxWidth) {
    int n = words.size();
    string tmp = {};
    int cnt = 0;
    vector<string> res;
    for (int i = 0; i <= n; i++) {
        if (i == n || tmp.size() + words[i].size() > maxWidth) {
            if (i == n) {
                tmp += string(maxWidth - tmp.size(), ' ');
                res.emplace_back(tmp);
                return res;
            }
            justification(tmp, cnt, maxWidth);
            res.emplace_back(tmp);
            tmp = {};
            cnt = 0;
        }
        if (tmp.size() + words[i].size() + 1 <= maxWidth) {
            tmp += words[i] + ' ';
            cnt++;
        }
        else {
            tmp += words[i];
        }
    }
    return res;
}

int main() {
    vector<string> words = { "What","must","be","acknowledgment","shall","be" };
    fullJustify(words, 16);
}