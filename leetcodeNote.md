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

#### [160. 相交链表](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/)

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
//错误示例
// class Solution {
// public:
//     ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//         //前提是能相交的情况下
//         ListNode *curA = headA;
//         ListNode *curB = headB;
//         while (curA && curB) {
//             if (curA == curB) return curA;
//             curA = curA->next;
//             curB = curB->next;
//             if (!curA) curA = headB;
//             if (!curB) curB = headA;
//         }
//         //这样写如果不相交的话就无法终止了
//         return {};
//     }
// };
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        //这道题思路很简单,就是把自己的链表遍历完,然后转到另一个链表如果有公共节点就会相交,因为两个链表的总长是一定的
        //而相交后的链表长度也是一定的,所以到达相交节点的路程是相等的
        //当然也有可能不用跳转到另一个链表之前就相遇的情况
        ListNode *curA = headA;
        ListNode *curB = headB;
        while (curA != curB) { //这样就可以解决死循环的问题
            //这个是最简洁的写法
            // curA = curA ? curA->next : headB;
            // curB = curB ? curB->next : headA;

            //错误写法
            // if (!curA) curA = headB;
            // if (!curB) curB = headA;
            // curA = curA->next;
            // curB = curB->next;

            //另一种正确写法
            if (!curA) curA = headB;
            else curA = curA->next;
            if (!curB) curB = headA;
            else curB = curB->next;
            
        }
        return curA;
    }
};
//哈希法-在这道题上发挥不算很好
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_map <ListNode*, int> umap;
        ListNode *curA = headA; //尽量不改变原链表
        while (curA != nullptr) {
            ++umap[curA];
            //umap.insert(pair<ListNode*,int> (curA, 1)); //可行
            curA = curA->next;
        }
        ListNode *curB = headB;
        while (curB != nullptr) {
            if (umap[curB]) return curB;
            curB = curB->next;
        }
        return nullptr;
    }
};
```

#### [剑指 Offer 03. 数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

```
//第一种先排序再使用双指针的思想
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) { O(nlogn)
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] == nums[i + 1]) {
                return nums[i];
            }
        }
        return {};
    }
};
//第二种使用哈希
//效率极其垃圾
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_map <int, int> umap;
        for (int i = 0; i < nums.size(); ++i) {
            ++umap[nums[i]];
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (umap[nums[i]] > 1) {
                return nums[i];
            }
        }
        return {}; //这个没有用
    }
};
//第三种原地交换法
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == i) continue;
            if (nums[nums[i]] == nums[i]) return nums[i];
            swap (nums[nums[i]], nums[i]);
        }
        return {};
    }
};

```

#### [88. 合并两个有序数组](https://leetcode-cn.com/problems/merge-sorted-array/)

```
//逆向双指针
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int s1 = m - 1;
        int s2 = n - 1;
        int pos = m + n - 1;
        //while (s1 || s2) { //这个地方这样写是错的 //错误示例 [1] 1 [] 0 //这样的话s2起始就是负的，在while循环中非0就是true
        while (s1 >= 0 || s2 >= 0) {
            //这样写也是错误的,因为if判断后没有终止，依旧往下走，而s1和s2可能为负，访问负数下标错误
            // if (s1 < 0) nums1[pos--] = nums2[s2--];
            // if (s2 < 0) nums1[pos--] = nums1[s1--];
            // if (nums1[s1] < nums2[s2])
            //     nums1[pos--] = nums2[s2--];
            // else nums1[pos--] = nums1[s1--];
            if (s1 < 0) nums1[pos--] = nums2[s2--];
            else if (s2 < 0) nums1[pos--] = nums1[s1--];
            else if (nums1[s1] < nums2[s2]) nums1[pos--] = nums2[s2--];
            else nums1[pos--] = nums1[s1--];
        }
    }
};
//合并再sort //次选方案
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for (int i = 0; i != n; ++i) {
            nums1[m + i] = nums2[i];
        }
        sort(nums1.begin(),nums1.end());
    }
};
```

#### [69. x 的平方根](https://leetcode-cn.com/problems/sqrtx/)

二分法我推荐看这个https://leetcode-cn.com/problems/search-insert-position/solution/te-bie-hao-yong-de-er-fen-cha-fa-fa-mo-ban-python-/十分详细地讲解了二分法

```
//暴力法-不到万不得已不用
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) return 0;
        if (x == 1) return 1;
        if (x == 4) return 2;
        for (long i = 1; i <= x/2; ++i) {
            if (i * i == x) return i;
            else if (i * i < x && (i + 1) * (i + 1) > x) return i;
        }
        return {};
    }
};
//二分法
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) return 0;
        if (x == 1) return 1;
        if (x == 4) return 2;
        int left = 1;
        int right = x;
        while (right > left) {
            int mid = (right - left + 1) / 2 + left;
            //if (mid * mid > x ) //这样会超出整形范围，原因已知，在乘法中x是int范围，但x-1 * x- 1之类的会超
            if (mid > x / mid) {
                right = mid - 1;
            }
            else left = mid;
        }
        return left;
    }
};
```

