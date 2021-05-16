# leetcode笔记

#### [1. 两数之和](https://leetcode-cn.com/problems/two-sum/)-哈希法

```
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> umap; //第一个int表示值，第二个int表示值所在下标
        for (int i = 0; i < nums.size(); ++i) {
            unordered_map<int, int>::iterator it = umap.find(target - nums[i]); //unordered_map的插入和查找效率为O(1)
            //可以简写为 auto it = umap.find(target - nums[i]);
            //target - nums[i] 这种写法很方便匹配值
            if (it != umap.end()) { //说明找到了匹配值
                return vector<int> {it->second, i};
            }
            else {
                umap.insert(pair<int, int> (nums[i], i));
            }
        }
        return {}; //这个地方是不满足时的返回值，题目一定满足，所以这里随便写
    }
};
```

#### [53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)-贪心

```
class Solution {

public:

  int maxSubArray(vector<int>& nums) {

​    //贪心的思路 如果相加的和为负则从下一个重新开始

​    //因为一个负数的和 + 下一个数一定是会变小的

​    int maxSum = INT_MIN; //不排除有非常小的数值出现的情况，使用INT_MIN

​    int sum = 0;

​    for (int i = 0; i < nums.size(); ++i) { //这里注意nums.size()是O(1)的操作

​      //需要考虑整个数组都是负数的情况

​      sum += nums[i];

​      maxSum = max(sum, maxSum);

​      if (sum < 0) sum = 0;

​    }

​    return maxSum;

  }

};
```

#### [206. 反转链表](https://leetcode-cn.com/problems/reverse-linked-list/)

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = nullptr; 
        ListNode *cur = head;
        ListNode *tmp = nullptr;        //定义在这里是为了节省一点资源
        while (cur != nullptr) {
            //ListNode *tmp = nullptr;  //这里定义也是可以的
            tmp = cur->next;            //保存cur->next的内容
            cur->next = pre;
            pre = cur;                  
            cur = tmp;
        }
        return pre;
    }
};

//定义虚拟头结点的做法
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *dummyHead = new ListNode(0, nullptr); //定义一个虚拟头结点ListNode(0, head); 0的值随便写 //这个是默认条件中构造函数之一
        ListNode *cur = head;
        ListNode *tmp = nullptr; //省点资源
        while (cur != nullptr) {
            tmp = cur->next;
            //虚拟头结点的头插法
            cur->next = dummyHead->next; 
            dummyHead->next = cur;
            cur = tmp;
        }
        return dummyHead->next;
    }
};
```

#### [21. 合并两个有序链表](https://leetcode-cn.com/problems/merge-two-sorted-lists/)-使用虚拟头结点

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *dummyHead = new ListNode(0, nullptr);
        ListNode *newcur = dummyHead;
        ListNode *cur1 = l1;
        ListNode *cur2 = l2;
        while (cur1 || cur2) {
            //考虑cur1或者cur2有一个先遍历完的情况
            if (cur1 != nullptr && cur2 == nullptr) {
                ListNode *tmp = cur1;
                cur1 = cur1->next; 
                newcur->next = tmp;
                newcur = newcur->next;
            }
            else if (cur1 == nullptr && cur2 != nullptr) {
                ListNode *tmp = cur2;
                cur2 = cur2->next;
                newcur->next = tmp;
                newcur = newcur->next;
            }
            else { //cur1和cur2都没有遍历完链表
                if (cur1->val < cur2->val) { //这个链表是升序的，小的在前
                    ListNode *tmp = cur1;
                    cur1 = cur1->next;
                    newcur->next = tmp;
                    newcur = newcur->next;
                }
                else {
                    ListNode *tmp = cur2;
                    cur2 = cur2->next;
                    newcur->next = tmp;
                    newcur = newcur->next;
                }
            }  
        }
        return dummyHead->next;
    }
};

```

#### [70. 爬楼梯](https://leetcode-cn.com/problems/climbing-stairs/)-动规

```
class Solution {
public:
    int climbStairs(int n) {
        // 1 = 1
        // 2 = 2
        // 3 = 3
        // 4 = 5
        // 第n个数等于n-1和n-2数之和
        if (n <= 2) return n;
        int dp[2] = {1, 2};
        for (int i = 3; i <= n; ++i) {
            int tmp = dp[1];        //以i = 3举例 tmp = 1层台阶的可能性
            dp[1] = dp[0] + dp[1];  //第三层等于1层 + 2层的总可能性 dp[1]更新为第三层的可能性
            dp[0] = tmp;           //dp[0]更新为第二层的可能性
        }
        return dp[1];
    }
};
```

#### [20. 有效的括号](https://leetcode-cn.com/problems/valid-parentheses/)-使用stack

```
class Solution {
public:
    bool isValid(string s) { 
        //利用栈的特性解决匹配问题
        //栈是后进先出的，括号的话例如[({})] 
        //匹配到左半部分,栈加入其匹配的右半部分
        stack<char> st;
        // for (int i : s) {
        //     if (i == '{') st.push('}');
        //     else if (i == '(') st.push(')');
        //     else if (i == '[') st.push(']');
        //     else {  //这一步说明匹配到了右括号
        //         if (i != st.top()) return false; //匹配失败
        //         else st.pop(); //匹配成功,此括号出栈
        //     }
        // }
        //上面没有考虑到"]"这种情况
        for (int i : s) {
            if (i == '{') st.push('}');
            else if (i == '(') st.push(')');
            else if (i == '[') st.push(']');
            else if (st.empty() || i != st.top()) return false; //栈为空是如果还匹配到了右半的括号一定是错误的
            else st.pop(); //匹配成功则弹出这个值
        }
        //有可能出现这种 {[[]] 这种之前的循环是找不出错的,判断栈是否为空应为括号匹配的话栈一定为空了
        if (st.empty()) return true; //栈为空则正确
        return false;
    }
};
```

#### [122. 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)-贪心

```
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //prices[3] - prices[0] = prices[3] - prices[2] + prices[2] - prices[1] + prices[1] - prices[0];
        //因为上面的推导公式得出一个结论,想要最大利润只需把上面每一段的正的相加即可，这就是这一段所有的正收益
        int mProfit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] - prices[i - 1] > 0) 
                mProfit += prices[i] - prices[i - 1];
        }
        return mProfit;
    }
};
```

#### [9. 回文数](https://leetcode-cn.com/problems/palindrome-number/)

```
class Solution {
public:
    bool isPalindrome(int x) {
        //负数不是回文数
        if (x < 0) return false;
        //最低位变最高位
        //int sum = 0; //1234567899 超出范围
        long sum = 0; //为什么会超出范围呢？
        // while (x) { //这样写犯了一个极大的错误,那就是x的值会被改变
        //     sum = x % 10 + sum * 10;
        //     x /= 10;
        // }
        int tmp = x;
        while (tmp) {
            sum = tmp % 10 + sum * 10;
            tmp /= 10;
        }
        return sum == x;     
    }
};
```

