
#include <iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *currA = headA, *currB = headB;
        while ((currA != NULL) && (currB != NULL)) {
            
            if (currA->val == currB->val) {
                cout << currA->val << " A" << endl;
                cout << currB->val << " B" << endl;
                return currA;
            }
            currA = currA->next;
            currB = currB->next;
        }
        return NULL;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    ListNode *A = new ListNode(1);
    ListNode *currNode = A;
    currNode->next = new ListNode(2);
    ListNode *B = new ListNode(3);
    B->next = new ListNode(2);    
    s.getIntersectionNode(A, B);
    return 0;
}